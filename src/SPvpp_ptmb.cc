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
	Signal orig_id,

	Signal ptp, 
	Signal signp, 
	Signal modeMemp, 
	Signal etaPTp,
	Signal FRp, 
	Signal phip,
	Signal orig_idrp,
	Signal rankrp,

	Signal clk
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
	Input_(orig_id , MUIDSIZE-1,0);

	OutReg_(ptp, BWPT-1,0); 
	OutReg (signp); 
	OutReg_(modeMemp, BWMODE-1,0);
	OutReg_(etaPTp, BWPTETA-1,0); 
	OutReg (FRp);
	OutReg_(phip, BWPHI-1, 0);
	OutReg_(orig_idrp , MUIDSIZE-1,0);
	OutReg_(rankrp, 5, 0);

	Input (clk);

beginmodule
	
	SelectPhisbp.init(11,0,"_SelectPhisbp");
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

	Reg_(pt, BWPT-1,0); // current track parameters
	Reg (sign); 
	Reg_(modeMem, BWMODE-1,0);
	Reg_(etaPT, BWPTETA-1,0); 
	Reg (FR);
	Reg_(phi, BWPHI-1, 0);

modulebody

	always (posedge (clk))
	begin
		me1Eta[0] = Signal(BWPTETA, 0); 
		me1Eta[1] = me1a(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA);  // this complicated bit numbering is made to take the most significant bits of the eta from the Signal values
		me1Eta[2] = me1b(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me1Eta[3] = me1c(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me1Eta[4] = me1d(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me1Eta[5] = me1e(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me1Eta[6] = me1f(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		
		me2Eta[0] = Signal(BWPTETA, 0); 
		me2Eta[1] = me2a(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me2Eta[2] = me2b(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me2Eta[3] = me2c(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		
		me1Phi[0] = Signal(BWPTETA, 0); 
		me1Phi[1] = me1a(BWPHI-1, 0); 
		me1Phi[2] = me1b(BWPHI-1, 0); 
		me1Phi[3] = me1c(BWPHI-1, 0); 
		me1Phi[4] = me1d(BWPHI-1, 0); 
		me1Phi[5] = me1e(BWPHI-1, 0); 
		me1Phi[6] = me1f(BWPHI-1, 0); 
		
		me2Phi[0] = Signal(BWPHI, 0); 
		me2Phi[1] = me2a(BWPHI-1, 0); 
		me2Phi[2] = me2b(BWPHI-1, 0); 
		me2Phi[3] = me2c(BWPHI-1, 0); 
		
		mb1Phi[0] = Signal(BWPHI, 0); 
		mb1Phi[1] = mb1a(BWPHI-1, 0); 
		mb1Phi[2] = mb1b(BWPHI-1, 0); 
		mb1Phi[3] = mb1c(BWPHI-1, 0); 
		mb1Phi[4] = mb1d(BWPHI-1, 0); 
		
		mb2Phi[0] = Signal(BWPHI, 0); 
		mb2Phi[1] = mb2a(BWPHI-1, 0); 
		mb2Phi[2] = mb2b(BWPHI-1, 0); 
		mb2Phi[3] = mb2c(BWPHI-1, 0);
		mb2Phi[4] = mb2d(BWPHI-1, 0);

		IdValid(0) = ifelse(idb2 != 0, 1, 0);
		IdValid(1) = ifelse(id2  != 0, 1, 0);
		IdValid(2) = ifelse(id1  != 0, 1, 0);
		IdValid(3) = ifelse(idb1 != 0, 1, 0);

		etaPT = 
			ifelse (IdValid(1) == 1, me2Eta[id2], 0);

		// phi is taken only from key station 2
		phi = ifelse (IdValid(1) == 1, me2Phi[id2], 0);
		
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
	
		sign = (phiA >= phiB);
		FR = 0;

		ptp		  = pt		;
		signp	  = sign	;
		modeMemp  = modeMem ;
		etaPTp	  = etaPT	;
		FRp		  = FR		;
		phip	  = phi	    ;
		orig_idrp = orig_id;
		rankrp    = rank    ;
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
				case1(Signal(4, 0)) begin EnableIdA = 0; EnableIdB = 0; EnableIdC = 0; end //         
				case1(Signal(4, 1)) begin EnableIdA = 1; EnableIdB = 0; EnableIdC = 0; end //       b2
				case1(Signal(4, 2)) begin EnableIdA = 2; EnableIdB = 0; EnableIdC = 0; end //	   2    
				case1(Signal(4, 3)) begin EnableIdA = 1; EnableIdB = 2; EnableIdC = 0; end //	   2  b2
				case1(Signal(4, 4)) begin EnableIdA = 4; EnableIdB = 0; EnableIdC = 0; end //	  1     
				case1(Signal(4, 5)) begin EnableIdA = 1; EnableIdB = 4; EnableIdC = 0; end //	  1   b2
				case1(Signal(4, 6)) begin EnableIdA = 4; EnableIdB = 2; EnableIdC = 0; end //	  12    
				case1(Signal(4, 7)) begin EnableIdA = 1; EnableIdB = 2; EnableIdC = 0; end //	  12  b2
				case1(Signal(4, 8)) begin EnableIdA = 8; EnableIdB = 0; EnableIdC = 0; end //		b1  
				case1(Signal(4, 9)) begin EnableIdA = 8; EnableIdB = 1; EnableIdC = 0; end //		b1b2
				case1(Signal(4,10)) begin EnableIdA = 8; EnableIdB = 2; EnableIdC = 0; end //	   2b1  
				case1(Signal(4,11)) begin EnableIdA = 8; EnableIdB = 2; EnableIdC = 0; end //	   2b1b2
				case1(Signal(4,12)) begin EnableIdA = 8; EnableIdB = 4; EnableIdC = 0; end //	  1	b1  
				case1(Signal(4,13)) begin EnableIdA = 8; EnableIdB = 4; EnableIdC = 0; end //	  1 b1b2
				case1(Signal(4,14)) begin EnableIdA = 8; EnableIdB = 2; EnableIdC = 0; end //	  12b1  
				case1(Signal(4,15)) begin EnableIdA = 8; EnableIdB = 2; EnableIdC = 0; end //	  12b1b2
			endcase
			result = (EnableIdA, EnableIdB, EnableIdC);
		end
	endfunction
}

Signal SPvpp_Modeb::operator()(Signal rank)
{
	initio
		rank.input(5,0,"rank");
	beginfunction
		begin
			begincase (rank)
				case1(Signal(6, 0x00))						result = 0;
				case3(Signal(6, 0x14), Signal(6, 0x19), Signal(6, 0x1e))	result = Signal(4, 0xb);
				case3(Signal(6, 0x20), Signal(6, 0x22), Signal(6, 0x24))	result = Signal(4, 0xb);
				case3(Signal(6, 0x13), Signal(6, 0x18), Signal(6, 0x1d))	result = Signal(4, 0xc);
				case1(Signal(6, 0x08))						result = Signal(4, 0xd);
				case3(Signal(6, 0x09), Signal(6, 0x0c), Signal(6, 0x0f))	result = Signal(4, 0xe);
				case1(Signal(6, 0x07))						result = Signal(4, 0xf);
// there could be e1e2 tracks in the overlap region
				case3(Signal(6, 0x06), Signal(6, 0x0b), Signal(6, 0x0e)) 	result = 6;
				Default								result = 0;
			endcase
		end
	endfunction
}


