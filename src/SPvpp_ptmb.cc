#include <L1Trigger/CSCTrackFinder/src/SPvpp_ptmb.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>

void SPvpp_ptmb::operator()
(
	// all etas use only 4 MSBs from the original Eta
	Signal me1a, Signal me1b, Signal me1c, Signal me1d, Signal me1e, Signal me1f, 
	Signal me2a, Signal me2b, Signal me2c, 
	Signal mb1a, Signal mb1b, Signal mb1c, Signal mb1d, 
	Signal mb2a, Signal mb2b, Signal mb2c, Signal mb2d, 
	
	Signal rank,
	Signal id1, Signal id2, Signal idb1, Signal idb2,
	
	Signal pt, 
	Signal sign, 
	Signal modeMem, 
	Signal etaPT,
	Signal FR, 
	Signal phi
)
{
initio

	me1a.input(BWMEIN-1,0,"me1a"); 
	me1b.input(BWMEIN-1,0,"me1b"); 
	me1c.input(BWMEIN-1,0,"me1c"); 
	me1d.input(BWMEIN-1,0,"me1d"); 
	me1e.input(BWMEIN-1,0,"me1e"); 
	me1f.input(BWMEIN-1,0,"me1f"); 

	me2a.input(BWMEIN-1,0,"me2a"); 
	me2b.input(BWMEIN-1,0,"me2b"); 
	me2c.input(BWMEIN-1,0,"me2c"); 

	mb1a.input(BWMBIN-1,0,"mb1a"); 
	mb1b.input(BWMBIN-1,0,"mb1b"); 
	mb1c.input(BWMBIN-1,0,"mb1c"); 
	mb1d.input(BWMBIN-1,0,"mb1d"); 

	mb2a.input(BWMBIN-1,0,"mb2a"); 
	mb2b.input(BWMBIN-1,0,"mb2b"); 
	mb2c.input(BWMBIN-1,0,"mb2c"); 
	mb2d.input(BWMBIN-1,0,"mb2d");

	rank.input(5,0,"rank"); 

	id1.input(2,0,"id1"); 
	id2.input(1,0,"id2"); 
	idb1.input(2,0,"idb1"); 
	idb2.input(2,0,"idb2");

	pt.output(BWPT-1,0,"pt",makereg); 
	sign.output("sign",makereg); 
	modeMem.output(BWMODE-1,0,"modeMem", makereg);
	etaPT.output(BWPTETA-1,0,"etaPT",makereg); 
	FR.output("FR", makereg);
	phi.output(BWPHI-1, 0, "phi", makereg);

beginmodule
	
	SelectPhisbp.init(11,0,"_SelectPhisbp");
//	SelectEtabp.init(1,0,"_SelectEtabp");
	Modebp.init(3,0,"_Modebp");	
	
	mode.reg(3,0,"mode"); 
	a.reg(11,0,"a"); 
	b.reg(11,0,"b");
	si.reg("si"); 
	d.reg(12,0,"d"); 
//	SelEta.reg(3,0,"SelEta"); 
	SelPhi.reg(11,0,"SelPhi"); 
	IdValid.reg(3,0,"IdValid");

	me1Eta.reg(BWPTETA-1,0,6,0,"me1Eta");
	me2Eta.reg(BWPTETA-1,0,3,0,"me2Eta");
	me1Phi.reg(BWPHI-1,0,6,0,"me1Phi");
	me2Phi.reg(BWPHI-1,0,3,0,"me2Phi");
	mb1Phi.reg(BWPHI-1,0,6,0,"mb1Phi");
	mb2Phi.reg(BWPHI-1,0,6,0,"mb2Phi");
	phiA.reg(BWPHI-1,0,"phiA"); 
	phiB.reg(BWPHI-1,0,"phiB"); 
	phiC.reg(BWPHI-1,0,"phiC"); 

	always 
	(
		me1a or me1b or me1c or me1d or me1e or me1f or 
		me2a or me2b or me2c or 
		mb1a or mb1b or mb1c or mb1d or 
		mb2a or mb2b or mb2c or mb2d or
		
		rank or
		id1 or id2 or idb1 or idb2
	)
	begin
		me1Eta[0] = 0; 
		me1Eta[1] = me1a(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA);  // this complicated bit numbering is made to take the most significant bits of the eta from the Signal values
		me1Eta[2] = me1b(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me1Eta[3] = me1c(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me1Eta[4] = me1d(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me1Eta[5] = me1e(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me1Eta[6] = me1f(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		
		me2Eta[0] = 0; 
		me2Eta[1] = me2a(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me2Eta[2] = me2b(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me2Eta[3] = me2c(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		
		me1Phi[0] = 0; 
		me1Phi[1] = me1a(BWPHI-1, 0); 
		me1Phi[2] = me1b(BWPHI-1, 0); 
		me1Phi[3] = me1c(BWPHI-1, 0); 
		me1Phi[4] = me1d(BWPHI-1, 0); 
		me1Phi[5] = me1e(BWPHI-1, 0); 
		me1Phi[6] = me1f(BWPHI-1, 0); 
		
		me2Phi[0] = 0; 
		me2Phi[1] = me2a(BWPHI-1, 0); 
		me2Phi[2] = me2b(BWPHI-1, 0); 
		me2Phi[3] = me2c(BWPHI-1, 0); 
		
		mb1Phi[0] = 0; 
		mb1Phi[1] = mb1a(BWPHI-1, 0); 
		mb1Phi[2] = mb1b(BWPHI-1, 0); 
		mb1Phi[3] = mb1c(BWPHI-1, 0); 
		mb1Phi[4] = mb1d(BWPHI-1, 0); 
		
		mb2Phi[0] = 0; 
		mb2Phi[1] = mb2a(BWPHI-1, 0); 
		mb2Phi[2] = mb2b(BWPHI-1, 0); 
		mb2Phi[3] = mb2c(BWPHI-1, 0);
		mb2Phi[4] = mb2d(BWPHI-1, 0);

		IdValid(0) = ifelse(idb2 != 0, 1, 0);
		IdValid(1) = ifelse(id2  != 0, 1, 0);
		IdValid(2) = ifelse(id1  != 0, 1, 0);
		IdValid(3) = ifelse(idb1 != 0, 1, 0);

//		SelEta = SelectEtabp(IdValid);
//		etaPT = 
//			ifelse (SelEta(1) == 1, me1Eta[id1],
//			ifelse (SelEta(0) == 1, me2Eta[id2], 0));

		etaPT = 
//			ifelse (IdValid(2) == 1, me1Eta[id1],
			ifelse (IdValid(1) == 1, me2Eta[id2], 0);

//		phi = 
//			ifelse (SelEta(1) == 1, me1Phi[id1],
//			ifelse (SelEta(0) == 1, me2Phi[id2], 0));

		// phi is taken only from key station 2
		phi = ifelse (IdValid(1) == 1, me2Phi[id2], 0);
		
//		FR = ifelse(id1 != 0, me1FR(id1), 0);

		SelPhi = SelectPhisbp(IdValid);
		phiA = 
			ifelse (SelPhi(11) == 1, mb1Phi[idb1],
			ifelse (SelPhi(10) == 1, me1Phi[id1],
			ifelse (SelPhi(9)  == 1, me2Phi[id2],
			ifelse (SelPhi(8)  == 1, mb2Phi[idb2], 0))));
		phiB = 			   
			ifelse (SelPhi(7) == 1, mb1Phi[idb1],
			ifelse (SelPhi(6) == 1, me1Phi[id1],
			ifelse (SelPhi(5)  == 1, me2Phi[id2],
			ifelse (SelPhi(4)  == 1, mb2Phi[idb2], 0))));
		phiC = 			   
			ifelse (SelPhi(3) == 1, mb1Phi[idb1],
			ifelse (SelPhi(2) == 1, me1Phi[id1],
			ifelse (SelPhi(1)  == 1, me2Phi[id2],
			ifelse (SelPhi(0)  == 1, mb2Phi[idb2], 0))));

		a = ifelse (phiA >= phiB, phiA - phiB, phiB - phiA);
		b = ifelse (phiB >= phiC, phiB - phiC, phiC - phiB);

		d(11,0) = phiA - phiB;
		d(12) = ifelse (phiA >= phiB, 1, 0);

		mode = Modebp(rank);

        pt = d;
	    
		si = ifelse ((d(12,9) != 7 && d(12,9) != 8 && mode > 5), 1, 0);
	
		modeMem = ifelse (si == 0, mode, 1);
	
//		sign = (phiA >= phiB) && (si == 0);
		sign = (phiA >= phiB);
		FR = 0;
	end
endmodule

}


Signal SPvpp_SelectPhisb::operator()(Signal IdValid)
{
	initio
		IdValid.input(3,0,"IdValid");
	beginfunction
		EnableIdA.reg(3,0,"EnableIdA");
		EnableIdB.reg(3,0,"EnableIdB");
		EnableIdC.reg(3,0,"EnableIdC");
		begin	
			begincase (IdValid)
				case1("4'b0000") begin EnableIdA = 0; EnableIdB = 0; EnableIdC = 0; end //         
				case1("4'b0001") begin EnableIdA = 1; EnableIdB = 0; EnableIdC = 0; end //       b2
				case1("4'b0010") begin EnableIdA = 2; EnableIdB = 0; EnableIdC = 0; end //	   2    
				case1("4'b0011") begin EnableIdA = 1; EnableIdB = 2; EnableIdC = 0; end //	   2  b2
				case1("4'b0100") begin EnableIdA = 4; EnableIdB = 0; EnableIdC = 0; end //	  1     
				case1("4'b0101") begin EnableIdA = 1; EnableIdB = 4; EnableIdC = 0; end //	  1   b2
				case1("4'b0110") begin EnableIdA = 4; EnableIdB = 2; EnableIdC = 0; end //	  12    
				case1("4'b0111") begin EnableIdA = 1; EnableIdB = 2; EnableIdC = 0; end //	  12  b2
				case1("4'b1000") begin EnableIdA = 8; EnableIdB = 0; EnableIdC = 0; end //		b1  
				case1("4'b1001") begin EnableIdA = 8; EnableIdB = 1; EnableIdC = 0; end //		b1b2
				case1("4'b1010") begin EnableIdA = 8; EnableIdB = 2; EnableIdC = 0; end //	   2b1  
				case1("4'b1011") begin EnableIdA = 8; EnableIdB = 2; EnableIdC = 0; end //	   2b1b2
				case1("4'b1100") begin EnableIdA = 8; EnableIdB = 4; EnableIdC = 0; end //	  1	b1  
				case1("4'b1101") begin EnableIdA = 8; EnableIdB = 4; EnableIdC = 0; end //	  1 b1b2
				case1("4'b1110") begin EnableIdA = 8; EnableIdB = 2; EnableIdC = 0; end //	  12b1  
				case1("4'b1111") begin EnableIdA = 8; EnableIdB = 2; EnableIdC = 0; end //	  12b1b2
			endcase
			result = (EnableIdA, EnableIdB, EnableIdC);
		end
	endfunction
}
/*	
Signal SPvpp_SelectEtab::operator()(Signal IdValid)
{
	initio
		IdValid.input(3,0,"IdValid");
	beginfunction	
		begin
			If (IdValid(2)) result = 2;
			Else 
				If (IdValid(1)) result = 1;
				Else 
					result = 0;
		end
	endfunction
}
  */
Signal SPvpp_Modeb::operator()(Signal rank)
{
	initio
		rank.input(5,0,"rank");
	beginfunction
		begin
			begincase (rank)
				case1("6'h00")						result = 0;
				case3("6'h14", "6'h19", "6'h1e")	result = "4'hb";
				case3("6'h20", "6'h22", "6'h24")	result = "4'hb";
				case3("6'h13", "6'h18", "6'h1d")	result = "4'hc";
				case1("6'h08")						result = "4'hd";
				case3("6'h09", "6'h0c", "6'h0f")	result = "4'he";
				case1("6'h07")						result = "4'hf";
// there could be e1e2 tracks in the overlap region
				case3("6'h06", "6'h0b", "6'h0e") 	result = 6;
				Default								result = 0;
			endcase
		end
	endfunction
}


