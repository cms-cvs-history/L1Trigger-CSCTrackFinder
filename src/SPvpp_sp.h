#ifndef _FILE_SPvpp_sp_FILE_
#define _FILE_SPvpp_sp_FILE_
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
#include <L1Trigger/CSCTrackFinder/src/SPvpp_bxcorr.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu23a.h>

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
		Signal mindphi,
		Signal mindeta_acc, Signal maxdeta_acc, Signal maxdphi_acc,
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

	Signal me1bi[NSEG1+1]	 ; 
	Signal me2bi[NSEG234+1]; 
	Signal me3bi[NSEG234+1]; 
	Signal me4bi[NSEG234+1]; 
	Signal mb1bi[NSEG12B+1]; 
	Signal mb2bi[NSEG12B+1]; 

	Signal dmb1[NSEG12B];

	Signal pass12, pass12ov, pass13;
	Signal Eqme12,  Eqme13,  Eqme12ov,  Eqme23,  Eqme24,  Eqme34,  Eq2b2,  Eq2b1, Eqme23a, Eqme23ar;
	Signal me2Id1[NTAU],  me3Id1[NTAU],  mb2idb1[NTAU],  me2Id3[NTAU],  me3Id2[NTAU],  mb2idb2[NTAU],  me2Id4[NTAU],  me3Id4[NTAU],  mb2id1[NTAU],  me2Rank[NTAU],  me3Rank[NTAU],  mb2rank[NTAU];
	memory me2Id1r, me3Id1r, mb2idb1r, me2Id3r, me3Id2r, mb2idb2r, me2Id4r, me3Id4r, mb2id1r, me2Rankr, me3Rankr, mb2rankr;
	memory me2Id1rr, me3Id1rr, mb2idb1rr, me2Id3rr, me3Id2rr, mb2idb2rr, me2Id4rr, me3Id4rr, mb2id1rr;
	Signal me2Rankrr[NTAU],    me3Rankrr[NTAU],    mb2rankrr[NTAU];
	memory me2Rankrrr,   me3Rankrrr,   mb2rankrrr;
	memory me2Rankrrrr,  me3Rankrrrr,  mb2rankrrrr;
	memory me2Rankrrrrr, me3Rankrrrrr, mb2rankrrrrr;

	Signal pt2a,    pt2b,    pt2c,    pt3a,    pt3b,    pt3c,    ptb2a,    ptb2b,    ptb2c;
	Signal sign2a,  sign2b,  sign2c,  sign3a,  sign3b,  sign3c,  signb2a,  signb2b,  signb2c;
	Signal mode2a,  mode2b,  mode2c,  mode3a,  mode3b,  mode3c,  modeb2a,  modeb2b,  modeb2c;  
	Signal etaPT2a, etaPT2b, etaPT2c, etaPT3a, etaPT3b, etaPT3c, etaPTb2a, etaPTb2b, etaPTb2c;

	Signal rankH, rankM, rankL;

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
	Signal u2aId, u2bId, u2cId, u3aId, u3bId, u3cId, ub2aId, ub2bId, ub2cId;
	Signal u2aIdt, u2bIdt, u2cIdt, u3aIdt, u3bIdt, u3cIdt, ub2aIdt, ub2bIdt, ub2cIdt;
	Signal u2aIdr, u2bIdr, u2cIdr, u3aIdr, u3bIdr, u3cIdr, ub2aIdr, ub2bIdr, ub2cIdr;
	Signal u2aIdrr, u2bIdrr, u2cIdrr, u3aIdrr, u3bIdrr, u3cIdrr, ub2aIdrr, ub2bIdrr, ub2cIdrr;

	Signal pt2ar,    pt2br,    pt2cr,    pt3ar,    pt3br,    pt3cr,    ptb2ar,    ptb2br,    ptb2cr;
	Signal sign2ar,  sign2br,  sign2cr,  sign3ar,  sign3br,  sign3cr,  signb2ar,  signb2br,  signb2cr;
	Signal mode2ar,  mode2br,  mode2cr,  mode3ar,  mode3br,  mode3cr,  modeb2ar,  modeb2br,  modeb2cr;  
	Signal etaPT2ar, etaPT2br, etaPT2cr, etaPT3ar, etaPT3br, etaPT3cr, etaPTb2ar, etaPTb2br, etaPTb2cr;

	Signal FR2ar, FR2br, FR2cr, FR3ar, FR3br, FR3cr, FRb2ar, FRb2br, FRb2cr;
	Signal phi2ar, phi2br, phi2cr, phi3ar, phi3br, phi3cr, phib2ar, phib2br, phib2cr;

	Signal pt2arr,   pt2brr,   pt2crr,   pt3arr,   pt3brr,   pt3crr,   ptb2arr,   ptb2brr,   ptb2crr;
	Signal sign2arr, sign2brr, sign2crr, sign3arr, sign3brr, sign3crr, signb2arr, signb2brr, signb2crr;
	Signal mode2arr, mode2brr, mode2crr, mode3arr, mode3brr, mode3crr, modeb2arr, modeb2brr, modeb2crr;  
	Signal etaPT2arr,etaPT2brr,etaPT2crr,etaPT3arr,etaPT3brr,etaPT3crr,etaPTb2arr,etaPTb2brr,etaPTb2crr;

	Signal FR2arr,FR2brr,FR2crr,FR3arr,FR3brr,FR3crr,FRb2arr,FRb2brr,FRb2crr;
	Signal phi2arr,phi2brr,phi2crr,phi3arr,phi3brr,phi3crr,phib2arr,phib2brr,phib2crr;

	Signal ir;

	memory me1bir;
	memory me2bir; 
	memory me3bir; 
	memory me4bir; 
	memory mb1bir; 
	memory mb2bir; 

	Signal	
		pt2arrr,  sign2arrr,  mode2arrr,  etaPT2arrr,  FR2arrr , phi2arrr  ,
		pt2brrr,  sign2brrr,  mode2brrr,  etaPT2brrr,  FR2brrr , phi2brrr  ,
		pt2crrr,  sign2crrr,  mode2crrr,  etaPT2crrr,  FR2crrr , phi2crrr  ,
		pt3arrr,  sign3arrr,  mode3arrr,  etaPT3arrr,  FR3arrr , phi3arrr  ,
		pt3brrr,  sign3brrr,  mode3brrr,  etaPT3brrr,  FR3brrr , phi3brrr  ,
		pt3crrr,  sign3crrr,  mode3crrr,  etaPT3crrr,  FR3crrr , phi3crrr  ,
		ptb2arrr, signb2arrr, modeb2arrr, etaPTb2arrr, FRb2arrr, phib2arrr ,
		ptb2brrr, signb2brrr, modeb2brrr, etaPTb2brrr, FRb2brrr, phib2brrr ,
		ptb2crrr, signb2crrr, modeb2crrr, etaPTb2crrr, FRb2crrr, phib2crrr ,
		u2aIdrrr,  u2bIdrrr,  u2cIdrrr,
		u3aIdrrr,  u3bIdrrr,  u3cIdrrr,
		ub2aIdrrr, ub2bIdrrr, ub2cIdrrr;


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

	SPvpp_eu23a u23a[3][3];

	SPvpp_eu2b1 u2b1[3][4];
	SPvpp_eu2b2 u2b2[3][4];

	SPvpp_tau2  au2 [3];
	SPvpp_tau2b au2b[3];
	SPvpp_tau3  au3 [3];

	SPvpp_bxa bxa;
	SPvpp_dtbx dtbx[2];
	SPvpp_bxcorr bxcorr;

};

#endif
