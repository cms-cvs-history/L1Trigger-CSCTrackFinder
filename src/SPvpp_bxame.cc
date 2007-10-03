#include <L1Trigger/CSCTrackFinder/src/SPvpp_bxame.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>


void SPvpp_bxame::operator()
(
	Signal inA,  Signal inB,  Signal inC,  Signal inD,  
	Signal outA, Signal outB, Signal outC, Signal outD, 
	Signal bxidA, Signal bxidB, Signal bxidC, Signal bxidD,
	Signal depth,
	Signal clk
)
{

	int bwin = mb ? BWMBIN : BWMEIN; // width of the input data for endcap or barrel
	int tstub = mb ? 12 : 9; // total number of stubs to analyze, including delayed
	int ninp = mb ? 4 : 3; // number of inputs
	int bwq = mb ? BWQB : BWQ; // quality bit width

initio
	inA.input(bwin-1, 0, "inA"); // input stubs
	inB.input(bwin-1, 0, "inB");
	inC.input(bwin-1, 0, "inC");
	Input_(inD, bwin-1, 0);

	outA.output(bwin-1, 0, "outA", makereg); // output stubs
	outB.output(bwin-1, 0, "outB", makereg);
	outC.output(bwin-1, 0, "outC", makereg);
	OutReg_(outD, bwin-1, 0);

	OutReg_(bxidA, BWBXID-1, 0); // original bx number and stub ID for each output
	OutReg_(bxidB, BWBXID-1, 0);
	OutReg_(bxidC, BWBXID-1, 0);
	OutReg_(bxidD, BWBXID-1, 0);

	Input_(depth, 1, 0); // how many BXs to remember

	clk.input("clk");

beginmodule

//	if (mb) CountZ11.init(2, 0, "_CountZ11");
// 	else    CountZ.init(2, 0, "_CountZ");

	CountZ.init(mb ? 3 : 2, 0, mb ? "_CountZ11" : "_CountZ");
	CountZ.mb = mb;

	inAr.reg(bwin-1, 0, "inAr");
	inBr.reg(bwin-1, 0, "inBr");
	inCr.reg(bwin-1, 0, "inCr");
	Reg_(inDr, bwin-1, 0);

	Reg_(inArr, bwin-1, 0);
	Reg_(inBrr, bwin-1, 0);
	Reg_(inCrr, bwin-1, 0);
	Reg_(inDrr, bwin-1, 0);
	
	Wire__(id, BWBXID-1, 0, tstub-1, 0); // id numbers to assign
	Reg__(in, bwin-1, 0, tstub-1, 0); // all stubs, including delayed
	Reg__(q, bwq-1, 0, tstub-1, 0); // all qualities, including delayed
	Reg_(Exists, tstub-1, 0); // valid flags

	Reg_(m0, tstub-1, 0); // positional codes for three best track stubs
	Reg_(m1, tstub-1, 0);
	Reg_(m2, tstub-1, 0);
	if (mb) Reg_(m3, tstub-1, 0);

	Reg_(i, 3, 0);
	Reg_(j, 3, 0);

	Reg_(ilgj, tstub-1, 0); // q[i] > q[j] flags
	Reg__(Larger, tstub-1, 0, tstub-1, 0); // Larger[i] for each stub shows if it's better than any other stub
	Reg_(larg1, tstub-1, 0);

	Reg_(s, mb ? 3 : 2, 0);

	int ii;

	// assign stub IDs	
	for (ii = 0; ii < tstub; ii++)
	{
		assign id[ii] = ((Signal)cns(3, ii/ninp), cns(3, ii%ninp + 1 + idoff*3));
	}

	always (posedge (clk))
	begin

		ii = 0;
		in[ii++] = inA  ;
		in[ii++] = inB  ;
		in[ii++] = inC  ;
		if (mb) in[ii++] = inD;
		in[ii++] = inAr ;
		in[ii++] = inBr ;
		in[ii++] = inCr ;
		if (mb) in[ii++] = inDr;
		in[ii++] = inArr;
		in[ii++] = inBrr;
		in[ii++] = inCrr;
		if (mb) in[ii++] = inDrr;

		// qualities & valid flags
		For (i = 0, i < tstub, i++)
		begin
			if (mb)	
			{
				q[i] = in[i](BWQB + BWPHI-1, BWPHI);
				Exists(i) = q[i] != 0;
			}
			else 
			{
				q[i] = in[i](BWQ+BWETAIN+BWPHI-1, BWETAIN+BWPHI);
				Exists(i) = in[i] (bwin-1);
			}
		end

		m0 = 0;
		m1 = 0;
		m2 = 0;
		if (mb) m3 = 0;		

		outA = 0;
		outB = 0;
		outC = 0;
		outD = 0;

		bxidA = 0;
		bxidB = 0;
		bxidC = 0;
		bxidD = 0; 

		// simultaneously compare each q with each
		For (i = 0, i < tstub, i++)
		begin
			ilgj = 0;
			For (j = 0, j < tstub, j++)
			begin
				// ilgj bits show which q is larger
				// the comparison scheme below avoids problems
				// when there are two or more stubs with the same q
				If 
				(
					(i < j && q[i] >= q[j])  || 
					(i > j && q[i] >  q[j])     
				)
				begin
					ilgj(j) = 1; 
				end
				
			end
			Larger[i] = ilgj; // "Larger" array shows the result of comparison for each stub
		end

		For (i = 0, i < tstub, i++)
		begin
			If (Exists(i)) Larger[i] = Larger[i] | (~Exists); // if this track exists make it larger than all non-existing tracks
			Else Larger[i] = 0; // else make it smaller than anything

			larg1 = Larger[i];
			// count zeroes in the comparison results. The best track will have none, the next will have one, the third will have two.
			// skip the bits corresponding to the comparison of the track with itself
			if (mb)
			{
				begincase(i)
					case1("4'h0") s = CountZ (larg1(11,1));
					case1("4'h1") s = CountZ ((larg1(11,2) , larg1(0)));
					case1("4'h2") s = CountZ ((larg1(11,3) , larg1(1,0)));
					case1("4'h3") s = CountZ ((larg1(11,4) , larg1(2,0)));
					case1("4'h4") s = CountZ ((larg1(11,5) , larg1(3,0)));
					case1("4'h5") s = CountZ ((larg1(11,6) , larg1(4,0)));
					case1("4'h6") s = CountZ ((larg1(11,7) , larg1(5,0)));
					case1("4'h7") s = CountZ ((larg1(11,8) , larg1(6,0)));
					case1("4'h8") s = CountZ ((larg1(11,9) , larg1(7,0)));
					case1("4'h9") s = CountZ ((larg1(11,10), larg1(8,0)));
					case1("4'ha") s = CountZ ((larg1(11)   , larg1(9,0)));
					case1("4'hb") s = CountZ (larg1(10,0));
				endcase
			}
			else
			{
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
			}

			// get the positional codes of the three best tracks to the three outputs
			If(s(0) == 1) m0(i) = 1; Else m0(i) = 0;
			If(s(1) == 1) m1(i) = 1; Else m1(i) = 0;
			If(s(2) == 1) m2(i) = 1; Else m2(i) = 0;
			if (mb) {If(s(3) == 1) m3(i) = 1; Else m3(i) = 0;}

		end
	
		for (ii = 0; ii < tstub; ii++)
		{
			outA  = outA  | ifelse(m0(ii), in[ii], 0);
			outB  = outB  | ifelse(m1(ii), in[ii], 0);
			outC  = outC  | ifelse(m2(ii), in[ii], 0);
			if (mb) {outD  = outD  | ifelse(m3(ii), in[ii], 0);}

			bxidA = bxidA | ifelse(m0(ii), id[ii], 0);
			bxidB = bxidB | ifelse(m1(ii), id[ii], 0);
			bxidC = bxidC | ifelse(m2(ii), id[ii], 0);
			if (mb) {bxidD = bxidD | ifelse(m3(ii), id[ii], 0);}
		}

		If (depth >= 2)
		begin
			inArr = inAr; // register all stubs for two-bx history
			inBrr = inBr;
			inCrr = inCr;
			if (mb) inDrr = inDr;
		end
		Else
		begin
			inArr = 0;
			inBrr = 0;
			inCrr = 0;
			if (mb) inDrr = 0;
		end

		If (depth >= 1)
		begin
			inAr = inA; // register all stubs for one-bx history
			inBr = inB;
			inCr = inC;
			if (mb) inDr = inD;
		end
		Else
		begin
			inAr = 0;
			inBr = 0;
			inCr = 0;
			if (mb) inDr = 0;
		end
	end

		
endmodule
}

