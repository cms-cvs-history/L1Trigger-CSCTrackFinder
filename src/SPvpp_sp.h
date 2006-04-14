#ifndef CSCTrackFinder_SPvpp_sp_h
#define CSCTrackFinder_SPvpp_sp_h

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>

#include <L1Trigger/CSCTrackFinder/src/spbits.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_bxa.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_etau12.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu12.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu12_ov.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu13.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu23_24_34.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu2b1.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu2b2.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_fsu.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_MuonMux.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_ptmb.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_ptme.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_tau2.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_tau2b.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_tau3.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_dtbx.h>

class SPvpp_sp : public module
{
public:
	void operator ()                                                 
	(                                                                
		Signal me1ap, Signal me1bp, Signal me1cp, Signal me1dp, Signal me1ep, Signal me1fp,
		Signal me2ap, Signal me2bp, Signal me2cp,
		Signal me3ap, Signal me3bp, Signal me3cp,
		Signal me4ap, Signal me4bp, Signal me4cp,
		Signal mb1ap, Signal mb1bp, 
		Signal pHp,	  Signal pMp,	Signal pLp,
		Signal idHp,  Signal idMp,	Signal idLp,
		Signal date,
		Signal mneta0, Signal mneta1, Signal mneta2, Signal mneta3, Signal mneta4, Signal mneta5, Signal mneta6, Signal mneta7, 
		Signal mxeta0, Signal mxeta1, Signal mxeta2, Signal mxeta3, Signal mxeta4, Signal mxeta5, Signal mxeta6, Signal mxeta7, 
		Signal etawn0, Signal etawn1, Signal etawn2, Signal etawn3, Signal etawn4, Signal etawn5, 
		Signal etaoff1, Signal etaoff2, Signal etaoff3, Signal etaoff4,
		Signal control,
		Signal clkp
	);                                                               

	memory me1r, me1rr;
	memory me2r, me2rr;
	memory me3r, me3rr;
	memory me4r, me4rr;
		        
	memory mb1r, mb1rr; 
	memory mb2r, mb2rr; 


	// wires --------------------------------------------------------------
	Signal me1[NSEG1];
	Signal me2[NSEG234];
	Signal me3[NSEG234]; 
	Signal me4[NSEG234];
	Signal mb1[NSEG12B];
	Signal mb2[NSEG12B]; 
	Signal dmb1[NSEG12B];

	Signal pass12, pass12ov, pass13;
	Signal Eqme12,  Eqme13,  Eqme12ov,  Eqme23,  Eqme24,  Eqme34,  Eq2b2,  Eq2b1;
	Signal me2Id1[NTAU],  me3Id1[NTAU],  mb2idb1[NTAU],  me2Id3[NTAU],  me3Id2[NTAU],  mb2idb2[NTAU],  me2Id4[NTAU],  me3Id4[NTAU],  mb2id1[NTAU],  me2Rank[NTAU],  me3Rank[NTAU],  mb2rank[NTAU];

	Signal pt2a,    pt2b,    pt2c,    pt3a,    pt3b,    pt3c,    ptb2a,    ptb2b,    ptb2c;
	Signal sign2a,  sign2b,  sign2c,  sign3a,  sign3b,  sign3c,  signb2a,  signb2b,  signb2c;
	Signal mode2a,  mode2b,  mode2c,  mode3a,  mode3b,  mode3c,  modeb2a,  modeb2b,  modeb2c;  
	Signal etaPT2a, etaPT2b, etaPT2c, etaPT3a, etaPT3b, etaPT3c, etaPTb2a, etaPTb2b, etaPTb2c;

	Signal m0, m1, m2;

	Signal ptH, ptM, ptL;
	Signal signH, signM, signL;
	Signal modeMemH, modeMemM, modeMemL;
	Signal etaPTH, etaPTM, etaPTL;

	Signal FR2a, FR2b, FR2c, FR3a, FR3b, FR3c, FRb2a, FRb2b, FRb2c;
	Signal phi2a, phi2b, phi2c, phi3a, phi3b, phi3c, phib2a, phib2b, phib2c;
	
	Signal FRH, FRM, FRL, phiH, phiM, phiL;
	Signal idH, idM, idL;

	Signal MinEta[8], MaxEta[8], EtaWindow[6];

	// regs ----------------------------------------------------------------


	Signal Eqme12r, Eqme13r, Eqme12ovr, Eqme23r, Eqme24r, Eqme34r, Eq2b1r, Eq2b2r;
	Signal u2aIdr, u2bIdr, u2cIdr, u3aIdr, u3bIdr, u3cIdr, ub2aIdr, ub2bIdr, ub2cIdr;

	Signal pt2ar,    pt2br,    pt2cr,    pt3ar,    pt3br,    pt3cr,    ptb2ar,    ptb2br,    ptb2cr;
	Signal sign2ar,  sign2br,  sign2cr,  sign3ar,  sign3br,  sign3cr,  signb2ar,  signb2br,  signb2cr;
	Signal mode2ar,  mode2br,  mode2cr,  mode3ar,  mode3br,  mode3cr,  modeb2ar,  modeb2br,  modeb2cr;  
	Signal etaPT2ar, etaPT2br, etaPT2cr, etaPT3ar, etaPT3br, etaPT3cr, etaPTb2ar, etaPTb2br, etaPTb2cr;

	Signal m0r, m1r, m2r;

	Signal FR2ar, FR2br, FR2cr, FR3ar, FR3br, FR3cr, FRb2ar, FRb2br, FRb2cr;
	Signal phi2ar, phi2br, phi2cr, phi3ar, phi3br, phi3cr, phib2ar, phib2br, phib2cr;

	Signal ir;

	//modules -----------------------------------------------------------------

	SPvpp_ptme ptu2a;
	SPvpp_ptme ptu2b;
	SPvpp_ptme ptu2c;

	SPvpp_ptme ptu3a;
	SPvpp_ptme ptu3b;
	SPvpp_ptme ptu3c;

	SPvpp_ptmb ptub2a;
	SPvpp_ptmb ptub2b;
	SPvpp_ptmb ptub2c;


	SPvpp_fsu fsuv;

	SPvpp_MuonMux mux;

	SPvpp_etau12  etu12  [6][3];
	SPvpp_etau12  etu12ov[6][3];
	SPvpp_etau12  etu13  [6][3];

	SPvpp_eu12    u12  [6][3];
	SPvpp_eu13    u13  [6][3];
	SPvpp_eu12_ov u12ov[6][3];

	SPvpp_eu23_24_34 u23[3][3];
	SPvpp_eu23_24_34 u24[3][3];
	SPvpp_eu23_24_34 u34[3][3];

	SPvpp_eu2b1 u2b1[3][4];
	SPvpp_eu2b2 u2b2[3][4];

	SPvpp_tau2  au2 [3];
	SPvpp_tau2b au2b[3];
	SPvpp_tau3  au3 [3];

	SPvpp_bxa bxa;
	SPvpp_dtbx dtbx[2];

};

#endif
