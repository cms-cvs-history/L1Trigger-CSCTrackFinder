#include <L1Trigger/CSCTrackFinder/src/SPvpp_fsu.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>

void SPvpp_fsu::operator()
( 
	Signal me2aRank, Signal me2aId1, Signal me2aId3, Signal me2aId4, 
	Signal me2bRank, Signal me2bId1, Signal me2bId3, Signal me2bId4, 
	Signal me2cRank, Signal me2cId1, Signal me2cId3, Signal me2cId4, 

	Signal me3aRank, Signal me3aId1, Signal me3aId2, Signal me3aId4, 
	Signal me3bRank, Signal me3bId1, Signal me3bId2, Signal me3bId4, 
	Signal me3cRank, Signal me3cId1, Signal me3cId2, Signal me3cId4, 
	
	Signal mb2aRank, Signal mb2aId1, Signal mb2aIdb1, Signal mb2aIdb2, 
	Signal mb2bRank, Signal mb2bId1, Signal mb2bIdb1, Signal mb2bIdb2, 
	Signal mb2cRank, Signal mb2cId1, Signal mb2cIdb1, Signal mb2cIdb2, 

	Signal m0, Signal m1, Signal m2
)
{
initio

	me2aRank.input(5,0,"me2aRank");	
	me2aId1.input(2,0,"me2aId1");	
	me2aId3.input(1,0,"me2aId3"); 
	me2aId4.input(1,0,"me2aId4"); 

	me2bRank.input(5,0,"me2bRank"); 
	me2bId1.input(2,0,"me2bId1"); 
	me2bId3.input(1,0,"me2bId3"); 
	me2bId4.input(1,0,"me2bId4");	

	me2cRank.input(5,0,"me2cRank"); 
	me2cId1.input(2,0,"me2cId1"); 
	me2cId3.input(1,0,"me2cId3"); 
	me2cId4.input(1,0,"me2cId4"); 

	me3aRank.input(5,0,"me3aRank"); 
	me3aId1.input(2,0,"me3aId1"); 
	me3aId2.input(1,0,"me3aId2"); 
	me3aId4.input(1,0,"me3aId4"); 

	me3bRank.input(5,0,"me3bRank"); 
	me3bId1.input(2,0,"me3bId1"); 
	me3bId2.input(1,0,"me3bId2"); 
	me3bId4.input(1,0,"me3bId4"); 
	
	me3cRank.input(5,0,"me3cRank");
	me3cId1.input(2,0,"me3cId1");
	me3cId2.input(1,0,"me3cId2"); 
	me3cId4.input(1,0,"me3cId4");


	mb2aRank.input(5,0,"mb2aRank"); 
	mb2aId1.input(2,0,"mb2aId1"); 
	mb2aIdb1.input(2,0,"mb2aIdb1"); 
	mb2aIdb2.input(2,0,"mb2aIdb2"); 

	mb2bRank.input(5,0,"mb2bRank"); 
	mb2bId1.input(2,0,"mb2bId1"); 
	mb2bIdb1.input(2,0,"mb2bIdb1"); 
	mb2bIdb2.input(2,0,"mb2bIdb2"); 

	mb2cRank.input(5,0,"mb2cRank"); 
	mb2cId1.input(2,0,"mb2cId1"); 
	mb2cIdb1.input(2,0,"mb2cIdb1"); 
	mb2cIdb2.input(2,0,"mb2cIdb2");
	
	m0.output(8,0,"m0",makereg); 
	m1.output(8,0,"m1",makereg); 
	m2.output(8,0,"m2",makereg);

beginmodule

	CountZ.init(2,0,"_CountZ");
	
	rank.reg(5,0,8,0,"rank");
	Id1.reg(2,0,8,0,"Id1");
	Id2.reg(1,0,8,0,"Id2");
	Id3.reg(2,0,8,0,"Id3");
	Id4.reg(2,0,8,0,"Id4");

	Reg_(Id1i, 2, 0); // temp variables
	Reg_(Id2i, 1, 0);
	Reg_(Id3i, 2, 0);
	Reg_(Id4i, 2, 0);

	Reg_(Id1j, 2, 0); // temp variables
	Reg_(Id2j, 1, 0);
	Reg_(Id3j, 2, 0);
	Reg_(Id4j, 2, 0);

	CommonStub.reg(35,0,"CommonStub");
	Exists.reg(8,0,"Exists");
	Larger.reg(8,0,8,0,"Larger");
	ilgj.reg(8,0,"ilgj");
	larg.reg(8,0,"larg");
	larg1.reg(8,0,"larg1");
	
	i.reg(7, 0, "i");
	int ii;
	j.reg(7, 0, "j");
	k.reg(7, 0, "k");
	
	s.reg(2,0,"s");
	
	always 
	(
		me2aRank or me2aId1 or me2aId3 or me2aId4 or 
		me2bRank or me2bId1 or me2bId3 or me2bId4 or 
		me2cRank or me2cId1 or me2cId3 or me2cId4 or 

		me3aRank or me3aId1 or me3aId2 or me3aId4 or 
		me3bRank or me3bId1 or me3bId2 or me3bId4 or 
		me3cRank or me3cId1 or me3cId2 or me3cId4 or 
	
		mb2aRank or mb2aId1 or mb2aIdb1 or mb2aIdb2 or 
		mb2bRank or mb2bId1 or mb2bIdb1 or mb2bIdb2 or 
		mb2cRank or mb2cId1 or mb2cIdb1 or mb2cIdb2
	)
	begin


		    rank[0] = me2aRank;
		    rank[1] = me2bRank;
	    	rank[2] = me2cRank;
		    rank[3] = me3aRank;
		    rank[4] = me3bRank;
	    	rank[5] = me3cRank;
		    rank[6] = mb2aRank;
		    rank[7] = mb2bRank;
	    	rank[8] = mb2cRank;
//--------------------------------------	
		    Id1[0] = me2aId1;
		    Id1[1] = me2bId1;
	    	Id1[2] = me2cId1;

		    Id2[0] = 1;
		    Id2[1] = 2;
	    	Id2[2] = 3;
		
		    Id3[0] = me2aId3;
		    Id3[1] = me2bId3;
	    	Id3[2] = me2cId3;
	
		    Id4[0] = me2aId4;
		    Id4[1] = me2bId4;
	    	Id4[2] = me2cId4;
//--------------------------------------	
		    Id1[3] = me3aId1;
		    Id1[4] = me3bId1;
	    	Id1[5] = me3cId1;
	
		    Id2[3] = me3aId2;
		    Id2[4] = me3bId2;
	    	Id2[5] = me3cId2;
	
		    Id3[3] = 1;
		    Id3[4] = 2;
	    	Id3[5] = 3;
	
		    Id4[3] = me3aId4;
		    Id4[4] = me3bId4;
	    	Id4[5] = me3cId4;
//--------------------------------------	
		    Id1[6] = mb2aId1;
		    Id1[7] = mb2bId1;
	    	Id1[8] = mb2cId1;
	
		    Id2[6] = 1;
		    Id2[7] = 2;
	    	Id2[8] = 3;
	
		    Id3[6] = mb2aIdb1;
		    Id3[7] = mb2bIdb1;
	    	Id3[8] = mb2cIdb1;
	
		    Id4[6] = mb2aIdb2;
		    Id4[7] = mb2bIdb2;
	    	Id4[8] = mb2cIdb2;
//--------------------------------------	

		
			m0 = 0;
			m1 = 0;
			m2 = 0;
			k = 0;
			CommonStub = 0;
			// first compare each stub number with each to find is there are the same stubs in two tracks. 
			for (ii = 0; ii < 8; ii++)	// this loop is unrolled in Verilog since XST compiler does not allow cycle variable to be inited with non-constant
			{
				For (j = ii+1, j < 9, j++)
				begin
					Id1i = Id1[ii]; Id1j = Id1[j];
					Id2i = Id2[ii]; Id2j = Id2[j];
					Id3i = Id3[ii]; Id3j = Id3[j];
					Id4i = Id4[ii]; Id4j = Id4[j];
					If 
					(
						(Id1i == Id1j && Id1i != 0) ||
						(Id2i == Id2j && Id2i != 0) ||
						((j<6  && ii<6 ) && Id3i == Id3j && Id3i != 0) ||
						((j>=6 && ii>=6) && Id3i == Id3j && Id3i != 0) ||
						((j<6  && ii<6 ) && Id4i == Id4j && Id4i != 0) ||
						((j>=6 && ii>=6) && Id4i == Id4j && Id4i != 0)
					)
					begin
						CommonStub(k) = 1; // These bits will remember the result of the comparison
					end
					k++;
				end
			}

			// simultaneously compare each rank with each
			For (i = 0, i < 9, i++)
			begin
				ilgj = 0;
				For (j = 0, j < 9, j++)
				begin
					// ilgj bits show which rank is larger
					If (i < j)	If (rank[i] >= rank[j]) ilgj(j) = 1; // this comparison scheme allows to avoid problems
					If (i > j)	If (rank[i] >  rank[j]) ilgj(j) = 1; // when there are two or more tracks with the same rank
				end
				Larger[i] = ilgj; // "Larger" array shows the result of comparison for each rank
				// simultaneously check if some ranks are not zeroes, and remember the results in Exists bits	
				Exists(i) = (rank[i] != 0);
			end

			k = 0;			
			for (ii = 0; ii < 8; ii++)	// this loop is unrolled in Verilog since XST compiler does not allow cycle variable to be inited with non-constant
			{
				larg = Larger[ii];
				For (j = ii+1, j < 9, j++) 
				begin
					If (CommonStub(k)) //if there is a common stub in tracks [i] and [j]
					begin
						If (larg(j)) Exists(j) = 0;  // if [i] >= [j] kill [j] 
						Else   		 Exists(ii) = 0;  // else kill [i]
					end
					k++;
				end
			}

			For (i = 0, i < 9, i++)
			begin
				If (Exists(i)) Larger[i] = Larger[i] | (~Exists); // if this track exists make it larger than all non-existing tracks
				Else Larger[i] = 0; // else make it smaller than anything

				larg1 = Larger[i];
				// count zeroes in the comparison results. The best track will have none, the next will have one, the third will have two.
				// skip the bits corresponding to the comparison of the track with itself
				begincase(i)
					case1("8'h00") s = CountZ (larg1(8,1));
					case1("8'h01") s = CountZ ((larg1(8,2), larg1(0)));
					case1("8'h02") s = CountZ ((larg1(8,3), larg1(1,0)));
					case1("8'h03") s = CountZ ((larg1(8,4), larg1(2,0)));
					case1("8'h04") s = CountZ ((larg1(8,5), larg1(3,0)));
					case1("8'h05") s = CountZ ((larg1(8,6), larg1(4,0)));
					case1("8'h06") s = CountZ ((larg1(8,7), larg1(5,0)));
					case1("8'h07") s = CountZ ((larg1(8),   larg1(6,0)));
					case1("8'h08") s = CountZ (larg1(7,0));
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
	initio
		d.input(7,0,"d");
	beginfunction
		begincase(d)	
			
				case1("8'b11111111") result = 1;

				case1("8'b11111110") result = 2;
				case1("8'b11111101") result = 2;
				case1("8'b11111011") result = 2;
				case1("8'b11110111") result = 2;
				case1("8'b11101111") result = 2;
				case1("8'b11011111") result = 2;
				case1("8'b10111111") result = 2;
				case1("8'b01111111") result = 2;

				case1("8'b11111100") result = 4;
				case1("8'b11111010") result = 4;
				case1("8'b11110110") result = 4;
				case1("8'b11101110") result = 4;
				case1("8'b11011110") result = 4;
				case1("8'b10111110") result = 4;
				case1("8'b01111110") result = 4;

				case1("8'b11111001") result = 4;
				case1("8'b11110101") result = 4;
				case1("8'b11101101") result = 4;
				case1("8'b11011101") result = 4;
				case1("8'b10111101") result = 4;
				case1("8'b01111101") result = 4;

				case1("8'b11110011") result = 4;
				case1("8'b11101011") result = 4;
				case1("8'b11011011") result = 4;
				case1("8'b10111011") result = 4;
				case1("8'b01111011") result = 4;
				
				case1("8'b11100111") result = 4;
				case1("8'b11010111") result = 4;
				case1("8'b10110111") result = 4;
				case1("8'b01110111") result = 4;

				case1("8'b11001111") result = 4;
				case1("8'b10101111") result = 4;
				case1("8'b01101111") result = 4;

				case1("8'b10011111") result = 4;
				case1("8'b01011111") result = 4;

				case1("8'b00111111") result = 4;

				Default  result = 0;
		endcase
			
	endfunction
}




