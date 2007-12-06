#include <L1Trigger/CSCTrackFinder/src/SPvpp_bxcorr.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>


void SPvpp_bxcorr::operator()
(
	Signal rank1, Signal rank2, Signal rank3,
	Signal b1, Signal b2, Signal b3,
	Signal id1, Signal id2, Signal id3,
	Signal bc1, Signal bc2, Signal bc3,
	Signal idc1, Signal idc2, Signal idc3,
	
	Signal acc,
	
	Signal pretrig,
	Signal clk
)
{
initio
	Input_(rank1, BWRANK-1, 0); 
	Input_(rank2, BWRANK-1, 0); 
	Input_(rank3, BWRANK-1, 0);

	Input_(b1, BWPOUT-1, 0); // three best tracks inputs
	Input_(b2, BWPOUT-1, 0); // {FRH, phiH, ptH, signH, modeMemH, etaPTH}
	Input_(b3, BWPOUT-1, 0);

	Input_(id1, MUIDSIZE-1, 0); // segment ids
	Input_(id2, MUIDSIZE-1, 0);
	Input_(id3, MUIDSIZE-1, 0);

	OutReg_(bc1, BWPOUT-1, 0); // tree best tracks with BX corrected 
	OutReg_(bc2, BWPOUT-1, 0);
	OutReg_(bc3, BWPOUT-1, 0);

	OutReg_(idc1, MUIDSIZE-1, 0); // segment ids for corrected tracks
	OutReg_(idc2, MUIDSIZE-1, 0);
	OutReg_(idc3, MUIDSIZE-1, 0);

	Input (acc); // accelerator track found
	
	Input_(pretrig, 1, 0); // how many stubs required to mark track timing
	Input (clk);

beginmodule

	CountZ.init(2, 0, "_CountZ");

	Reg__(in, BWPOUT-1, 0, 8, 0);
	Reg__(id, MUIDSIZE-1, 0, 8, 0);
	Reg__(r, BWRANK-1, 0, 8, 0);

	Reg_(Exists, 8, 0); // valid flags

	Reg_(m0, 8, 0); // positional codes for three best track stubs
	Reg_(m1, 8, 0);
	Reg_(m2, 8, 0);

	Reg_(i, 3, 0);
	Reg_(j, 3, 0);

	Reg_(ilgj, 8, 0); // q[i] > q[j] flags
	Reg__(Larger, 8, 0, 8, 0); // Larger[i] for each stub shows if it's better than any other stub
	Reg_(larg1, 8, 0);

	Reg_(s, 2, 0);
	Reg_(stubn, 2, 0);
	Reg_(stubd, 2, 0);
	Reg__(del2stubs, 2, 0, 8, 0);
	Reg__(del1stubs, 2, 0, 8, 0);

	int ii, jj;

	always (posedge (clk))
	begin

		For (i = 0, i < 3, i++)
		begin
			in[i+6] = in[i+3];
			in[i+3] = in[i];

			id[i+6] = id[i+3];
			id[i+3] = id[i];

			r[i+6] = r[i+3];
			r[i+3] = r[i];

			del1stubs[i+6] = del1stubs[i+3];
			del1stubs[i+3] = del1stubs[i];

			del2stubs[i+6] = del2stubs[i+3];
			del2stubs[i+3] = del2stubs[i];
		end
	
	end

	always 
	(
		b1 or b2 or b3 or
		id1 or id2 or id3 or
		rank1 or rank2 or rank3 or
		in[3] or in[4] or in[5] or in[6] or in[7] or in[8] or 
		id[3] or id[4] or id[5] or id[6] or id[7] or id[8] or 
		r[3] or r[4] or r[5] or r[6] or r[7] or r[8] or 
		del1stubs[3] or del1stubs[4] or del1stubs[5] or del1stubs[6] or del1stubs[7] or del1stubs[8] or 
		del2stubs[3] or del2stubs[4] or del2stubs[5] or del2stubs[6] or del2stubs[7] or del2stubs[8] or 
		pretrig
	)
	begin
	
	
		in[0] = b1; // input
		in[1] = b2;
		in[2] = b3;

		id[0] = id1; // id input
		id[1] = id2;
		id[2] = id3;

		r[0] = rank1; // rank
		r[1] = rank2; 
		r[2] = rank3; 

		// calculate number of stubs with delay == 2 and delay >= 1
		For (i = 0, i < 3, i++)
		begin
			del2stubs[i] = 0;
			del1stubs[i] = 0;
			for (jj = 0; jj < 6; jj++)
			{
				stubn = id[i](jj*6+2,jj*6); // stub number
				stubd = id[i](jj*6+5,jj*6+3); // stub delay
				If (stubn > 0 && stubd == 2) del2stubs[i]++; 
				If (stubn > 0 && stubd >= 1) del1stubs[i]++; 
			}
		end


		m0 = 0;
		m1 = 0;
		m2 = 0;

		bc1 = 0;		
		bc2 = 0;		
		bc3 = 0;		

		idc1 = 0;		
		idc2 = 0;		
		idc3 = 0;		

		For (i = 0, i < 9, i++)
		begin
			ilgj = 0;
			For (j = 0, j < 9, j++)
			begin
				// ilgj bits show which q is larger
				// the comparison scheme below avoids problems
				// when there are two or more stubs with the same q
				If 
				(
					(i < j && r[i] >= r[j])  || 
					(i > j && r[i] >  r[j])     
				)
				begin
					ilgj(j) = 1; 
				end
				
			end
			Larger[i] = ilgj; // "Larger" array shows the result of comparison for each stub
			Exists(i) = 
				r[i] != 0 &&
				(	
					(          i <= 2 && del2stubs[i] >= pretrig) ||
					(i >= 3 && i <= 5 && del1stubs[i] >= pretrig && del2stubs[i] < pretrig) ||
					(i >= 6           && del1stubs[i] < pretrig)
				); // track can be used only at the bx of the pretrigger condition

		end

		For (i = 0, i < 9, i++)
		begin
			If (Exists(i)) Larger[i] = Larger[i] | (~Exists); // if this track exists make it larger than all non-existing tracks
			Else Larger[i] = 0; // else make it smaller than anything

			larg1 = Larger[i];
			// count zeroes in the comparison results. The best track will have none, the next will have one, the third will have two.
			// skip the bits corresponding to the comparison of the track with itself
			begincase(i)
				case1("4'h0") s = CountZ (larg1(8,1));
				case1("4'h1") s = CountZ ((larg1(8,2), larg1(0)));
				case1("4'h2") s = CountZ ((larg1(8,3), larg1(1,0)));
				case1("4'h3") s = CountZ ((larg1(8,4), larg1(2,0)));
				case1("4'h4") s = CountZ ((larg1(8,5), larg1(3,0)));
				case1("4'h5") s = CountZ ((larg1(8,6), larg1(4,0)));
				case1("4'h6") s = CountZ ((larg1(8,7), larg1(5,0)));
				case1("4'h7") s = CountZ ((larg1(8)  , larg1(6,0)));
				case1("4'h8") s = CountZ (larg1(7,0));
			endcase

			// get the positional codes of the three best tracks to the three outputs
			If(s(0) == 1) m0(i) = 1; Else m0(i) = 0;
			If(s(1) == 1) m1(i) = 1; Else m1(i) = 0;
			If(s(2) == 1) m2(i) = 1; Else m2(i) = 0;

		end

		For (i = 0, i < 9, i++)
		begin
			bc1 = bc1  | ifelse(m0(i), in[i], 0);
			bc2 = bc2  | ifelse(m1(i), in[i], 0);
			bc3 = bc3  | ifelse(m2(i), in[i], 0);

			idc1 = idc1 | ifelse(m0(i), id[i], 0);
			idc2 = idc2 | ifelse(m1(i), id[i], 0);
			idc3 = idc3 | ifelse(m2(i), id[i], 0);
		end

		// if output 3 is not occupied, stick acc track in it
		If (bc3 == 0 && acc) 
		begin
			bc3(BWETAOUT+BWMODE-1, BWETAOUT) = MODE_ACC;
		end


	end

endmodule
}
