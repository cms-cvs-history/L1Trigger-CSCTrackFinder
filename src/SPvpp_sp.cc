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
	Signal etaoff1, Signal etaoff2, Signal etaoff3, Signal etaoff4,
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

	Input_(etaoff1, BWETAIN-1, 0); // eta offsets (individual for 4 ME stations)
	Input_(etaoff2, BWETAIN-1, 0); 
	Input_(etaoff3, BWETAIN-1, 0); 
	Input_(etaoff4, BWETAIN-1, 0); 

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

	u2aIdr.reg(MUIDSIZE-1,0,"u2aIdr");
	u2bIdr.reg(MUIDSIZE-1,0,"u2bIdr");
	u2cIdr.reg(MUIDSIZE-1,0,"u2cIdr");

	u3aIdr.reg(MUIDSIZE-1,0,"u3aIdr");
	u3bIdr.reg(MUIDSIZE-1,0,"u3bIdr");
	u3cIdr.reg(MUIDSIZE-1,0,"u3cIdr");

	ub2aIdr.reg(MUIDSIZE-1,0,"ub2aIdr");
	ub2bIdr.reg(MUIDSIZE-1,0,"ub2bIdr");
	ub2cIdr.reg(MUIDSIZE-1,0,"ub2cIdr");
	
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

	pt2ar.reg(BWPT-1,0,"pt2ar"); 
	pt2br.reg(BWPT-1,0,"pt2br"); 
	pt2cr.reg(BWPT-1,0,"pt2cr");

	pt3ar.reg(BWPT-1,0,"pt3ar"); 
	pt3br.reg(BWPT-1,0,"pt3br"); 
	pt3cr.reg(BWPT-1,0,"pt3cr");

	ptb2ar.reg(BWPT-1,0,"ptb2ar"); 
	ptb2br.reg(BWPT-1,0,"ptb2br"); 
	ptb2cr.reg(BWPT-1,0,"ptb2cr");

	sign2ar.reg("sign2ar"); 
	sign2br.reg("sign2br"); 
	sign2cr.reg("sign2cr"); 

	sign3ar.reg("sign3ar"); 
	sign3br.reg("sign3br"); 
	sign3cr.reg("sign3cr");

	signb2ar.reg("signb2ar"); 
	signb2br.reg("signb2br"); 
	signb2cr.reg("signb2cr");

	mode2ar.reg(BWMODE-1,0,"mode2ar"); 
	mode2br.reg(BWMODE-1,0,"mode2br"); 
	mode2cr.reg(BWMODE-1,0,"mode2cr");

	mode3ar.reg(BWMODE-1,0,"mode3ar"); 
	mode3br.reg(BWMODE-1,0,"mode3br"); 
	mode3cr.reg(BWMODE-1,0,"mode3cr");

	modeb2ar.reg(BWMODE-1,0,"modeb2ar"); 
	modeb2br.reg(BWMODE-1,0,"modeb2br"); 
	modeb2cr.reg(BWMODE-1,0,"modeb2cr");

	etaPT2ar.reg(BWETAOUT-1,0,"etaPT2ar"); 
	etaPT2br.reg(BWETAOUT-1,0,"etaPT2br"); 
	etaPT2cr.reg(BWETAOUT-1,0,"etaPT2cr"); 

	etaPT3ar.reg(BWETAOUT-1,0,"etaPT3ar"); 
	etaPT3br.reg(BWETAOUT-1,0,"etaPT3br"); 
	etaPT3cr.reg(BWETAOUT-1,0,"etaPT3cr"); 

	etaPTb2ar.reg(BWETAOUT-1,0,"etaPTb2ar"); 
	etaPTb2br.reg(BWETAOUT-1,0,"etaPTb2br"); 
	etaPTb2cr.reg(BWETAOUT-1,0,"etaPTb2cr"); 

	FR2ar.reg("FR2ar"); 
	FR2br.reg("FR2br"); 
	FR2cr.reg("FR2cr");

	FR3ar.reg("FR3ar"); 
	FR3br.reg("FR3br"); 
	FR3cr.reg("FR3cr");

	FRb2ar.reg("FRb2ar"); 
	FRb2br.reg("FRb2br"); 
	FRb2cr.reg("FRb2cr");

	phi2ar.reg(BWPHI-1,0,"phi2ar"); 
	phi2br.reg(BWPHI-1,0,"phi2br"); 
	phi2cr.reg(BWPHI-1,0,"phi2cr");

	phi3ar.reg(BWPHI-1,0,"phi3ar"); 
	phi3br.reg(BWPHI-1,0,"phi3br"); 
	phi3cr.reg(BWPHI-1,0,"phi3cr");

	phib2ar.reg(BWPHI-1,0,"phib2ar"); 
	phib2br.reg(BWPHI-1,0,"phib2br"); 
	phib2cr.reg(BWPHI-1,0,"phib2cr");
	
	m0r.reg(8,0,"m0r"); 
	m1r.reg(8,0,"m1r"); 
	m2r.reg(8,0,"m2r"); 

	ir.reg(4, 0, "ir");
	
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

#ifndef _BXAON
	assign	me1[a] 	= 	me1ap  ;	
	assign	me1[b] 	= 	me1bp  ;	
	assign	me1[c] 	= 	me1cp  ;	
	assign	me1[d] 	= 	me1dp  ;	
	assign	me1[e] 	= 	me1ep  ;	
	assign	me1[f] 	= 	me1fp  ;	

	assign	me2[a] 	= 	me2ap  ;	
	assign	me2[b] 	= 	me2bp  ;	
	assign	me2[c] 	= 	me2cp  ;	

	assign	me3[a] 	= 	me3ap  ;	
	assign	me3[b] 	= 	me3bp  ;	
	assign	me3[c] 	= 	me3cp  ;	

	assign	me4[a] 	= 	me4ap  ;	
	assign	me4[b] 	= 	me4bp  ;	
	assign	me4[c] 	= 	me4cp  ;	

	assign	mb1[a]	=	dmb1[a]; 
	assign	mb1[b] 	=	dmb1[b]; 
	assign	mb1[c] 	=	dmb1[c]; 
	assign	mb1[d] 	=	dmb1[d]; 
		      	        
	assign	mb2[a] 	=	0; 
	assign	mb2[b] 	=	0; 
	assign	mb2[c] 	=	0; 
	assign	mb2[d]	=	0; 
#endif

//#############################################################################
// Madorsky:
// Drift tubes send second trackstub (if available) on the next BX
// Modules below realign this second stub back to nominal BX
	dtbx[0](mb1ap, dmb1[a], dmb1[c], clkp);
	dtbx[1](mb1bp, dmb1[b], dmb1[d], clkp);

#ifdef _BXAON
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

		etaoff1, etaoff2, etaoff3, etaoff4,

		control(0), // BXA enable

		clkp
	);

#endif

	
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

			u12  [i][j] (me1[i], me2[j], Eqme12  (l12+BWEQ12-1, l12), pass12(lX12), pass12(lY12), me1[pYi[i]], pass12(lZ12), me1[pZi[i]]);
			u13  [i][j] (me1[i], me3[j], Eqme13  (l12+BWEQ12-1, l12), pass13(lX12), pass13(lY12), me1[pYi[i]], pass13(lZ12), me1[pZi[i]]);
			u12ov[i][j] (me1[i], me2[j], Eqme12ov(l12ov),             pass12ov(lX12), pass12ov(lY12), me1[pYi[i]], pass12ov(lZ12), me1[pZi[i]]);
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

			u23[i][j] (me2[i], me3[j], Eqme23(l), MinEta[2], MaxEta[2], EtaWindow[2]);
			u24[i][j] (me2[i], me4[j], Eqme24(l), MinEta[3], MaxEta[3], EtaWindow[3]);
			u34[i][j] (me3[i], me4[j], Eqme34(l), MinEta[4], MaxEta[4], EtaWindow[4]);
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
			me2Id1[i], me2Id3[i], me2Id4[i], me2Rank[i],
			control(0),
			clkp
		);

		au3 [i] 
		(
			Eqme13r(l12+BWEQ12P-1, l12),	//EQ 1->3, taken every 12 bits
			(Eqme23r(i+BWEQ234P*2), Eqme23r(i+BWEQ234P), Eqme23r(i)),   // unusual case of extrapolation 3 to 2, bit order is such that tau receives 3 to 2 extrapolation results
			Eqme34r(l23+BWEQ234P-1, l23),     
			me3Id1[i], me3Id2[i], me3Id4[i], me3Rank[i],
			control(0),
			clkp
		);
		au2b[i] 
		(
			Eq2b1r (l2b1+BWEQ2B1P-1, l2b1), 
			Eq2b2r (l2b2+BWEQ2B2P-1, l2b2), 
			Eqme12ovr(l12o+BWEQ12OVP-1, l12o), 
			mb2idb1[i], mb2idb2[i], mb2id1[i], mb2rank[i],
			control(0),
			clkp
		);
	}

// assign pt to all 9 muons 
	ptu2a 
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		me3rr[0], me3rr[1], me3rr[2],
		me4rr[0], me4rr[1], me4rr[2],
		me2Rank[0], me2Id1[0], "2'h1", me2Id3[0], me2Id4[0],
		pt2a, sign2a, mode2a, etaPT2a, FR2a, phi2a
	);

	ptu2b 
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		me3rr[0], me3rr[1], me3rr[2],
		me4rr[0], me4rr[1], me4rr[2],
		me2Rank[1], me2Id1[1], "2'h2", me2Id3[1], me2Id4[1],
		pt2b, sign2b, mode2b, etaPT2b, FR2b, phi2b
	);

	ptu2c 
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		me3rr[0], me3rr[1], me3rr[2],
		me4rr[0], me4rr[1], me4rr[2],
		me2Rank[2], me2Id1[2], "2'h3", me2Id3[2], me2Id4[2],
		pt2c, sign2c, mode2c, etaPT2c, FR2c, phi2c
	);

	ptu3a 
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		me3rr[0], me3rr[1], me3rr[2],
		me4rr[0], me4rr[1], me4rr[2],
		me3Rank[0], me3Id1[0], me3Id2[0], "2'h1", me3Id4[0],
		pt3a, sign3a, mode3a, etaPT3a, FR3a, phi3a
	);

	ptu3b 
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		me3rr[0], me3rr[1], me3rr[2],
		me4rr[0], me4rr[1], me4rr[2],
		me3Rank[1], me3Id1[1], me3Id2[1], "2'h2", me3Id4[1],
		pt3b, sign3b, mode3b, etaPT3b, FR3b, phi3b
	);

	ptu3c 
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		me3rr[0], me3rr[1], me3rr[2],
		me4rr[0], me4rr[1], me4rr[2],
		me3Rank[2], me3Id1[2], me3Id2[2], "2'h3", me3Id4[2],
		pt3c, sign3c, mode3c, etaPT3c, FR3c, phi3c
	);

	ptub2a
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		mb1rr[0], mb1rr[1], mb1rr[2], mb1rr[3], 
		mb2rr[0], mb2rr[1], mb2rr[2], mb2rr[3], 
		mb2rank[0], mb2id1[0], "2'h1", mb2idb1[0], mb2idb2[0],
		ptb2a, signb2a, modeb2a, etaPTb2a, FRb2a, phib2a
	);

	ptub2b
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		mb1rr[0], mb1rr[1], mb1rr[2], mb1rr[3], 
		mb2rr[0], mb2rr[1], mb2rr[2], mb2rr[3], 
		mb2rank[1], mb2id1[1], "2'h2", mb2idb1[1], mb2idb2[1],
		ptb2b, signb2b, modeb2b, etaPTb2b, FRb2b, phib2b
	);

	ptub2c
	(
		me1rr[0], me1rr[1], me1rr[2], me1rr[3], me1rr[4], me1rr[5], 
		me2rr[0], me2rr[1], me2rr[2],
		mb1rr[0], mb1rr[1], mb1rr[2], mb1rr[3], 
		mb2rr[0], mb2rr[1], mb2rr[2], mb2rr[3], 
		mb2rank[2], mb2id1[2], "2'h3", mb2idb1[2], mb2idb2[2],
		ptb2c, signb2c, modeb2c, etaPTb2c, FRb2c, phib2c
	);

// select the best muons simultaneously with PT assignment
	fsuv
	(
		me2Rank[0], me2Id1[0], me2Id3 [0],  me2Id4 [0], 
		me2Rank[1], me2Id1[1], me2Id3 [1],  me2Id4 [1], 
		me2Rank[2], me2Id1[2], me2Id3 [2],  me2Id4 [2], 
		        		   			  	 		    	
		me3Rank[0], me3Id1[0], me3Id2 [0],  me3Id4 [0], 
		me3Rank[1], me3Id1[1], me3Id2 [1],  me3Id4 [1], 
		me3Rank[2], me3Id1[2], me3Id2 [2],  me3Id4 [2], 
		        		   			   	 			    	
		mb2rank[0], mb2id1[0], mb2idb1[0],  mb2idb2[0],  
		mb2rank[1], mb2id1[1], mb2idb1[1],  mb2idb2[1],  
		mb2rank[2], mb2id1[2], mb2idb1[2],  mb2idb2[2],  

////m's contain ids for best tracks, 0->2
		m0, m1, m2                            
	);


	// register all intermediary signals
	always (posedge (clkp))
	begin
// third clock
		m0r =  	 m0;
		m1r =  	 m1;
		m2r =	 m2;

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

		u2aIdr 	 = (me2Id4[0], me2Id3[0], (Signal)"2'h1", me2Id1[0]);
		u2bIdr 	 = (me2Id4[1], me2Id3[1], (Signal)"2'h2", me2Id1[1]);
		u2cIdr   = (me2Id4[2], me2Id3[2], (Signal)"2'h3", me2Id1[2]);
					   
		u3aIdr 	 = (me3Id4[0], (Signal)"2'h1", me3Id2[0], me3Id1[0]);
		u3bIdr 	 = (me3Id4[1], (Signal)"2'h2", me3Id2[1], me3Id1[1]);
		u3cIdr 	 = (me3Id4[2], (Signal)"2'h3", me3Id2[2], me3Id1[2]);
					   
		ub2aIdr	 = (mb2idb2[0], mb2idb1[0], (Signal)"2'h0", (Signal)"2'h0", (Signal)"2'h1", mb2id1[0]);
		ub2bIdr	 = (mb2idb2[1], mb2idb1[1], (Signal)"2'h0", (Signal)"2'h0", (Signal)"2'h2", mb2id1[1]);
		ub2cIdr	 = (mb2idb2[2], mb2idb1[2], (Signal)"2'h0", (Signal)"2'h0", (Signal)"2'h3", mb2id1[2]);


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
	
		
	end

// multiplex the best muons to the output
	mux
	(
		m0r, m1r, m2r,

		pt2ar,  sign2ar,  mode2ar,  etaPT2ar,  FR2ar , phi2ar  ,
		pt2br,  sign2br,  mode2br,  etaPT2br,  FR2br , phi2br  ,
		pt2cr,  sign2cr,  mode2cr,  etaPT2cr,  FR2cr , phi2cr  ,
		pt3ar,  sign3ar,  mode3ar,  etaPT3ar,  FR3ar , phi3ar  ,
		pt3br,  sign3br,  mode3br,  etaPT3br,  FR3br , phi3br  ,
		pt3cr,  sign3cr,  mode3cr,  etaPT3cr,  FR3cr , phi3cr  ,
		ptb2ar, signb2ar, modeb2ar, etaPTb2ar, FRb2ar, phib2ar ,
		ptb2br, signb2br, modeb2br, etaPTb2br, FRb2br, phib2br ,
		ptb2cr, signb2cr, modeb2cr, etaPTb2cr, FRb2cr, phib2cr ,

		u2aIdr,  u2bIdr,  u2cIdr,
		u3aIdr,  u3bIdr,  u3cIdr,
		ub2aIdr, ub2bIdr, ub2cIdr, 
	
		ptH, signH, modeMemH, etaPTH, FRH, phiH,
		ptM, signM, modeMemM, etaPTM, FRM, phiM,
		ptL, signL, modeMemL, etaPTL, FRL, phiL,
		idH, idM, idL
	);

    // assign outputs
	assign	pHp = (FRH, phiH, ptH, signH, modeMemH, etaPTH);
	assign	pMp = (FRM, phiM, ptM, signM, modeMemM, etaPTM);
	assign	pLp = (FRL, phiL, ptL, signL, modeMemL, etaPTL);
	assign	idHp = idH;
	assign	idMp = idM;
	assign	idLp = idL;

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


