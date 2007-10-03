#include <L1Trigger/CSCTrackFinder/src/SPvpp_ptme.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>


#define PHICUTL 128
#define PHICUTH (4095 - PHICUTL)


void SPvpp_ptme::operator()
(
	// all etas use only 4 MSBs from the original Eta

	Signal me1a, Signal me1b, Signal me1c, Signal me1d, Signal me1e, Signal me1f, 
	Signal me2a, Signal me2b, Signal me2c, 
	Signal me3a, Signal me3b, Signal me3c, 
	Signal me4a, Signal me4b, Signal me4c,
	
	Signal rank,
	Signal id1, Signal id2, Signal id3, Signal id4,
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
			  	
	me3a.input(BWMEIN-1,0,"me3a"); 
	me3b.input(BWMEIN-1,0,"me3b"); 
	me3c.input(BWMEIN-1,0,"me3c");
			  	
	me4a.input(BWMEIN-1,0,"me4a"); 
	me4b.input(BWMEIN-1,0,"me4b"); 
	me4c.input(BWMEIN-1,0,"me4c");

	rank.input(5,0,"rank"); 
	id1.input(2,0,"id1"); 
	id2.input(1,0,"id2"); 
	id3.input(1,0,"id3"); 
	id4.input(1,0,"id4");
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

	SelectPhisp.init(11,0,"_SelectPhisp");
	Modep.init(3,0,"_Modep");	 
	DecodeFR.init(0, 0, "_DecodeFR");

    mode.reg(3,0,"mode"); 
	a.reg(11,0,"a"); 
	b.reg(11,0,"b");
    modeout.reg(3,0,"modeout"); 
	modenew.reg(3,0,"modenew");
	si.reg("si"); 
	d.reg(12,0,"d"); 
 	c.reg(12,0,"c"); 
	SelPhi.reg(11,0,"SelPhi"); 
	IdValid.reg(3,0,"IdValid");

	me1Eta.reg(BWPTETA-1,0,NSEG1,0,"me1Eta");
	me2Eta.reg(BWPTETA-1,0,NSEG234,0,"me2Eta");
	me3Eta.reg(BWPTETA-1,0,NSEG234,0,"me3Eta");

	me1Phi.reg(BWPHI-1,0,NSEG1,0,"me1Phi");
	me2Phi.reg(BWPHI-1,0,NSEG234,0,"me2Phi");
	me3Phi.reg(BWPHI-1,0,NSEG234,0,"me3Phi");
	me4Phi.reg(BWPHI-1,0,NSEG234,0,"me4Phi");

	phiA.reg(BWPHI-1,0,"phiA"); 
	phiB.reg(BWPHI-1,0,"phiB"); 
	phiC.reg(BWPHI-1,0,"phiC"); 

	me1FR.reg(NSEG1, 0, "me1FR");

	Reg__ (CSCID, BWCSCID-1,0,NSEG1,0);

	Reg_(pt, BWPT-1,0); // current track parameters
	Reg (sign); 
	Reg_(modeMem, BWMODE-1,0);
	Reg_(etaPT, BWPTETA-1,0); 
	Reg (FR);
	Reg_(phi, BWPHI-1, 0);

	always (posedge (clk))
	begin

		me1Eta[0] = 0; 
		me1Eta[1] = me1a(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); // this complicated bit numbering is made to take the most significant bits of the eta from the Signal values
		me1Eta[2] = me1b(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me1Eta[3] = me1c(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me1Eta[4] = me1d(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me1Eta[5] = me1e(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me1Eta[6] = me1f(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		
		me2Eta[0] = 0; 
		me2Eta[1] = me2a(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me2Eta[2] = me2b(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me2Eta[3] = me2c(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		
		me3Eta[0] = 0; 
		me3Eta[1] = me3a(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me3Eta[2] = me3b(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA); 
		me3Eta[3] = me3c(BWPHI+BWETAIN-1, BWPHI+BWETAIN-BWPTETA);
		
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
		
		me3Phi[0] = 0; 
		me3Phi[1] = me3a(BWPHI-1, 0); 
		me3Phi[2] = me3b(BWPHI-1, 0); 
		me3Phi[3] = me3c(BWPHI-1, 0); 
		
		me4Phi[0] = 0; 
		me4Phi[1] = me4a(BWPHI-1, 0); 
		me4Phi[2] = me4b(BWPHI-1, 0); 
		me4Phi[3] = me4c(BWPHI-1, 0);

        CSCID[0] = 0;
        CSCID[1] = me1a(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI);
        CSCID[2] = me1b(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI);
        CSCID[3] = me1c(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI);
        CSCID[4] = me1d(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI);
        CSCID[5] = me1e(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI);
        CSCID[6] = me1f(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI);

		me1FR(0) = 0;
//DEA
		me1FR(1) = DecodeFR(me1a(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI), 0); // FR is derived from CSCid
		me1FR(2) = DecodeFR(me1b(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI), 1);
		me1FR(3) = DecodeFR(me1c(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI), 2);
		me1FR(4) = DecodeFR(me1d(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI), 3);
		me1FR(5) = DecodeFR(me1e(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI), 4);
		me1FR(6) = DecodeFR(me1f(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI), 5);


		IdValid(0) = ifelse (id4 != 0, 1, 0);
		IdValid(1) = ifelse (id3 != 0, 1, 0);
		IdValid(2) = ifelse (id2 != 0, 1, 0);
		IdValid(3) = ifelse (id1 != 0, 1, 0);

		etaPT = 
			ifelse (IdValid(2) == 1, me2Eta[id2], 
			ifelse (IdValid(1) == 1, me3Eta[id3], 0));

        // correct eta around boundary of ME1/1 and ME1/2, so no overlap
        // only 5 bits for this eta vs. 7 originally, 
        // So 14 = 56>>2, 13 = 55>>2
        etaPT = 
            ifelse (CSCID[id1] > 3 && etaPT >= 14, 13, 
            ifelse (CSCID[id1] < 4 && CSCID[id1] > 0 && etaPT < 14, 14, etaPT));

		// phi is taken only from key stations
		phi = 
			ifelse (IdValid(2) == 1, me2Phi[id2],
			ifelse (IdValid(1) == 1, me3Phi[id3], 0));

		FR = ifelse(id1 != 0, me1FR(id1), 0);

		SelPhi = SelectPhisp(IdValid);
		phiA = 
			ifelse (SelPhi(11) == 1, me1Phi[id1],
			ifelse (SelPhi(10) == 1, me2Phi[id2],
			ifelse (SelPhi(9)  == 1, me3Phi[id3],
			ifelse (SelPhi(8)  == 1, me4Phi[id4], 0))));
		phiB = 			   
			ifelse (SelPhi(7) == 1, me1Phi[id1],
			ifelse (SelPhi(6) == 1, me2Phi[id2],
			ifelse (SelPhi(5) == 1, me3Phi[id3],
			ifelse (SelPhi(4) == 1, me4Phi[id4], 0))));
		phiC = 			   
			ifelse (SelPhi(3) == 1, me1Phi[id1],
			ifelse (SelPhi(2) == 1, me2Phi[id2],
			ifelse (SelPhi(1) == 1, me3Phi[id3],
			ifelse (SelPhi(0) == 1, me4Phi[id4], 0))));

		a = ifelse (phiA >= phiB, phiA - phiB, phiB - phiA);
		b = ifelse (phiB >= phiC, phiB - phiC, phiC - phiB);

		d(11,0) = phiA - phiB;
		d(12) = ifelse (phiA >= phiB, 1, 0);

		c(11,0) = (b(7,4), a(8,1));
		c(12) = ((phiB >= phiA) || (phiB >= phiC)) && ((phiA >= phiB) || (phiC >= phiB));

		mode = Modep(rank);

		modeout = 
		  ifelse ((etaPT(BWPTETA-1,1) < 3) && ((mode == 2) || (mode == 3)), 6,  
		  ifelse ((etaPT(BWPTETA-1,1) < 3) && (mode == 4), 7, 
		  ifelse ((etaPT(BWPTETA-1,1) < 3) && (mode == 5), 8, mode)));

		// kill low-quality muons near sector boundary 3/5/04
		If 
		(
			(modeout == 5 || modeout == 8 || modeout == 9 || modeout == 10) && 
			(phi < PHICUTL || phi > PHICUTH)
		)
			modeout = 0;


		modenew = ifelse ((modeout >= 2) && (modeout <= 5), 1, 0);

		pt = ifelse (modenew == 0, d, c);
	
		si = ifelse ((((a(11,9) != 0) || (b(11,8) != 0)) && (modenew == 1)) || ((d(12,9) != 7) && (d(12,9) != 8) && (modeout > 5)), 1, 0);
	
		modeMem = ifelse (si == 0, modeout, 1);
	
		sign = (phiA >= phiB);

		ptp		  = pt		; 
		signp	  = sign	;
		modeMemp  = modeMem ;
		etaPTp	  = etaPT	;
		FRp		  = FR		;
		phip	  = phi	    ;
		orig_idrp = orig_id ;
		rankrp    = rank    ;
	end
endmodule
}


Signal SPvpp_SelectPhis::operator()(Signal IdValid)
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
				case1("4'b0001") begin EnableIdA = 1; EnableIdB = 0; EnableIdC = 0; end //    4
				case1("4'b0010") begin EnableIdA = 2; EnableIdB = 0; EnableIdC = 0; end //   3 
				case1("4'b0011") begin EnableIdA = 2; EnableIdB = 1; EnableIdC = 0; end //   34
				case1("4'b0100") begin EnableIdA = 4; EnableIdB = 0; EnableIdC = 0; end //  2  
				case1("4'b0101") begin EnableIdA = 4; EnableIdB = 1; EnableIdC = 0; end //  2 4
				case1("4'b0110") begin EnableIdA = 4; EnableIdB = 2; EnableIdC = 0; end //  23 
				case1("4'b0111") begin EnableIdA = 4; EnableIdB = 2; EnableIdC = 1; end //  234
				case1("4'b1000") begin EnableIdA = 8; EnableIdB = 0; EnableIdC = 0; end // 1   
				case1("4'b1001") begin EnableIdA = 8; EnableIdB = 1; EnableIdC = 0; end // 1  4
				case1("4'b1010") begin EnableIdA = 8; EnableIdB = 2; EnableIdC = 0; end // 1 3 
				case1("4'b1011") begin EnableIdA = 8; EnableIdB = 2; EnableIdC = 1; end // 1 34
				case1("4'b1100") begin EnableIdA = 8; EnableIdB = 4; EnableIdC = 0; end // 12  
				case1("4'b1101") begin EnableIdA = 8; EnableIdB = 4; EnableIdC = 1; end // 12 4
				case1("4'b1110") begin EnableIdA = 8; EnableIdB = 4; EnableIdC = 2; end // 123 
				case1("4'b1111") begin EnableIdA = 8; EnableIdB = 4; EnableIdC = 2; end // 1234
			endcase
			result = (EnableIdA, EnableIdB, EnableIdC);
		end
	endfunction
}

Signal SPvpp_Mode::operator()(Signal rank)
{
	initio
		rank.input(5,0,"rank");
	beginfunction
		begin
			begincase (rank)
				case1("6'd00")					 result = 0;
				case3("6'h12", "6'h17", "6'h1c") result = 2;
				case3("6'h1f", "6'h21", "6'h23") result = 2;
				case3("6'h11", "6'h16", "6'h1b") result = 3;
				case3("6'h10", "6'h15", "6'h1a") result = 4;
				case1("6'd04") 					 result = 5;
				case3("6'h06", "6'h0b", "6'h0e") result = 6;
				case3("6'h05", "6'h0a", "6'h0d") result = 7;
				case1("6'd03") 					 result = 8;
				case1("6'd02") 					 result = 9;
				case1("6'd01") 					 result = "4'ha";
				Default							 result = 0;
			endcase
		end
	endfunction
}

Signal SPvpp_DecodeFR::operator()(Signal CSCid, Signal stubn)
{
initio
	CSCid.input(BWCSCID-1, 0, "CSCid");
	stubn.input(2, 0, "stubn");
beginfunction
	begin
		// correct ME11 geometry used according to Darin (4/13/07)
		If (stubn < 3)
			result = ifelse (CSCid == 2 || CSCid == 4 || CSCid == 6, 1, 0);
		Else
			result = ifelse (CSCid == 1 || CSCid == 3 || CSCid == 5, 1, 0);
	end
endfunction
}
