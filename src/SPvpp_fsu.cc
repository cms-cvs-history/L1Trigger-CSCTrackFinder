#include <L1Trigger/CSCTrackFinder/src/SPvpp_fsu.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>

void SPvpp_fsu::operator()
( 
	Signal me2aRank, Signal phi2a, 
	Signal me2bRank, Signal phi2b, 
	Signal me2cRank, Signal phi2c, 
								   							   
	Signal me3aRank, Signal phi3a, 
	Signal me3bRank, Signal phi3b, 
	Signal me3cRank, Signal phi3c, 
								   						   
	Signal mb2aRank, Signal phib2a,
	Signal mb2bRank, Signal phib2b,
	Signal mb2cRank, Signal phib2c,

	Signal m0, Signal m1, Signal m2,

	Signal phi_watch_en, 
	Signal mindphi,

	Signal clk
)
{
initio

	me2aRank.input(5,0,"me2aRank");
	Input_(phi2a, BWPHI-1,0);	

	me2bRank.input(5,0,"me2bRank"); 
	Input_(phi2b, BWPHI-1,0);	

	me2cRank.input(5,0,"me2cRank"); 
	Input_(phi2c, BWPHI-1,0);	

	me3aRank.input(5,0,"me3aRank"); 
	Input_(phi3a, BWPHI-1,0);	

	me3bRank.input(5,0,"me3bRank"); 
	Input_(phi3b, BWPHI-1,0);	

	me3cRank.input(5,0,"me3cRank");
	Input_(phi3c, BWPHI-1,0);	

	mb2aRank.input(5,0,"mb2aRank"); 
	Input_(phib2a, BWPHI-1,0);	

	mb2bRank.input(5,0,"mb2bRank"); 
	Input_(phib2b, BWPHI-1,0);	

	mb2cRank.input(5,0,"mb2cRank"); 
	Input_(phib2c, BWPHI-1,0);	
	
	m0.output(8,0,"m0",makereg); 
	m1.output(8,0,"m1",makereg); 
	m2.output(8,0,"m2",makereg);

	Input (phi_watch_en); // enable ghost cancellation based on phi proximity
	Input_(mindphi, BWPHI-1, 0); // min phi difference

	Input (clk);

beginmodule

	CountZ.init(2,0,"_CountZ");
	
	rank.reg(5,0,8,0,"rank");
	Reg__(phi, BWPHI-1, 0, 8, 0);

	Reg__(rankr, 5, 0, 8, 0);     // 1bx delayed ranks
	Reg__(phir, BWPHI-1, 0, 8, 0);// 1bx delayed phis
	Reg__(rankrr, 5, 0, 8, 0);     // 2bx delayed ranks
	Reg__(phirr, BWPHI-1, 0, 8, 0);// 2bx delayed phis

	Exists.reg(8,0,"Exists");
	Reg_(survived, 8, 0);
	Larger.reg(8,0,8,0,"Larger");
	ilgj.reg(8,0,"ilgj");
	larg.reg(8,0,"larg");
	larg1.reg(8,0,"larg1");
	
	i.reg(7, 0, "i");
	j.reg(7, 0, "j");
	k.reg(7, 0, "k");
	
	s.reg(2,0,"s");

	Reg_(dphi, BWPHI-1, 0); // delta phi
	Reg_(dphir, BWPHI-1, 0); 
	Reg_(dphirr, BWPHI-1, 0); 

	Reg_(killrr1, 8, 0); // which rankrr to kill
	Reg_(killrr2, 8, 0); // which rankrr to kill
	Reg_(killrr3, 8, 0); // which rankrr to kill
	Reg_(killr,  8, 0); // which rankr to kill
	Reg_(kill,   8, 0); // which rank to kill

	
	always (posedge (clk))
	begin

			For (i = 0, i < 9, i++) // keep two clock history of tracks
			begin
				rankrr[i] = rankr[i]; 
				phirr[i]  = phir[i];

				rankr[i] = rank[i]; 
				phir[i]  = phi[i];
			end

		    rank[0] = me2aRank;
		    rank[1] = me2bRank;
	    	rank[2] = me2cRank;
		    rank[3] = me3aRank;
		    rank[4] = me3bRank;
	    	rank[5] = me3cRank;
		    rank[6] = mb2aRank;
		    rank[7] = mb2bRank;
	    	rank[8] = mb2cRank;

		    phi[0] = phi2a;
		    phi[1] = phi2b;
	    	phi[2] = phi2c;
		    phi[3] = phi3a;
		    phi[4] = phi3b;
	    	phi[5] = phi3c;
		    phi[6] = phib2a;
		    phi[7] = phib2b;
	    	phi[8] = phib2c;
		
			m0 = 0;
			m1 = 0;
			m2 = 0;
			k = 0;

			// simultaneously compare each rank with each
			For (i = 0, i < 9, i++)
			begin
				ilgj = 0;
				For (j = 0, j < 9, j++)
				begin
					// ilgj bits show which rank is larger
					// the comparison scheme below avoids problems
					// when there are two or more tracks with the same rank
					If 
					(
						(
							(i < j && rankrr[i] >= rankrr[j])  || 
							(i > j && rankrr[i] >  rankrr[j])     
						) && 
						!killr(i)
					)
					begin
						ilgj(j) = 1; 
					end
					
				end
				Larger[i] = ilgj; // "Larger" array shows the result of comparison for each rank
				// simultaneously check if some ranks are not zeroes, and remember the results in Exists bits	
				Exists(i) = (rankrr[i] != 0 && !killr(i));
			end

			killrr1 = 0;
			killrr2 = 0;
			killrr3 = 0;
			killr = kill; // remember tracks to kill from -2bx to current comparisons on previous clock
			kill = 0;

			If (phi_watch_en)
			begin
				For (i = 0, i < 9, i++) 
				begin
					For (j = i+1, j < 9, j++)
					begin
						// compare and possibly cancel tracks in the same clock 
						dphirr = ifelse(phirr[i] > phirr[j], phirr[i] - phirr[j], phirr[j] - phirr[i]); 
		
						If (dphirr < mindphi) // if they are close in phi
						begin
							If (Larger[i](j)) killrr1(j) = 1; // kill j if i is better
							Else              killrr1(i) = 1; // kill i if j is better
						end
					end
				end

				For (i = 0, i < 9, i++)
				begin
					For (j = 0, j < 9, j++)
					begin
						// compare -2bx tracks with -1bx, cancel delayed if there is a better current one close in phi
						dphir = ifelse(phirr[i] > phir[j], phirr[i] - phir[j], phir[j] - phirr[i]);
	
						If (dphir < mindphi) // phi is close
						begin
							If (rankrr[i] >= rankr[j]) killr(j) = 1; // -1bx is ghost (same or worse quality)
							Else                       killrr2(i) = 1; // delayed one is pre-ghost (not all stubs have come up yet)
						end
					end
				end

				For (i = 0, i < 9, i++)
				begin
					For (j = 0, j < 9, j++)
					begin
						// compare -2bx tracks with current ones, cancel delayed if there is a better current one close in phi
						dphi = ifelse(phirr[i] > phi[j], phirr[i] - phi[j], phi[j] - phirr[i]);
	
						If (dphi < mindphi) // phi is close
						begin
							If (rankrr[i] >= rank[j]) kill(j) = 1; // -0bx is ghost (same or worse quality)
							Else                      killrr3(i) = 1; // delayed one is pre-ghost (not all stubs have come up yet)
						end
					end
				end

			end

			survived = Exists & (~killrr1) & (~killrr2) & (~killrr3); // remove bad delayed tracks

			For (i = 0, i < 9, i++)
			begin
				If (survived(i)) Larger[i] = Larger[i] | (~survived); // if this track exists make it larger than all non-existing tracks
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
					case1("4'h7") s = CountZ ((larg1(8),   larg1(6,0)));
					case1("4'h8") s = CountZ (larg1(7,0));
				endcase

				// get the positional codes of the three best tracks to the three outputs
				If(s(0) == 1) m0(i) = 1; Else m0(i) = 0;
				If(s(1) == 1) m1(i) = 1; Else m1(i) = 0;
				If(s(2) == 1) m2(i) = 1; Else m2(i) = 0;
			end
	end

endmodule
}

Signal SPvpp_CountZeroes::operator()(Signal d)
{
	int bwin = mb ? 11 : 8; // input data width
	int bwout = mb ? 4 : 3; // output width

	initio
		d.input(bwin-1, 0, "d");
	beginfunction

		Reg_(s, 3, 0);
		Reg_(res, bwout-1, 0);

		begin
			s = 0;
			res = 0;
			for (int i = 0; i < bwin; i++)
			{
				If (!d(i)) s++;
			}
			If (s < bwout) res(s) = 1;
			result = res;
		end

	endfunction
}

/*
Signal SPvpp_CountZeroes11::operator()(Signal d)
{
	initio
		d.input(10,0,"d");
	beginfunction

		Reg_(s, 3, 0);
		Reg_(res, 3, 0);

		begin
			s = 0;
			res = 0;
			for (int i = 0; i < 11; i++)
			{
				If (!d(i)) s++;
			}
			If (s < 4) res(s) = 1;
			result = res;
		end

	endfunction
}
*/



