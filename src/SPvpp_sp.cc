#include <L1Trigger/CSCTrackFinder/src/SPvpp_sp.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>
#include <time.h>



void SPvpp_sp::operator()
(
	Signal me1ap, Signal me1bp, Signal me1cp, Signal me1dp, Signal me1ep, Signal me1fp,
	Signal me2ap, Signal me2bp, Signal me2cp,
	Signal me3ap, Signal me3bp, Signal me3cp,
	Signal me4ap, Signal me4bp, Signal me4cp,
	Signal mb1ap, Signal mb1bp, 
	Signal pHp,  Signal pMp,  Signal pLp,
	Signal idHp, Signal idMp, Signal idLp,
	Signal date,
	Signal mneta0, Signal mneta1, Signal mneta2, Signal mneta3, Signal mneta4, Signal mneta5, Signal mneta6, Signal mneta7, 
	Signal mxeta0, Signal mxeta1, Signal mxeta2, Signal mxeta3, Signal mxeta4, Signal mxeta5, Signal mxeta6, Signal mxeta7, 
	Signal etawn0, Signal etawn1, Signal etawn2, Signal etawn3, Signal etawn4, Signal etawn5, 
	Signal mindphi,
	Signal mindeta_acc, Signal maxdeta_acc, Signal maxdphi_acc,
	Signal control,
	Signal clkp
)

{
initio
	me1ap.input(BWMEIN-1,0,"me1ap"); // {CSCid[3:0], q[3:0], /*am,*/ eta[5:0], phi[11:0]}
	me1bp.input(BWMEIN-1,0,"me1bp"); 
	me1cp.input(BWMEIN-1,0,"me1cp"); 
	me1dp.input(BWMEIN-1,0,"me1dp"); 
	me1ep.input(BWMEIN-1,0,"me1ep"); 
	me1fp.input(BWMEIN-1,0,"me1fp"); 
							   
	me2ap.input(BWMEIN-1,0,"me2ap"); 
	me2bp.input(BWMEIN-1,0,"me2bp"); 
	me2cp.input(BWMEIN-1,0,"me2cp"); 
							   
	me3ap.input(BWMEIN-1,0,"me3ap"); 
	me3bp.input(BWMEIN-1,0,"me3bp"); 
	me3cp.input(BWMEIN-1,0,"me3cp"); 
							   
	me4ap.input(BWMEIN-1,0,"me4ap"); 
	me4bp.input(BWMEIN-1,0,"me4bp"); 
	me4cp.input(BWMEIN-1,0,"me4cp"); 

	Input_(mb1ap, BWMBIN-1,0); // {FL, q[2:0], phi[11:0]}
	Input_(mb1bp, BWMBIN-1,0);

	Output_(idHp, MUIDSIZE-1, 0);
	Output_(idMp, MUIDSIZE-1, 0);
	Output_(idLp, MUIDSIZE-1, 0);

	Output_(pHp, BWPOUT-1,0); // {FR, phi[11:0], pt[12:0], sign, mode[3:0], eta[3:0]}
	Output_(pMp, BWPOUT-1,0);
	Output_(pLp, BWPOUT-1,0);

	Output_(date, 15,0);

	Input_(mneta0, BWETAIN-1, 0); 
	Input_(mneta1, BWETAIN-1, 0); 
	Input_(mneta2, BWETAIN-1, 0); 
	Input_(mneta3, BWETAIN-1, 0); 
	Input_(mneta4, BWETAIN-1, 0); 
	Input_(mneta5, BWETAIN-1, 0); 
	Input_(mneta6, BWETAIN-1, 0); 
	Input_(mneta7, BWETAIN-1, 0); 
		   		 					  
	Input_(mxeta0, BWETAIN-1, 0); 
	Input_(mxeta1, BWETAIN-1, 0); 
	Input_(mxeta2, BWETAIN-1, 0); 
	Input_(mxeta3, BWETAIN-1, 0); 
	Input_(mxeta4, BWETAIN-1, 0); 
	Input_(mxeta5, BWETAIN-1, 0); 
	Input_(mxeta6, BWETAIN-1, 0); 
	Input_(mxeta7, BWETAIN-1, 0); 
		   				 
	Input_(etawn0, BWETAIN, 0); 
	Input_(etawn1, BWETAIN, 0); 
	Input_(etawn2, BWETAIN, 0); 
	Input_(etawn3, BWETAIN, 0); 
	Input_(etawn4, BWETAIN, 0); 
	Input_(etawn5, BWETAIN, 0); 

	Input_(mindphi, BWPHI-1, 0);
	Input_(mindeta_acc, BWETAIN-1,0); // min eta difference for acc tracks
	Input_(maxdeta_acc, BWETAIN-1,0); // max eta difference for acc tracks
	Input_(maxdphi_acc, BWPHI-3,0);   // max phi difference for acc tracks (without 2 lower bits)

	Input_(control, 15, 0); // control register {reserved[14:0], BXA_enable}

	clkp.input("clkp");

	
beginmodule

	int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, i, j;
        int mi;

	// initializing modules

  	ptu2a.init("ptme","ptu2a");
	ptu2b.init("ptme","ptu2b");
	ptu2c.init("ptme","ptu2c");

	ptu3a.init("ptme","ptu3a");
	ptu3b.init("ptme","ptu3b");
	ptu3c.init("ptme","ptu3c");

	ptub2a.init("ptmb","ptub2a");
	ptub2b.init("ptmb","ptub2b");
	ptub2c.init("ptmb","ptub2c");
	
	fsuv.init("fsu","fsuv");

	mux.init("MuonMux","mux");
	bxa.init("bxa", "bxa_");
	dtbx[0].init("dtbx", "dtbx_0");
	dtbx[1].init("dtbx", "dtbx_1");
	bxcorr.init("bxcorr", "bxcorrect");

// init internal variables------------------------------------------
	for (mi = 0; mi < NSEG1; mi++) 
		me1[mi].wire(BWMEIN-1, 0, "me1_", mi);
	
	for (mi = 0; mi < NSEG234; mi++)
	{
		me2[mi].wire(BWMEIN-1, 0, "me2_", mi);
		me3[mi].wire(BWMEIN-1, 0, "me3_", mi);
		me4[mi].wire(BWMEIN-1, 0, "me4_", mi);
	}
	for (mi = 0; mi < NSEG12B; mi++)
	{
		mb1[mi].wire(BWMBIN-1, 0, "mb1_", mi); 
		mb2[mi].wire(BWMBIN-1, 0, "mb2_", mi); 
	}
	Wire__(dmb1, BWMBIN-1, 0, NSEG12B-1, 0);

	me1r.reg(BWMEIN-1, 0, 5, 0, "me1r");
	me2r.reg(BWMEIN-1, 0, 2, 0, "me2r");
	me3r.reg(BWMEIN-1, 0, 2, 0, "me3r");
	me4r.reg(BWMEIN-1, 0, 2, 0, "me4r");

	mb1r.reg(BWMBIN-1, 0, 3, 0, "mb1r"); 
	mb2r.reg(BWMBIN-1, 0, 3, 0, "mb2r"); 

	me1rr.reg(BWMEIN-1, 0, 5, 0, "me1rr");
	me2rr.reg(BWMEIN-1, 0, 2, 0, "me2rr");
	me3rr.reg(BWMEIN-1, 0, 2, 0, "me3rr");
	me4rr.reg(BWMEIN-1, 0, 2, 0, "me4rr");

	mb1rr.reg(BWMBIN-1, 0, 3, 0, "mb1rr"); 
	mb2rr.reg(BWMBIN-1, 0, 3, 0, "mb2rr"); 

	Wire__(MinEta, BWETAIN-1, 0, 7, 0); 
	Wire__(MaxEta, BWETAIN-1, 0, 7, 0); 
	Wire__(EtaWindow, BWETAIN, 0, 5, 0);
	
	Wire__(me1bi, BWBXID-1, 0, NSEG1, 0); // original bx and id of the track 
	Wire__(me2bi, BWBXID-1, 0, NSEG234, 0); // number of elements for each station is +1 because stub IDs start from 1
	Wire__(me3bi, BWBXID-1, 0, NSEG234, 0);
	Wire__(me4bi, BWBXID-1, 0, NSEG234, 0);
	Wire__(mb1bi, BWBXID-1, 0, NSEG12B, 0);
	Wire__(mb2bi, BWBXID-1, 0, NSEG12B, 0);

	Reg__(me1bir, BWBXID-1, 0, NSEG1, 0);
	Reg__(me2bir, BWBXID-1, 0, NSEG234, 0);
	Reg__(me3bir, BWBXID-1, 0, NSEG234, 0);
	Reg__(me4bir, BWBXID-1, 0, NSEG234, 0);
	Reg__(mb1bir, BWBXID-1, 0, NSEG12B, 0);
	Reg__(mb2bir, BWBXID-1, 0, NSEG12B, 0);

// wires --------------------------------------------------

	pass12.wire  (BWPASS12-1, 0, "pass12");
	pass12ov.wire  (BWPASS12-1, 0, "pass12ov");
	Wire_(pass13, BWPASS12-1, 0);

	Eqme12.wire  (BWEQ12R-1, 0, "Eqme12");
	Eqme13.wire  (BWEQ12R-1, 0, "Eqme13");	
	Eqme12ov.wire(BWEQ12OVR-1, 0, "Eqme12ov");
	Eqme23.wire  (BWEQ234R-1, 0, "Eqme23");
	Eqme24.wire  (BWEQ234R-1, 0, "Eqme24");
	Eqme34.wire  (BWEQ234R-1, 0, "Eqme34"); 
	Eq2b1.wire   (BWEQ2B1R-1, 0, "Eq2b1");
	Eq2b2.wire   (BWEQ2B2R-1, 0, "Eq2b2");

	Wire_(Eqme23a, BWEQ234R-1, 0); // accelerator tracks extrapolation results

	u2aIdr.reg (MUIDSIZE-1,0,"u2aIdr");  Reg_(u2aIdrr , MUIDSIZE-1,0); Reg_(u2aIdrrr , MUIDSIZE-1,0); Reg_(u2aId , MUIDSIZE-1,0); Wire_(u2aIdt , MUIDSIZE-1,0);
	u2bIdr.reg (MUIDSIZE-1,0,"u2bIdr");  Reg_(u2bIdrr , MUIDSIZE-1,0); Reg_(u2bIdrrr , MUIDSIZE-1,0); Reg_(u2bId , MUIDSIZE-1,0); Wire_(u2bIdt , MUIDSIZE-1,0);
	u2cIdr.reg (MUIDSIZE-1,0,"u2cIdr");  Reg_(u2cIdrr , MUIDSIZE-1,0); Reg_(u2cIdrrr , MUIDSIZE-1,0); Reg_(u2cId , MUIDSIZE-1,0); Wire_(u2cIdt , MUIDSIZE-1,0);
		   	   			  				 	  	   	   		  		   	  	   	   		  		   	  	   	 		  		   	   	 		  		  
	u3aIdr.reg (MUIDSIZE-1,0,"u3aIdr");  Reg_(u3aIdrr , MUIDSIZE-1,0); Reg_(u3aIdrrr , MUIDSIZE-1,0); Reg_(u3aId , MUIDSIZE-1,0); Wire_(u3aIdt , MUIDSIZE-1,0);
	u3bIdr.reg (MUIDSIZE-1,0,"u3bIdr");  Reg_(u3bIdrr , MUIDSIZE-1,0); Reg_(u3bIdrrr , MUIDSIZE-1,0); Reg_(u3bId , MUIDSIZE-1,0); Wire_(u3bIdt , MUIDSIZE-1,0);
	u3cIdr.reg (MUIDSIZE-1,0,"u3cIdr");  Reg_(u3cIdrr , MUIDSIZE-1,0); Reg_(u3cIdrrr , MUIDSIZE-1,0); Reg_(u3cId , MUIDSIZE-1,0); Wire_(u3cIdt , MUIDSIZE-1,0);
		   	   			  				 	  	   	   		  		   	  	   	   		  		   	  	   	   		  		   	   	   		  		  
	ub2aIdr.reg(MUIDSIZE-1,0,"ub2aIdr"); Reg_(ub2aIdrr, MUIDSIZE-1,0); Reg_(ub2aIdrrr, MUIDSIZE-1,0); Reg_(ub2aId, MUIDSIZE-1,0); Wire_(ub2aIdt, MUIDSIZE-1,0);
	ub2bIdr.reg(MUIDSIZE-1,0,"ub2bIdr"); Reg_(ub2bIdrr, MUIDSIZE-1,0); Reg_(ub2bIdrrr, MUIDSIZE-1,0); Reg_(ub2bId, MUIDSIZE-1,0); Wire_(ub2bIdt, MUIDSIZE-1,0);
	ub2cIdr.reg(MUIDSIZE-1,0,"ub2cIdr"); Reg_(ub2cIdrr, MUIDSIZE-1,0); Reg_(ub2cIdrrr, MUIDSIZE-1,0); Reg_(ub2cId, MUIDSIZE-1,0); Wire_(ub2cIdt, MUIDSIZE-1,0);

	
	idH.wire(MUIDSIZE-1, 0, "idH");
	idM.wire(MUIDSIZE-1, 0, "idM");
	idL.wire(MUIDSIZE-1, 0, "idL");

	for (i = 0; i < NTAU; i++)
	{
		me2Id1[i].wire (2, 0, "me2Id1", i);  
		me3Id1[i].wire (2, 0, "me3Id1", i);  
		mb2idb1[i].wire(2, 0, "mb2idb1", i);
		me2Id3[i].wire (1, 0, "me2Id3", i);  
		me3Id2[i].wire (1, 0, "me3Id2", i);  
		mb2idb2[i].wire(2, 0, "mb2idb2", i);
		me2Id4[i].wire (1, 0, "me2Id4", i); 
		me3Id4[i].wire (1, 0, "me3Id4", i);                   
		mb2id1[i].wire (2, 0, "mb2id1", i); 
		
		me2Rank[i].wire(5, 0, "me2Rank", i);
		me3Rank[i].wire(5, 0, "me3Rank", i);
		mb2rank[i].wire(5, 0, "mb2rank", i);                 
	}

	Reg__(me2Id1r ,2, 0, NTAU-1, 0); Reg__(me2Id1rr ,2, 0, NTAU-1, 0);
	Reg__(me3Id1r ,2, 0, NTAU-1, 0); Reg__(me3Id1rr ,2, 0, NTAU-1, 0);
	Reg__(mb2idb1r,2, 0, NTAU-1, 0); Reg__(mb2idb1rr,2, 0, NTAU-1, 0);
	Reg__(me2Id3r ,1, 0, NTAU-1, 0); Reg__(me2Id3rr ,1, 0, NTAU-1, 0);
	Reg__(me3Id2r ,1, 0, NTAU-1, 0); Reg__(me3Id2rr ,1, 0, NTAU-1, 0);
	Reg__(mb2idb2r,2, 0, NTAU-1, 0); Reg__(mb2idb2rr,2, 0, NTAU-1, 0);
	Reg__(me2Id4r ,1, 0, NTAU-1, 0); Reg__(me2Id4rr ,1, 0, NTAU-1, 0);
	Reg__(me3Id4r ,1, 0, NTAU-1, 0); Reg__(me3Id4rr ,1, 0, NTAU-1, 0);
	Reg__(mb2id1r ,2, 0, NTAU-1, 0); Reg__(mb2id1rr ,2, 0, NTAU-1, 0);

	Reg__(me2Rankr,5, 0, NTAU-1, 0); Wire__(me2Rankrr,5, 0, NTAU-1, 0);
	Reg__(me3Rankr,5, 0, NTAU-1, 0); Wire__(me3Rankrr,5, 0, NTAU-1, 0);
	Reg__(mb2rankr,5, 0, NTAU-1, 0); Wire__(mb2rankrr,5, 0, NTAU-1, 0);

	Reg__(me2Rankrrr,5, 0, NTAU-1, 0); Reg__(me2Rankrrrr,5, 0, NTAU-1, 0); Reg__(me2Rankrrrrr,5, 0, NTAU-1, 0);
	Reg__(me3Rankrrr,5, 0, NTAU-1, 0); Reg__(me3Rankrrrr,5, 0, NTAU-1, 0); Reg__(me3Rankrrrrr,5, 0, NTAU-1, 0);
	Reg__(mb2rankrrr,5, 0, NTAU-1, 0); Reg__(mb2rankrrrr,5, 0, NTAU-1, 0); Reg__(mb2rankrrrrr,5, 0, NTAU-1, 0);

	Wire_(rankH, BWRANK-1, 0);
	Wire_(rankM, BWRANK-1, 0);
	Wire_(rankL, BWRANK-1, 0);
	
	pt2a.wire(BWPT-1,0,"pt2a"); 
	pt2b.wire(BWPT-1,0,"pt2b"); 
	pt2c.wire(BWPT-1,0,"pt2c");

	pt3a.wire(BWPT-1,0,"pt3a"); 
	pt3b.wire(BWPT-1,0,"pt3b"); 
	pt3c.wire(BWPT-1,0,"pt3c");

	ptb2a.wire(BWPT-1,0,"ptb2a"); 
	ptb2b.wire(BWPT-1,0,"ptb2b"); 
	ptb2c.wire(BWPT-1,0,"ptb2c");

	sign2a.wire("sign2a"); 
	sign2b.wire("sign2b"); 
	sign2c.wire("sign2c"); 

	sign3a.wire("sign3a"); 
	sign3b.wire("sign3b"); 
	sign3c.wire("sign3c");
	
	signb2a.wire("signb2a"); 
	signb2b.wire("signb2b"); 
	signb2c.wire("signb2c");

	mode2a.wire(BWMODE-1,0,"mode2a"); 
	mode2b.wire(BWMODE-1,0,"mode2b"); 
	mode2c.wire(BWMODE-1,0,"mode2c");

	mode3a.wire(BWMODE-1,0,"mode3a"); 
	mode3b.wire(BWMODE-1,0,"mode3b"); 
	mode3c.wire(BWMODE-1,0,"mode3c");

	modeb2a.wire(BWMODE-1,0,"modeb2a"); 
	modeb2b.wire(BWMODE-1,0,"modeb2b"); 
	modeb2c.wire(BWMODE-1,0,"modeb2c");

	etaPT2a.wire(BWETAOUT-1,0,"etaPT2a"); 
	etaPT2b.wire(BWETAOUT-1,0,"etaPT2b"); 
	etaPT2c.wire(BWETAOUT-1,0,"etaPT2c"); 

	etaPT3a.wire(BWETAOUT-1,0,"etaPT3a"); 
	etaPT3b.wire(BWETAOUT-1,0,"etaPT3b"); 
	etaPT3c.wire(BWETAOUT-1,0,"etaPT3c"); 

	etaPTb2a.wire(BWETAOUT-1,0,"etaPTb2a"); 
	etaPTb2b.wire(BWETAOUT-1,0,"etaPTb2b"); 
	etaPTb2c.wire(BWETAOUT-1,0,"etaPTb2c"); 

	FR2a.wire("FR2a"); 
	FR2b.wire("FR2b"); 
	FR2c.wire("FR2c");
	      
	FR3a.wire("FR3a"); 
	FR3b.wire("FR3b"); 
	FR3c.wire("FR3c");
	      
	FRb2a.wire("FRb2a"); 
	FRb2b.wire("FRb2b"); 
	FRb2c.wire("FRb2c");
	      
	phi2a.wire(BWPHI-1,0,"phi2a"); 
	phi2b.wire(BWPHI-1,0,"phi2b"); 
	phi2c.wire(BWPHI-1,0,"phi2c");
	      
	phi3a.wire(BWPHI-1,0,"phi3a"); 
	phi3b.wire(BWPHI-1,0,"phi3b"); 
	phi3c.wire(BWPHI-1,0,"phi3c");
	      
	phib2a.wire(BWPHI-1,0,"phib2a"); 
	phib2b.wire(BWPHI-1,0,"phib2b"); 
	phib2c.wire(BWPHI-1,0,"phib2c");

	ptH.wire(BWPT-1,0,"ptH"); 
	ptM.wire(BWPT-1,0,"ptM"); 
	ptL.wire(BWPT-1,0,"ptL");
	
	signH.wire("signH"); 
	signM.wire("signM"); 
	signL.wire("signL"); 

	modeMemH.wire(BWMODE-1,0,"modeMemH"); 
	modeMemM.wire(BWMODE-1,0,"modeMemM"); 
	modeMemL.wire(BWMODE-1,0,"modeMemL"); 

	etaPTH.wire(BWETAOUT-1,0,"etaPTH"); 
	etaPTM.wire(BWETAOUT-1,0,"etaPTM"); 
	etaPTL.wire(BWETAOUT-1,0,"etaPTL"); 

	m0.wire(8,0,"m0"); 
	m1.wire(8,0,"m1"); 
	m2.wire(8,0,"m2"); 

	FRH.wire("FRH"); 
	FRM.wire("FRM");  
	FRL.wire("FRL");  

	phiH.wire(BWPHIOUT-1, 0, "phiH");
	phiM.wire(BWPHIOUT-1, 0, "phiM");
	phiL.wire(BWPHIOUT-1, 0, "phiL");

// regs ------------------------------------------------------------------
	Eqme12r.reg  (BWEQ12R-1, 0, "Eqme12r");
	Eqme13r.reg  (BWEQ12R-1, 0, "Eqme13r");	
	Eqme12ovr.reg(BWEQ12OVR-1, 0, "Eqme12ovr");
	Eqme23r.reg  (BWEQ234R-1, 0, "Eqme23r");
	Eqme24r.reg  (BWEQ234R-1, 0, "Eqme24r");
	Eqme34r.reg  (BWEQ234R-1, 0, "Eqme34r"); 
	Eq2b1r.reg   (BWEQ2B1R-1, 0, "Eq2b1r");
	Eq2b2r.reg   (BWEQ2B2R-1, 0, "Eq2b2r");

	pt2ar.reg (BWPT-1,0,"pt2ar");  Reg_(pt2arr , BWPT-1, 0); Reg_(pt2arrr , BWPT-1, 0); 
	pt2br.reg (BWPT-1,0,"pt2br");  Reg_(pt2brr , BWPT-1, 0); Reg_(pt2brrr , BWPT-1, 0);
	pt2cr.reg (BWPT-1,0,"pt2cr");  Reg_(pt2crr , BWPT-1, 0); Reg_(pt2crrr , BWPT-1, 0);
	pt3ar.reg (BWPT-1,0,"pt3ar");  Reg_(pt3arr , BWPT-1, 0); Reg_(pt3arrr , BWPT-1, 0);
	pt3br.reg (BWPT-1,0,"pt3br");  Reg_(pt3brr , BWPT-1, 0); Reg_(pt3brrr , BWPT-1, 0);
	pt3cr.reg (BWPT-1,0,"pt3cr");  Reg_(pt3crr , BWPT-1, 0); Reg_(pt3crrr , BWPT-1, 0);
	ptb2ar.reg(BWPT-1,0,"ptb2ar"); Reg_(ptb2arr, BWPT-1, 0); Reg_(ptb2arrr, BWPT-1, 0);
	ptb2br.reg(BWPT-1,0,"ptb2br"); Reg_(ptb2brr, BWPT-1, 0); Reg_(ptb2brrr, BWPT-1, 0);
	ptb2cr.reg(BWPT-1,0,"ptb2cr"); Reg_(ptb2crr, BWPT-1, 0); Reg_(ptb2crrr, BWPT-1, 0);

	sign2ar.reg ("sign2ar");       Reg(sign2arr );           Reg(sign2arrr );
	sign2br.reg ("sign2br"); 	   Reg(sign2brr );			 Reg(sign2brrr );
	sign2cr.reg ("sign2cr"); 	   Reg(sign2crr );			 Reg(sign2crrr );
	sign3ar.reg ("sign3ar"); 	   Reg(sign3arr );			 Reg(sign3arrr );
	sign3br.reg ("sign3br"); 	   Reg(sign3brr );			 Reg(sign3brrr );
	sign3cr.reg ("sign3cr");	   Reg(sign3crr );			 Reg(sign3crrr );
	signb2ar.reg("signb2ar"); 	   Reg(signb2arr);			 Reg(signb2arrr);
	signb2br.reg("signb2br"); 	   Reg(signb2brr);			 Reg(signb2brrr);
	signb2cr.reg("signb2cr");	   Reg(signb2crr);			 Reg(signb2crrr);

	mode2ar.reg (BWMODE-1,0,"mode2ar");  Reg_(mode2arr , BWMODE-1,0); Reg_(mode2arrr , BWMODE-1,0);
	mode2br.reg (BWMODE-1,0,"mode2br");  Reg_(mode2brr , BWMODE-1,0); Reg_(mode2brrr , BWMODE-1,0);
	mode2cr.reg (BWMODE-1,0,"mode2cr");	 Reg_(mode2crr , BWMODE-1,0); Reg_(mode2crrr , BWMODE-1,0);
	mode3ar.reg (BWMODE-1,0,"mode3ar");  Reg_(mode3arr , BWMODE-1,0); Reg_(mode3arrr , BWMODE-1,0);
	mode3br.reg (BWMODE-1,0,"mode3br");  Reg_(mode3brr , BWMODE-1,0); Reg_(mode3brrr , BWMODE-1,0);
	mode3cr.reg (BWMODE-1,0,"mode3cr");	 Reg_(mode3crr , BWMODE-1,0); Reg_(mode3crrr , BWMODE-1,0);
	modeb2ar.reg(BWMODE-1,0,"modeb2ar"); Reg_(modeb2arr, BWMODE-1,0); Reg_(modeb2arrr, BWMODE-1,0);
	modeb2br.reg(BWMODE-1,0,"modeb2br"); Reg_(modeb2brr, BWMODE-1,0); Reg_(modeb2brrr, BWMODE-1,0);
	modeb2cr.reg(BWMODE-1,0,"modeb2cr"); Reg_(modeb2crr, BWMODE-1,0); Reg_(modeb2crrr, BWMODE-1,0);

	etaPT2ar.reg (BWETAOUT-1,0,"etaPT2ar"); Reg_(etaPT2arr , BWETAOUT-1,0); Reg_(etaPT2arrr , BWETAOUT-1,0);
	etaPT2br.reg (BWETAOUT-1,0,"etaPT2br"); Reg_(etaPT2brr , BWETAOUT-1,0);	Reg_(etaPT2brrr , BWETAOUT-1,0);
	etaPT2cr.reg (BWETAOUT-1,0,"etaPT2cr"); Reg_(etaPT2crr , BWETAOUT-1,0);	Reg_(etaPT2crrr , BWETAOUT-1,0);
	etaPT3ar.reg (BWETAOUT-1,0,"etaPT3ar"); Reg_(etaPT3arr , BWETAOUT-1,0);	Reg_(etaPT3arrr , BWETAOUT-1,0);
	etaPT3br.reg (BWETAOUT-1,0,"etaPT3br"); Reg_(etaPT3brr , BWETAOUT-1,0);	Reg_(etaPT3brrr , BWETAOUT-1,0);
	etaPT3cr.reg (BWETAOUT-1,0,"etaPT3cr"); Reg_(etaPT3crr , BWETAOUT-1,0);	Reg_(etaPT3crrr , BWETAOUT-1,0);
	etaPTb2ar.reg(BWETAOUT-1,0,"etaPTb2ar");Reg_(etaPTb2arr, BWETAOUT-1,0); Reg_(etaPTb2arrr, BWETAOUT-1,0);
	etaPTb2br.reg(BWETAOUT-1,0,"etaPTb2br");Reg_(etaPTb2brr, BWETAOUT-1,0); Reg_(etaPTb2brrr, BWETAOUT-1,0);
	etaPTb2cr.reg(BWETAOUT-1,0,"etaPTb2cr");Reg_(etaPTb2crr, BWETAOUT-1,0); Reg_(etaPTb2crrr, BWETAOUT-1,0);
	
	
	FR2ar.reg ("FR2ar");   Reg(FR2arr);	    Reg(FR2arrr);	
	FR2br.reg ("FR2br");   Reg(FR2brr);		Reg(FR2brrr);	
	FR2cr.reg ("FR2cr");   Reg(FR2crr);		Reg(FR2crrr);	
	FR3ar.reg ("FR3ar");   Reg(FR3arr);		Reg(FR3arrr);	
	FR3br.reg ("FR3br");   Reg(FR3brr);		Reg(FR3brrr);	
	FR3cr.reg ("FR3cr");   Reg(FR3crr);		Reg(FR3crrr);	
	FRb2ar.reg("FRb2ar");  Reg(FRb2arr);	Reg(FRb2arrr);
	FRb2br.reg("FRb2br");  Reg(FRb2brr);	Reg(FRb2brrr);
	FRb2cr.reg("FRb2cr");  Reg(FRb2crr);	Reg(FRb2crrr);

	phi2ar.reg (BWPHI-1,0,"phi2ar");   Reg_(phi2arr , BWPHI-1,0);  Reg_(phi2arrr , BWPHI-1,0);
	phi2br.reg (BWPHI-1,0,"phi2br");   Reg_(phi2brr , BWPHI-1,0);  Reg_(phi2brrr , BWPHI-1,0);
	phi2cr.reg (BWPHI-1,0,"phi2cr");   Reg_(phi2crr , BWPHI-1,0);  Reg_(phi2crrr , BWPHI-1,0);
	phi3ar.reg (BWPHI-1,0,"phi3ar");   Reg_(phi3arr , BWPHI-1,0);  Reg_(phi3arrr , BWPHI-1,0);
	phi3br.reg (BWPHI-1,0,"phi3br");   Reg_(phi3brr , BWPHI-1,0);  Reg_(phi3brrr , BWPHI-1,0);
	phi3cr.reg (BWPHI-1,0,"phi3cr");   Reg_(phi3crr , BWPHI-1,0);  Reg_(phi3crrr , BWPHI-1,0);
	phib2ar.reg(BWPHI-1,0,"phib2ar");  Reg_(phib2arr, BWPHI-1,0);  Reg_(phib2arrr, BWPHI-1,0);
	phib2br.reg(BWPHI-1,0,"phib2br");  Reg_(phib2brr, BWPHI-1,0);  Reg_(phib2brrr, BWPHI-1,0);
	phib2cr.reg(BWPHI-1,0,"phib2cr");  Reg_(phib2crr, BWPHI-1,0);  Reg_(phib2crrr, BWPHI-1,0);
	
	ir.reg(4, 0, "ir");
	
	Reg_(Eqme23ar, 6, 0); // accelerator tracks extrapolation results delay
	
	assign MinEta [0] = mneta0;
	assign MinEta [1] = mneta1;
	assign MinEta [2] = mneta2;
	assign MinEta [3] = mneta3;
	assign MinEta [4] = mneta4;
	assign MinEta [5] = mneta5;
	assign MinEta [6] = mneta6;
	assign MinEta [7] = mneta7;
													  
	assign MaxEta [0] = mxeta0;
	assign MaxEta [1] = mxeta1;
	assign MaxEta [2] = mxeta2;
	assign MaxEta [3] = mxeta3;
	assign MaxEta [4] = mxeta4;
	assign MaxEta [5] = mxeta5;
	assign MaxEta [6] = mxeta6;
	assign MaxEta [7] = mxeta7;

	assign EtaWindow [0] = etawn0; 
	assign EtaWindow [1] = etawn1;
	assign EtaWindow [2] = etawn2;
	assign EtaWindow [3] = etawn3;
	assign EtaWindow [4] = etawn4;
	assign EtaWindow [5] = etawn5;



//#############################################################################
// Madorsky:
// Drift tubes send second trackstub (if available) on the next BX
// Modules below realign this second stub back to nominal BX
	dtbx[0](mb1ap, dmb1[a], dmb1[c], clkp);
	dtbx[1](mb1bp, dmb1[b], dmb1[d], clkp);

	bxa
	(
		me1ap, me1bp, me1cp, me1dp,	me1ep, me1fp,
		me2ap, me2bp, me2cp,		     
		me3ap, me3bp, me3cp,
		me4ap, me4bp, me4cp,
		dmb1[a], dmb1[b], dmb1[c], dmb1[d],
		"16'd0", "16'd0", "16'd0", "16'd0",

		me1[a],	me1[b],	me1[c],	me1[d],	me1[e],	me1[f],
		me2[a],	me2[b],	me2[c],
		me3[a],	me3[b],	me3[c],
		me4[a],	me4[b],	me4[c],
		mb1[a],	mb1[b],	mb1[c],	mb1[d],
		mb2[a],	mb2[b],	mb2[c],	mb2[d],

		me1bi[1],	me1bi[2],	me1bi[3],	me1bi[4],	me1bi[5],	me1bi[6],
		me2bi[1],	me2bi[2],	me2bi[3],
		me3bi[1],	me3bi[2],	me3bi[3],
		me4bi[1],	me4bi[2],	me4bi[3],
		mb1bi[1],	mb1bi[2],	mb1bi[3],	mb1bi[4],
		mb2bi[1],	mb2bi[2],	mb2bi[3],	mb2bi[4],

		control(2,1), // BXA depth

		clkp
	);

	assign me1bi[0] = 0; // ID = 0 means no track stub
	assign me2bi[0] = 0;
	assign me3bi[0] = 0;
	assign me4bi[0] = 0;
	assign mb1bi[0] = 0;
	assign mb2bi[0] = 0;

	
// ##################################################################################################################################################################

	int pYi[] = {1, 0, 0, 4, 3, 3};
	int pZi[] = {2, 2, 1, 5, 5, 4};
	int irr;

// Eta extrapolation units
	for (i = 0; i < NSEG1; i++)
	{
		for (j = 0; j < NSEG234; j++)
		{
			int lp12 = j * NSEG1 + i; // number of lsb for pass12

			etu12  [i][j].init("etau12",    "etu12_",   i*10+j);
			etu12ov[i][j].init("etau12ov",  "etu12ov_", i*10+j);
			etu13  [i][j].init("etau13",    "etu13_",   i*10+j);

			etu12  [i][j] (me1[i], me2[j], pass12  (lp12), MinEta[0], MaxEta[0], EtaWindow[0]);
			etu12ov[i][j] (me1[i], me2[j], pass12ov(lp12), MinEta[5], MaxEta[5], EtaWindow[5]);
			etu13  [i][j] (me1[i], me3[j], pass13  (lp12), MinEta[1], MaxEta[1], EtaWindow[1]);
		}
	}

// Phi extrapolations, using Eta results
	for (i = 0; i < NSEG1; i++)
	{
		for (j = 0; j < NSEG234; j++)
		{
			int lX12 = j * NSEG1 + i; // number of lsb for passX
			int lY12 = j * NSEG1 + pYi[i]; // number of lsb for passY
			int lZ12 = j * NSEG1 + pZi[i]; // number of lsb for passZ
			int l12 = j * NSEG1 * BWEQ12 + i * BWEQ12; // number of lsb for Eqme12
			int l12ov = j * NSEG1 * BWEQ12OV + i * BWEQ12OV; // number of lsb for Eqme12ov

			u12  [i][j].init("eu12",    "u12_",   i*10+j);
			u13  [i][j].init("eu13",    "u13_",   i*10+j);
			u12ov[i][j].init("eu12_ov", "u12ov_", i*10+j);

			u12  [i][j] (me1[i], me2[j], Eqme12  (l12+BWEQ12-1, l12), pass12(lX12), pass12(lY12), me1[pYi[i]], pass12(lZ12), me1[pZi[i]]      , control(5,4));
			u13  [i][j] (me1[i], me3[j], Eqme13  (l12+BWEQ12-1, l12), pass13(lX12), pass13(lY12), me1[pYi[i]], pass13(lZ12), me1[pZi[i]]      , control(5,4));
			u12ov[i][j] (me1[i], me2[j], Eqme12ov(l12ov),             pass12ov(lX12), pass12ov(lY12), me1[pYi[i]], pass12ov(lZ12), me1[pZi[i]], control(5,4));
		}
	}

	for (i = 0; i < NSEG234; i++)
	{
		for (j = 0; j < NSEG234; j++)
		{
			int l = i * NSEG234 * BWEQ234 + j * BWEQ234;

			u23[i][j].init("eu23_24_34", "u23_", i*10+j);
			u24[i][j].init("eu23_24_34", "u24_", i*10+j);
			u34[i][j].init("eu23_24_34", "u34_", i*10+j);

			u23[i][j] (me2[i], me3[j], Eqme23(l), MinEta[2], MaxEta[2], EtaWindow[2], control(5,4));
			u24[i][j] (me2[i], me4[j], Eqme24(l), MinEta[3], MaxEta[3], EtaWindow[3], control(5,4));
			u34[i][j] (me3[i], me4[j], Eqme34(l), MinEta[4], MaxEta[4], EtaWindow[4], control(5,4));
			
			// accelerator track extrapolators
			u23a[i][j].init("eu23a", "u23a_", i*10+j);
			u23a[i][j] (me2[i], me3[j], Eqme23a(l), mindeta_acc, maxdeta_acc, maxdphi_acc /*, control(5,4)*/, clkp);

		}
	}

	for (i = 0; i < NSEG234; i++)
	{
		for (j = 0; j < NSEG12B; j++)
		{
			int l2b1 = i * NSEG12B * BWEQ2B1 + j * BWEQ2B1;
			int l2b2 = i * NSEG12B * BWEQ2B2 + j * BWEQ2B2;

			u2b1[i][j].init("eu2b1", "u2b1_", i*10+j);
			u2b2[i][j].init("eu2b2", "u2b2_", i*10+j);

			u2b1[i][j] (me2[i], mb1[j], Eq2b1(l2b1+BWEQ2B1-1, l2b1), MinEta[6], MaxEta[6]); 
			u2b2[i][j] (me2[i], mb2[j], Eq2b2(l2b2),                 MinEta[7], MaxEta[7]);
		}
	}

	// assemble tracks
	for (i = 0; i < NTAU; i++)
	{
		int l12 =  i * BWEQ12P  ;
		int l23 =  i * BWEQ234P ;
		int l2b1 = i * BWEQ2B1P ;
		int l2b2 = i * BWEQ2B2P ;
		int l12o = i * BWEQ12OVP;

		au2 [i].init("tau2",  "au2",  i);
		au3 [i].init("tau3",  "au3",  i);
		au2b[i].init("tau2b", "au2b", i);

		au2 [i] 
		(
			Eqme12r(l12+BWEQ12P-1, l12),  
			Eqme23r(l23+BWEQ234P-1, l23),   
			Eqme24r(l23+BWEQ234P-1, l23),     
			me2Id1[i], me2Id3[i], me2Id4[i], me2Rank[i]
		);

		au3 [i] 
		(
			Eqme13r(l12+BWEQ12P-1, l12),	//EQ 1->3, taken every 12 bits
			(Eqme23r(i+BWEQ234P*2), Eqme23r(i+BWEQ234P), Eqme23r(i)),   // unusual case of extrapolation 3 to 2, bit order is such that tau receives 3 to 2 extrapolation results
			Eqme34r(l23+BWEQ234P-1, l23),     
			me3Id1[i], me3Id2[i], me3Id4[i], me3Rank[i]
		);
		au2b[i] 
		(
			Eq2b1r (l2b1+BWEQ2B1P-1, l2b1), 
			Eq2b2r (l2b2+BWEQ2B2P-1, l2b2), 
			Eqme12ovr(l12o+BWEQ12OVP-1, l12o), 
			mb2idb1[i], mb2idb2[i], mb2id1[i], mb2rank[i]
		);
	}

// assign pt to all 9 muons 
	ptu2a 
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		me3rr[0], me3rr[1], me3rr[2],
		me4rr[0], me4rr[1], me4rr[2],
		me2Rankr[0], me2Id1r[0], "2'h1", me2Id3r[0], me2Id4r[0], u2aId,
		pt2a, sign2a, mode2a, etaPT2a, FR2a, phi2a,	u2aIdt, me2Rankrr[0],
		clkp
	);

	ptu2b 
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		me3rr[0], me3rr[1], me3rr[2],
		me4rr[0], me4rr[1], me4rr[2],
		me2Rankr[1], me2Id1r[1], "2'h2", me2Id3r[1], me2Id4r[1], u2bId,
		pt2b, sign2b, mode2b, etaPT2b, FR2b, phi2b, u2bIdt, me2Rankrr[1],
		clkp
	);

	ptu2c 
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		me3rr[0], me3rr[1], me3rr[2],
		me4rr[0], me4rr[1], me4rr[2],
		me2Rankr[2], me2Id1r[2], "2'h3", me2Id3r[2], me2Id4r[2], u2cId,
		pt2c, sign2c, mode2c, etaPT2c, FR2c, phi2c, u2cIdt, me2Rankrr[2], 
		clkp
	);

	ptu3a 
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		me3rr[0], me3rr[1], me3rr[2],
		me4rr[0], me4rr[1], me4rr[2],
		me3Rankr[0], me3Id1r[0], me3Id2r[0], "2'h1", me3Id4r[0], u3aId,
		pt3a, sign3a, mode3a, etaPT3a, FR3a, phi3a, u3aIdt, me3Rankrr[0],
		clkp
	);

	ptu3b 
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		me3rr[0], me3rr[1], me3rr[2],
		me4rr[0], me4rr[1], me4rr[2],
		me3Rankr[1], me3Id1r[1], me3Id2r[1], "2'h2", me3Id4r[1], u3bId,
		pt3b, sign3b, mode3b, etaPT3b, FR3b, phi3b, u3bIdt, me3Rankrr[1],
		clkp
	);

	ptu3c 
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		me3rr[0], me3rr[1], me3rr[2],
		me4rr[0], me4rr[1], me4rr[2],
		me3Rankr[2], me3Id1r[2], me3Id2r[2], "2'h3", me3Id4r[2], u3cId,
		pt3c, sign3c, mode3c, etaPT3c, FR3c, phi3c, u3cIdt, me3Rankrr[2],
		clkp
	);

	ptub2a
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		mb1rr[0], mb1rr[1], mb1rr[2], mb1rr[3], 
		mb2rr[0], mb2rr[1], mb2rr[2], mb2rr[3], 
		mb2rankr[0], mb2id1r[0], "2'h1", mb2idb1r[0], mb2idb2r[0], ub2aId,
		ptb2a, signb2a, modeb2a, etaPTb2a, FRb2a, phib2a, ub2aIdt, mb2rankrr[0],
		clkp
	);

	ptub2b
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		mb1rr[0], mb1rr[1], mb1rr[2], mb1rr[3], 
		mb2rr[0], mb2rr[1], mb2rr[2], mb2rr[3], 
		mb2rankr[1], mb2id1r[1], "2'h2", mb2idb1r[1], mb2idb2r[1], ub2bId,
		ptb2b, signb2b, modeb2b, etaPTb2b, FRb2b, phib2b, ub2bIdt, mb2rankrr[1],
		clkp
	);

	ptub2c
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		mb1rr[0], mb1rr[1], mb1rr[2], mb1rr[3], 
		mb2rr[0], mb2rr[1], mb2rr[2], mb2rr[3], 
		mb2rankr[2], mb2id1r[2], "2'h3", mb2idb1r[2], mb2idb2r[2], ub2cId,
		ptb2c, signb2c, modeb2c, etaPTb2c, FRb2c, phib2c, ub2cIdt, mb2rankrr[2], 
		clkp
	);


// select the best muons
	fsuv
	(
		me2Rankrr[0],  phi2a, // phi inputs are calculated by PT assignment units within the same clock
		me2Rankrr[1],  phi2b, 
		me2Rankrr[2],  phi2c, 
		        			   
		me3Rankrr[0],  phi3a, 
		me3Rankrr[1],  phi3b, 
		me3Rankrr[2],  phi3c, 
		        	 	   	
		mb2rankrr[0],  phib2a, 
		mb2rankrr[1],  phib2b, 
		mb2rankrr[2],  phib2c, 

//  m's contain ids for best tracks, 0->2
		m0, m1, m2,

		control(6), // ghost cancellation based on phi proximity
		mindphi, // min phi difference for ghost cancellation

		clkp                            
	);


	// register all intermediary signals
	always (posedge (clkp))
	begin
// fifth clock
		for (irr = 0; irr < NTAU; irr++)
		{
			me2Rankrrrrr[irr] =  me2Rankrrrr[irr];
			me3Rankrrrrr[irr] =  me3Rankrrrr[irr];
			mb2rankrrrrr[irr] =  mb2rankrrrr[irr];
		}

		pt2arrr =   	 pt2arr ;
		pt2brrr =   	 pt2brr ;
		pt2crrr =   	 pt2crr ;
		pt3arrr =   	 pt3arr ; 
		pt3brrr =   	 pt3brr ; 
		pt3crrr =   	 pt3crr ; 
		ptb2arrr =  	 ptb2arr;
		ptb2brrr =  	 ptb2brr;
		ptb2crrr =  	 ptb2crr;
					          
		etaPT2arrr =  etaPT2arr  ;
		etaPT2brrr =  etaPT2brr  ;
		etaPT2crrr =  etaPT2crr  ;
		etaPT3arrr =  etaPT3arr  ;
		etaPT3brrr =  etaPT3brr  ;
		etaPT3crrr =  etaPT3crr  ;
		etaPTb2arrr = etaPTb2arr ;
		etaPTb2brrr = etaPTb2brr ;
		etaPTb2crrr = etaPTb2crr ;
					          
		mode2arrr =   mode2arr	  ;
		mode2brrr =   mode2brr	  ;
		mode2crrr =   mode2crr	  ;
		mode3arrr =   mode3arr	  ;
		mode3brrr =   mode3brr	  ;
		mode3crrr =   mode3crr	  ;
		modeb2arrr =  modeb2arr  ;
		modeb2brrr =  modeb2brr  ;
		modeb2crrr =  modeb2crr  ;
					          
		sign2arrr =   sign2arr	  ;
		sign2brrr =   sign2brr	  ;
		sign2crrr =   sign2crr	  ;
		sign3arrr =   sign3arr	  ;
		sign3brrr =   sign3brr	  ;
		sign3crrr =   sign3crr	  ;
		signb2arrr =  signb2arr  ;
		signb2brrr =  signb2brr  ;
		signb2crrr =  signb2crr  ;

		FR2arrr	 = FR2arr   ;
		FR2brrr	 = FR2brr   ;
		FR2crrr	 = FR2crr   ;
		FR3arrr	 = FR3arr   ;
		FR3brrr	 = FR3brr   ;
		FR3crrr	 = FR3crr   ;
		FRb2arrr	 = FRb2arr  ;
		FRb2brrr	 = FRb2brr  ;
		FRb2crrr	 = FRb2crr  ;
		       	         
		phi2arrr	 = phi2arr  ;
		phi2brrr	 = phi2brr  ;
		phi2crrr	 = phi2crr  ;
		phi3arrr	 = phi3arr  ;
		phi3brrr	 = phi3brr  ;
		phi3crrr	 = phi3crr  ;
		phib2arrr	 = phib2arr ;
		phib2brrr	 = phib2brr ;
		phib2crrr	 = phib2crr ;

		u2aIdrrr 	 = u2aIdrr ;
		u2bIdrrr 	 = u2bIdrr ;
		u2cIdrrr      = u2cIdrr ;
		u3aIdrrr 	 = u3aIdrr ;
		u3bIdrrr 	 = u3bIdrr ;
		u3cIdrrr 	 = u3cIdrr ;
		ub2aIdrrr	 = ub2aIdrr;
		ub2bIdrrr	 = ub2bIdrr;
		ub2cIdrrr	 = ub2cIdrr;

// fourth clock
		for (irr = 0; irr < NTAU; irr++)
		{
			me2Rankrrrr[irr] =  me2Rankrrr[irr];
			me3Rankrrrr[irr] =  me3Rankrrr[irr];
			mb2rankrrrr[irr] =  mb2rankrrr[irr];
		}

		pt2arr =   	 pt2ar ;
		pt2brr =   	 pt2br ;
		pt2crr =   	 pt2cr ;
		pt3arr =   	 pt3ar ; 
		pt3brr =   	 pt3br ; 
		pt3crr =   	 pt3cr ; 
		ptb2arr =  	 ptb2ar;
		ptb2brr =  	 ptb2br;
		ptb2crr =  	 ptb2cr;
					          
		etaPT2arr =  etaPT2ar  ;
		etaPT2brr =  etaPT2br  ;
		etaPT2crr =  etaPT2cr  ;
		etaPT3arr =  etaPT3ar  ;
		etaPT3brr =  etaPT3br  ;
		etaPT3crr =  etaPT3cr  ;
		etaPTb2arr = etaPTb2ar ;
		etaPTb2brr = etaPTb2br ;
		etaPTb2crr = etaPTb2cr ;
					          
		mode2arr =   mode2ar	  ;
		mode2brr =   mode2br	  ;
		mode2crr =   mode2cr	  ;
		mode3arr =   mode3ar	  ;
		mode3brr =   mode3br	  ;
		mode3crr =   mode3cr	  ;
		modeb2arr =  modeb2ar  ;
		modeb2brr =  modeb2br  ;
		modeb2crr =  modeb2cr  ;
					          
		sign2arr =   sign2ar	  ;
		sign2brr =   sign2br	  ;
		sign2crr =   sign2cr	  ;
		sign3arr =   sign3ar	  ;
		sign3brr =   sign3br	  ;
		sign3crr =   sign3cr	  ;
		signb2arr =  signb2ar  ;
		signb2brr =  signb2br  ;
		signb2crr =  signb2cr  ;

		FR2arr	 = FR2ar   ;
		FR2brr	 = FR2br   ;
		FR2crr	 = FR2cr   ;
		FR3arr	 = FR3ar   ;
		FR3brr	 = FR3br   ;
		FR3crr	 = FR3cr   ;
		FRb2arr	 = FRb2ar  ;
		FRb2brr	 = FRb2br  ;
		FRb2crr	 = FRb2cr  ;
		       	         
		phi2arr	 = phi2ar  ;
		phi2brr	 = phi2br  ;
		phi2crr	 = phi2cr  ;
		phi3arr	 = phi3ar  ;
		phi3brr	 = phi3br  ;
		phi3crr	 = phi3cr  ;
		phib2arr	 = phib2ar ;
		phib2brr	 = phib2br ;
		phib2crr	 = phib2cr ;

		u2aIdrr 	 = u2aIdr ;
		u2bIdrr 	 = u2bIdr ;
		u2cIdrr      = u2cIdr ;
		u3aIdrr 	 = u3aIdr ;
		u3bIdrr 	 = u3bIdr ;
		u3cIdrr 	 = u3cIdr ;
		ub2aIdrr	 = ub2aIdr;
		ub2bIdrr	 = ub2bIdr;
		ub2cIdrr	 = ub2cIdr;

// third clock
		for (irr = 0; irr < NTAU; irr++)
		{
			me2Rankrrr[irr] =  me2Rankrr[irr];
			me3Rankrrr[irr] =  me3Rankrr[irr];
			mb2rankrrr[irr] =  mb2rankrr[irr];
		}

		pt2ar =   	 pt2a ;
		pt2br =   	 pt2b ;
		pt2cr =   	 pt2c ;
		pt3ar =   	 pt3a ; 
		pt3br =   	 pt3b ; 
		pt3cr =   	 pt3c ; 
		ptb2ar =  	 ptb2a;
		ptb2br =  	 ptb2b;
		ptb2cr =  	 ptb2c;
					          
		etaPT2ar =  etaPT2a  ;
		etaPT2br =  etaPT2b  ;
		etaPT2cr =  etaPT2c  ;
		etaPT3ar =  etaPT3a  ;
		etaPT3br =  etaPT3b  ;
		etaPT3cr =  etaPT3c  ;
		etaPTb2ar = etaPTb2a ;
		etaPTb2br = etaPTb2b ;
		etaPTb2cr = etaPTb2c ;
					          
		mode2ar =   mode2a	  ;
		mode2br =   mode2b	  ;
		mode2cr =   mode2c	  ;
		mode3ar =   mode3a	  ;
		mode3br =   mode3b	  ;
		mode3cr =   mode3c	  ;
		modeb2ar =  modeb2a  ;
		modeb2br =  modeb2b  ;
		modeb2cr =  modeb2c  ;
					          
		sign2ar =   sign2a	  ;
		sign2br =   sign2b	  ;
		sign2cr =   sign2c	  ;
		sign3ar =   sign3a	  ;
		sign3br =   sign3b	  ;
		sign3cr =   sign3c	  ;
		signb2ar =  signb2a  ;
		signb2br =  signb2b  ;
		signb2cr =  signb2c  ;

		FR2ar	 = FR2a   ;
		FR2br	 = FR2b   ;
		FR2cr	 = FR2c   ;
		FR3ar	 = FR3a   ;
		FR3br	 = FR3b   ;
		FR3cr	 = FR3c   ;
		FRb2ar	 = FRb2a  ;
		FRb2br	 = FRb2b  ;
		FRb2cr	 = FRb2c  ;
		       	         
		phi2ar	 = phi2a  ;
		phi2br	 = phi2b  ;
		phi2cr	 = phi2c  ;
		phi3ar	 = phi3a  ;
		phi3br	 = phi3b  ;
		phi3cr	 = phi3c  ;
		phib2ar	 = phib2a ;
		phib2br	 = phib2b ;
		phib2cr	 = phib2c ;

		u2aIdr 	 = u2aIdt ;
		u2bIdr 	 = u2bIdt ;
		u2cIdr   = u2cIdt ;
		u3aIdr 	 = u3aIdt ;
		u3bIdr 	 = u3bIdt ;
		u3cIdr 	 = u3cIdt ;
		ub2aIdr	 = ub2aIdt;
		ub2bIdr	 = ub2bIdt;
		ub2cIdr	 = ub2cIdt;

		for (irr = 0; irr < NTAU; irr++)
		{
			me2Id1rr [irr] =  me2Id1r[irr] ;
			me2Id3rr [irr] =  me2Id3r[irr] ; 
			me2Id4rr [irr] =  me2Id4r[irr] ; 
			me3Id1rr [irr] =  me3Id1r[irr] ; 
			me3Id2rr [irr] =  me3Id2r[irr] ; 
			me3Id4rr [irr] =  me3Id4r[irr] ; 
			mb2idb1rr[irr] =  mb2idb1r[irr];
			mb2idb2rr[irr] =  mb2idb2r[irr];
			mb2id1rr [irr] =  mb2id1r[irr] ;
		}
// second clock

		For (ir = 0, ir < NSEG1, ir++) me1rr[ir] = me1r[ir];	

		For (ir = 0, ir < NSEG234, ir++)
		begin
			me2rr[ir] = me2r[ir];	
			me3rr[ir] = me3r[ir];	
			me4rr[ir] = me4r[ir];	
		end

		For (ir = 0, ir < NSEG12B, ir++)
		begin
			mb1rr[ir] = mb1r[ir]; 
			mb2rr[ir] = mb2r[ir]; 
		end

		for (irr = 0; irr < NTAU; irr++)
		{
			me2Id1r [irr] =  me2Id1[irr] ;
			me2Id3r [irr] =  me2Id3[irr] ; 
			me2Id4r [irr] =  me2Id4[irr] ; 
			me2Rankr[irr] =  me2Rank[irr];
			me3Id1r [irr] =  me3Id1[irr] ; 
			me3Id2r [irr] =  me3Id2[irr] ; 
			me3Id4r [irr] =  me3Id4[irr] ; 
			me3Rankr[irr] =  me3Rank[irr];
			mb2idb1r[irr] =  mb2idb1[irr];
			mb2idb2r[irr] =  mb2idb2[irr];
			mb2id1r [irr] =  mb2id1[irr] ;
			mb2rankr[irr] =  mb2rank[irr];
		}

		// the code below does this:
		// 1. take stub Id found by assembly unit (me2Id1[0] means station 1 stub that matched key station 2 stub). Stub Id for key station is a fixed number (0,1,2).
		// 2. look up the original stub Id and BX from me1bir. This needs to be done because BXA sometimes changes stub Id and BX
		u2aId 	 = ((Signal)"6'h0", (Signal)"6'h0", me4bir[me2Id4[0]], me3bir[me2Id3[0]], me2bir[1], me1bir[me2Id1[0]]);
		u2bId 	 = ((Signal)"6'h0", (Signal)"6'h0", me4bir[me2Id4[1]], me3bir[me2Id3[1]], me2bir[2], me1bir[me2Id1[1]]);
		u2cId    = ((Signal)"6'h0", (Signal)"6'h0", me4bir[me2Id4[2]], me3bir[me2Id3[2]], me2bir[3], me1bir[me2Id1[2]]);
			  	   	   
		u3aId 	 = ((Signal)"6'h0", (Signal)"6'h0", me4bir[me3Id4[0]], me3bir[1], me2bir[me3Id2[0]], me1bir[me3Id1[0]]);
		u3bId 	 = ((Signal)"6'h0", (Signal)"6'h0", me4bir[me3Id4[1]], me3bir[2], me2bir[me3Id2[1]], me1bir[me3Id1[1]]);
		u3cId 	 = ((Signal)"6'h0", (Signal)"6'h0", me4bir[me3Id4[2]], me3bir[3], me2bir[me3Id2[2]], me1bir[me3Id1[2]]);
			  	   	   
		ub2aId	 = (mb2bir[mb2idb2[0]], mb1bir[mb2idb1[0]], (Signal)"6'h0", (Signal)"6'h0", me2bir[1], me1bir[mb2id1[0]]);
		ub2bId	 = (mb2bir[mb2idb2[1]], mb1bir[mb2idb1[1]], (Signal)"6'h0", (Signal)"6'h0", me2bir[2], me1bir[mb2id1[1]]);
		ub2cId	 = (mb2bir[mb2idb2[2]], mb1bir[mb2idb1[2]], (Signal)"6'h0", (Signal)"6'h0", me2bir[3], me1bir[mb2id1[2]]);

// first clock
		Eqme12r   =  Eqme12  ; // {2c1f[2], 2c1e[2], 2c1d[2], 2c1c[2], 2c1b[2], 2c1a[2], // [2] means size of field is 2 bits
                               //  2b1f[2], 2b1e[2], 2b1d[2], 2b1c[2], 2b1b[2], 2b1a[2],
					 		   //  2a1f[2], 2a1e[2], 2a1d[2], 2a1c[2], 2a1b[2], 2a1a[2]}
					 						 
		Eqme13r	  =	 Eqme13	 ; // {3c1f[2], 3c1e[2], 3c1d[2], 3c1c[2], 3c1b[2], 3c1a[2], // [2] means size of field is 2 bits
					 		   //  3b1f[2], 3b1e[2], 3b1d[2], 3b1c[2], 3b1b[2], 3b1a[2],
					 		   //  3a1f[2], 3a1e[2], 3a1d[2], 3a1c[2], 3a1b[2], 3a1a[2]}
					 							 
		Eqme12ovr =	 Eqme12ov; // {2c1f[1], 2c1e[1], 2c1d[1], 2c1c[1], 2c1b[1], 2c1a[1], // [1] means size of field is 1 bits
					 		   //  2b1f[1], 2b1e[1], 2b1d[1], 2b1c[1], 2b1b[1], 2b1a[1],
					 		   //  2a1f[1], 2a1e[1], 2a1d[1], 2a1c[1], 2a1b[1], 2a1a[1]}
					 							 
		Eqme23r	  =	 Eqme23	 ; // {2c3c[1], 2c3b[1], 2c3a[1], // [1] means size of field is 1 bits
					 		   //  2b3c[1], 2b3b[1], 2b3a[1],                                     
					 		   //  2a3c[1], 2a3b[1], 2a3a[1]}                                     
					 							 
		Eqme24r	  =	 Eqme24	 ; // {2c4c[1], 2c4b[1], 2c4a[1], // [1] means size of field is 1 bits
					 		   //  2b4c[1], 2b4b[1], 2b4a[1],                                     
					 		   //  2a4c[1], 2a4b[1], 2a4a[1]}                                     
					 							 
		Eqme34r	  =	 Eqme34	 ; // {3c4c[1], 3c4b[1], 3c4a[1], // [1] means size of field is 1 bits
					 		   //  3b4c[1], 3b4b[1], 3b4a[1],                                     
					 		   //  3a4c[1], 3a4b[1], 3a4a[1]}                                     
					 							 
		Eq2b1r	  =	 Eq2b1	 ; // {2c1d[2], 2c1c[2], 2c1b[2], 2c1a[2], // [2] means size of field is 1 bits
					 		   //  2b1d[2], 2b1c[2], 2b1b[2], 2b1a[2],                                     
					 		   //  2a1d[2], 2a1c[2], 2a1b[2], 2a1a[2]}                                     
					 							 
		Eq2b2r	  =	 Eq2b2	 ; // {2c2d[1], 2c2c[1], 2c2b[1], 2c2a[1], // [1] means size of field is 1 bits
							   //  2b2d[1], 2b2c[1], 2b2b[1], 2b2a[1],                                     
							   //  2a2d[1], 2a2c[1], 2a2b[1], 2a2a[1]}                                     


		// register the PtAssignment units inputs to synchronize them with tau outputs
		for (irr = 0; irr < NSEG1; irr++) me1r[irr]	= me1[irr];	

		for (irr = 0; irr < NSEG234; irr++)
		{
			me2r[irr] = me2[irr];	
			me3r[irr] = me3[irr];	
			me4r[irr] = me4[irr];	
		}

		for (irr = 0; irr < NSEG12B; irr++)
		{
			mb1r[irr] = mb1[irr]; 
			mb2r[irr] = mb2[irr]; 
		}

		for (irr = 0; irr <= NSEG1; irr++) 
		{
			me1bir[irr]	= me1bi[irr];	
		}

		for (irr = 0; irr <= NSEG234; irr++)
		{
			me2bir[irr] = me2bi[irr];	
			me3bir[irr] = me3bi[irr];	
			me4bir[irr] = me4bi[irr];	
		}

		for (irr = 0; irr <= NSEG12B; irr++)
		{
			mb1bir[irr] = mb1bi[irr]; 
			mb2bir[irr] = mb2bi[irr]; 
		}
	
		// accelerator extrapolation result delay to match collision timing
		Eqme23ar = (Eqme23ar(5, 0), ror(Eqme23a));	
		
	end

// multiplex the best muons to the output
	mux
	(
		m0, m1, m2,

		pt2arrr,  sign2arrr,  mode2arrr,  etaPT2arrr,  FR2arrr , phi2arrr  , me2Rankrrrrr[0], 
		pt2brrr,  sign2brrr,  mode2brrr,  etaPT2brrr,  FR2brrr , phi2brrr  , me2Rankrrrrr[1],
		pt2crrr,  sign2crrr,  mode2crrr,  etaPT2crrr,  FR2crrr , phi2crrr  , me2Rankrrrrr[2],
		pt3arrr,  sign3arrr,  mode3arrr,  etaPT3arrr,  FR3arrr , phi3arrr  , me3Rankrrrrr[0],
		pt3brrr,  sign3brrr,  mode3brrr,  etaPT3brrr,  FR3brrr , phi3brrr  , me3Rankrrrrr[1],
		pt3crrr,  sign3crrr,  mode3crrr,  etaPT3crrr,  FR3crrr , phi3crrr  , me3Rankrrrrr[2],
		ptb2arrr, signb2arrr, modeb2arrr, etaPTb2arrr, FRb2arrr, phib2arrr , mb2rankrrrrr[0],
		ptb2brrr, signb2brrr, modeb2brrr, etaPTb2brrr, FRb2brrr, phib2brrr , mb2rankrrrrr[1],
		ptb2crrr, signb2crrr, modeb2crrr, etaPTb2crrr, FRb2crrr, phib2crrr , mb2rankrrrrr[2],

		u2aIdrrr,  u2bIdrrr,  u2cIdrrr,
		u3aIdrrr,  u3bIdrrr,  u3cIdrrr,
		ub2aIdrrr, ub2bIdrrr, ub2cIdrrr, 
	
		ptH, signH, modeMemH, etaPTH, FRH, phiH, rankH,
		ptM, signM, modeMemM, etaPTM, FRM, phiM, rankM,
		ptL, signL, modeMemL, etaPTL, FRL, phiL, rankL,
		idH, idM, idL
		
	);


	// correct bx assignment according to pretrigger requirement
	bxcorr
	(
		rankH, rankM, rankL, 

		(FRH, phiH, ptH, signH, modeMemH, etaPTH),
		(FRM, phiM, ptM, signM, modeMemM, etaPTM),
		(FRL, phiL, ptL, signL, modeMemL, etaPTL),

		idH, idM, idL,

		pHp, pMp, pLp,
		idHp, idMp, idLp,
		
		Eqme23ar(6), // acc track found		
		
		control(8,7), // pretrig

		clkp
	);

    // assign outputs
//	assign	pHp = (FRH, phiH, ptH, signH, modeMemH, etaPTH);
//	assign	pMp = (FRM, phiM, ptM, signM, modeMemM, etaPTM);
//	assign	pLp = (FRL, phiL, ptL, signL, modeMemL, etaPTL);
//	assign	idHp = idH;
//	assign	idMp = idM;
//	assign	idLp = idL;

// generate date output
#ifdef VGEN
	struct tm *ltm;
	time_t lt;
	lt = time(NULL);
	ltm = localtime(&lt);

	cout << "\n    assign date = {4'd"<< ltm->tm_mon+1 <<", 5'd"<< ltm->tm_mday <<", 7'd"<< ltm->tm_year-100 <<"};\n" << endl;
	
#endif

endmodule
}
