#include <L1Trigger/CSCTrackFinder/src/SPvpp_MuonMux.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>

void SPvpp_MuonMux::operator()
(
	Signal m0, Signal m1, Signal m2,
	Signal pt0, Signal sign0, Signal modeMem0, Signal etaPT0, Signal FR0, Signal phi0, Signal rank0,
	Signal pt1, Signal sign1, Signal modeMem1, Signal etaPT1, Signal FR1, Signal phi1, Signal rank1,
	Signal pt2, Signal sign2, Signal modeMem2, Signal etaPT2, Signal FR2, Signal phi2, Signal rank2,
	Signal pt3, Signal sign3, Signal modeMem3, Signal etaPT3, Signal FR3, Signal phi3, Signal rank3,
	Signal pt4, Signal sign4, Signal modeMem4, Signal etaPT4, Signal FR4, Signal phi4, Signal rank4,
	Signal pt5, Signal sign5, Signal modeMem5, Signal etaPT5, Signal FR5, Signal phi5, Signal rank5,
	Signal pt6, Signal sign6, Signal modeMem6, Signal etaPT6, Signal FR6, Signal phi6, Signal rank6,
	Signal pt7, Signal sign7, Signal modeMem7, Signal etaPT7, Signal FR7, Signal phi7, Signal rank7,
	Signal pt8, Signal sign8, Signal modeMem8, Signal etaPT8, Signal FR8, Signal phi8, Signal rank8,
																					  		  		
	Signal id0, Signal id1, Signal id2, Signal id3, Signal id4, Signal id5,			  		  		
	Signal id6, Signal id7, Signal id8,												  		  		
																					  		  		
	Signal ptH, Signal signH, Signal modeMemH, Signal etaPTH, Signal FRH, Signal phiH, Signal rankH, 
	Signal ptM, Signal signM, Signal modeMemM, Signal etaPTM, Signal FRM, Signal phiM, Signal rankM,
	Signal ptL, Signal signL, Signal modeMemL, Signal etaPTL, Signal FRL, Signal phiL, Signal rankL,
	Signal idH, Signal idM, Signal idL
)

{
initio

	m0.input(8,0,"m0"); 
	m1.input(8,0,"m1"); 
	m2.input(8,0,"m2");
	
	pt0.input(BWPT-1,0,"pt0"); sign0.input("sign0"); modeMem0.input(BWMODE-1,0,"modeMem0"); etaPT0.input(BWETAOUT-1,0,"etaPT0"); FR0.input("FR0"); phi0.input(BWPHI-1,0,"phi0"); Input_(rank0, BWRANK-1, 0);
	pt1.input(BWPT-1,0,"pt1"); sign1.input("sign1"); modeMem1.input(BWMODE-1,0,"modeMem1"); etaPT1.input(BWETAOUT-1,0,"etaPT1"); FR1.input("FR1"); phi1.input(BWPHI-1,0,"phi1"); Input_(rank1, BWRANK-1, 0);
	pt2.input(BWPT-1,0,"pt2"); sign2.input("sign2"); modeMem2.input(BWMODE-1,0,"modeMem2"); etaPT2.input(BWETAOUT-1,0,"etaPT2"); FR2.input("FR2"); phi2.input(BWPHI-1,0,"phi2"); Input_(rank2, BWRANK-1, 0);
	pt3.input(BWPT-1,0,"pt3"); sign3.input("sign3"); modeMem3.input(BWMODE-1,0,"modeMem3"); etaPT3.input(BWETAOUT-1,0,"etaPT3"); FR3.input("FR3"); phi3.input(BWPHI-1,0,"phi3"); Input_(rank3, BWRANK-1, 0);
	pt4.input(BWPT-1,0,"pt4"); sign4.input("sign4"); modeMem4.input(BWMODE-1,0,"modeMem4"); etaPT4.input(BWETAOUT-1,0,"etaPT4"); FR4.input("FR4"); phi4.input(BWPHI-1,0,"phi4"); Input_(rank4, BWRANK-1, 0);
	pt5.input(BWPT-1,0,"pt5"); sign5.input("sign5"); modeMem5.input(BWMODE-1,0,"modeMem5"); etaPT5.input(BWETAOUT-1,0,"etaPT5"); FR5.input("FR5"); phi5.input(BWPHI-1,0,"phi5"); Input_(rank5, BWRANK-1, 0);
	pt6.input(BWPT-1,0,"pt6"); sign6.input("sign6"); modeMem6.input(BWMODE-1,0,"modeMem6"); etaPT6.input(BWETAOUT-1,0,"etaPT6"); FR6.input("FR6"); phi6.input(BWPHI-1,0,"phi6"); Input_(rank6, BWRANK-1, 0);
	pt7.input(BWPT-1,0,"pt7"); sign7.input("sign7"); modeMem7.input(BWMODE-1,0,"modeMem7"); etaPT7.input(BWETAOUT-1,0,"etaPT7"); FR7.input("FR7"); phi7.input(BWPHI-1,0,"phi7"); Input_(rank7, BWRANK-1, 0);
	pt8.input(BWPT-1,0,"pt8"); sign8.input("sign8"); modeMem8.input(BWMODE-1,0,"modeMem8"); etaPT8.input(BWETAOUT-1,0,"etaPT8"); FR8.input("FR8"); phi8.input(BWPHI-1,0,"phi8"); Input_(rank8, BWRANK-1, 0);

	id0.input(MUIDSIZE - 1,0,"id0");
	id1.input(MUIDSIZE - 1,0,"id1");
	id2.input(MUIDSIZE - 1,0,"id2");
	id3.input(MUIDSIZE - 1,0,"id3");
	id4.input(MUIDSIZE - 1,0,"id4");
	id5.input(MUIDSIZE - 1,0,"id5");
	id6.input(MUIDSIZE - 1,0,"id6");
	id7.input(MUIDSIZE - 1,0,"id7");
	id8.input(MUIDSIZE - 1,0,"id8");

	ptH.output(BWPT-1,0,"ptH",makereg); signH.output("signH",makereg); modeMemH.output(BWMODE-1,0,"modeMemH",makereg); etaPTH.output(BWETAOUT-1,0,"etaPTH",makereg); FRH.output("FRH",makereg); phiH.output(BWPHIOUT-1,0,"phiH",makereg); OutReg_(rankH, BWRANK-1, 0);
	ptM.output(BWPT-1,0,"ptM",makereg); signM.output("signM",makereg); modeMemM.output(BWMODE-1,0,"modeMemM",makereg); etaPTM.output(BWETAOUT-1,0,"etaPTM",makereg); FRM.output("FRM",makereg); phiM.output(BWPHIOUT-1,0,"phiM",makereg); OutReg_(rankM, BWRANK-1, 0);
	ptL.output(BWPT-1,0,"ptL",makereg); signL.output("signL",makereg); modeMemL.output(BWMODE-1,0,"modeMemL",makereg); etaPTL.output(BWETAOUT-1,0,"etaPTL",makereg); FRL.output("FRL",makereg); phiL.output(BWPHIOUT-1,0,"phiL",makereg); OutReg_(rankL, BWRANK-1, 0);

	idH.output(MUIDSIZE - 1, 0, "idH", makereg);
	idM.output(MUIDSIZE - 1, 0, "idM", makereg);
	idL.output(MUIDSIZE - 1, 0, "idL", makereg);

beginmodule
	
	ScalePhi.init(BWPHIOUT-1,0,"_ScalePhi");
	pt.reg(BWPT-1,0,8,0,"pt");
	sign.reg(8,0,"sign");
	modeMem.reg(BWMODE-1,0,8,0,"modeMem");
	etaPT.reg(BWETAOUT-1,0,8,0,"etaPT");
	FR.reg(8, 0, "FR");
	phi.reg(BWPHI-1, 0, 8, 0, "phi");
	id.reg(MUIDSIZE-1, 0, 8, 0, "id");
	phiHs.reg(BWPHI-1,0,"phiHs");
	phiMs.reg(BWPHI-1,0,"phiMs");
	phiLs.reg(BWPHI-1,0,"phiLs");
	Reg__(rank, BWRANK-1, 0, 8, 0);

	i.reg(3, 0, "i");
	
modulebody

	always 
	(
		m0 or m1 or m2 or
	
		pt0 or sign0 or modeMem0 or etaPT0 or FR0 or phi0 or rank0 or
		pt1 or sign1 or modeMem1 or etaPT1 or FR1 or phi1 or rank1 or
		pt2 or sign2 or modeMem2 or etaPT2 or FR2 or phi2 or rank2 or
		pt3 or sign3 or modeMem3 or etaPT3 or FR3 or phi3 or rank3 or
		pt4 or sign4 or modeMem4 or etaPT4 or FR4 or phi4 or rank4 or
		pt5 or sign5 or modeMem5 or etaPT5 or FR5 or phi5 or rank5 or
		pt6 or sign6 or modeMem6 or etaPT6 or FR6 or phi6 or rank6 or
		pt7 or sign7 or modeMem7 or etaPT7 or FR7 or phi7 or rank7 or
		pt8 or sign8 or modeMem8 or etaPT8 or FR8 or phi8 or rank8 or
		id0 or id1 or id2 or id3 or id4 or id5 or id6 or id7 or id8
	)
	begin
		//Place parameters into arrays for easier access
		pt[0] = pt0; sign(0) = sign0; modeMem[0] = modeMem0; etaPT[0] = etaPT0; FR(0) = FR0; phi[0] = phi0;
		pt[1] = pt1; sign(1) = sign1; modeMem[1] = modeMem1; etaPT[1] = etaPT1;	FR(1) = FR1; phi[1] = phi1;
		pt[2] = pt2; sign(2) = sign2; modeMem[2] = modeMem2; etaPT[2] = etaPT2;	FR(2) = FR2; phi[2] = phi2;
		pt[3] = pt3; sign(3) = sign3; modeMem[3] = modeMem3; etaPT[3] = etaPT3;	FR(3) = FR3; phi[3] = phi3;
		pt[4] = pt4; sign(4) = sign4; modeMem[4] = modeMem4; etaPT[4] = etaPT4;	FR(4) = FR4; phi[4] = phi4;
		pt[5] = pt5; sign(5) = sign5; modeMem[5] = modeMem5; etaPT[5] = etaPT5;	FR(5) = FR5; phi[5] = phi5;
		pt[6] = pt6; sign(6) = sign6; modeMem[6] = modeMem6; etaPT[6] = etaPT6;	FR(6) = FR6; phi[6] = phi6;
		pt[7] = pt7; sign(7) = sign7; modeMem[7] = modeMem7; etaPT[7] = etaPT7;	FR(7) = FR7; phi[7] = phi7;
		pt[8] = pt8; sign(8) = sign8; modeMem[8] = modeMem8; etaPT[8] = etaPT8;	FR(8) = FR8; phi[8] = phi8;

		rank[0] = rank0;
		rank[1] = rank1;
		rank[2] = rank2;
		rank[3] = rank3;
		rank[4] = rank4;
		rank[5] = rank5;
		rank[6] = rank6;
		rank[7] = rank7;
		rank[8] = rank8;

		id[0] = id0; id[1] = id1; id[2] = id2;
		id[3] = id3; id[4] = id4; id[5] = id5;
		id[6] = id6; id[7] = id7; id[8] = id8;
		
		rankH		 = 0;			
		rankM		 = 0;
		rankL		 = 0;

		ptH		 = 0;			
		ptM		 = 0;
		ptL		 = 0;
		
		signH	 = 0;
		signM	 = 0;
		signL	 = 0;
			
		modeMemH = 0;
		modeMemM = 0;
		modeMemL = 0;
			
		etaPTH	 = 0;
		etaPTM	 = 0;
		etaPTL	 = 0;
		
		FRH		 = 0;			
		FRM		 = 0;
		FRL		 = 0;

		phiHs	 = 0;			
		phiMs	 = 0;
		phiLs	 = 0;

		idH		 = 0;
		idM		 = 0;
		idL		 = 0;

		//Loop over params and mux out best ones according to mx's
		For (i = 0, i < 9, i++)
		begin
			
			rankH	 = rankH	| ifelse(m0(i) == 1, rank[i], 0);
			rankM	 = rankM	| ifelse(m1(i) == 1, rank[i], 0);
			rankL	 = rankL	| ifelse(m2(i) == 1, rank[i], 0);

			ptH		 = ptH		| ifelse(m0(i) == 1, pt[i], 0);
			ptM		 = ptM		| ifelse(m1(i) == 1, pt[i], 0);
			ptL		 = ptL		| ifelse(m2(i) == 1, pt[i], 0);
			                   
			signH	 = signH	| ifelse(m0(i) == 1, sign(i), 0);
			signM	 = signM	| ifelse(m1(i) == 1, sign(i), 0);
			signL	 = signL	| ifelse(m2(i) == 1, sign(i), 0);
				       	    
			modeMemH = modeMemH | ifelse(m0(i) == 1, modeMem[i], 0);
			modeMemM = modeMemM | ifelse(m1(i) == 1, modeMem[i], 0);
			modeMemL = modeMemL | ifelse(m2(i) == 1, modeMem[i], 0);
				       	    
			etaPTH	 = etaPTH	| ifelse(m0(i) == 1, etaPT[i], 0);
			etaPTM	 = etaPTM	| ifelse(m1(i) == 1, etaPT[i], 0);
			etaPTL	 = etaPTL	| ifelse(m2(i) == 1, etaPT[i], 0);

			FRH		 = FRH		| ifelse(m0(i) == 1, FR(i), 0);
			FRM		 = FRM		| ifelse(m1(i) == 1, FR(i), 0);
			FRL		 = FRL		| ifelse(m2(i) == 1, FR(i), 0);
			                   
			phiHs	 = phiHs	| ifelse(m0(i) == 1, phi[i], 0);
			phiMs	 = phiMs	| ifelse(m1(i) == 1, phi[i], 0);
			phiLs	 = phiLs	| ifelse(m2(i) == 1, phi[i], 0);

			idH		 = idH		| ifelse(m0(i) == 1, id[i], 0);
			idM		 = idM		| ifelse(m1(i) == 1, id[i], 0);
			idL		 = idL		| ifelse(m2(i) == 1, id[i], 0);

		end

		phiH = ScalePhi(phiHs);
		phiM = ScalePhi(phiMs);
		phiL = ScalePhi(phiLs);

	end
endmodule
}


#define ScalePhi result = (i * 24 / 128)
// 360 / 60 (one sector) / 2.5 (phi precision in degrees) = 24
// Phi lost 5 LSBs, 7 bist left, so it can have 128 combinations
char * SPvpp_ScalePhi::itoh7(int i)
{
	sprintf (h7, "7'h%02x", i);
	return h7;
}

Signal SPvpp_ScalePhi::operator()(Signal phi)
{
initio
	phi.input(BWPHI-1,0,"phi");
beginfunction
	begin
		int i = 0;
		result = 0;
		// this arm-twisting code below actually simulates and generates the case statement, 
		// which during Verilog synthesis gets implemented as ROM.
		begincase(phi(BWPHI-1, BWPHI-BWPHISCALE))

			case1(itoh7(  i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;


			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;

			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
			case1(itoh7(++i)) ScalePhi;
		endcase
	end
endfunction
}

