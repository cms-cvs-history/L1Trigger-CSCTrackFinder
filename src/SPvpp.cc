/**
\class SPvpp

Runs Verilog++ model of Sector Processor

\author A. Madorsky
*/

#include <L1Trigger/CSCTrackFinder/src/SPvpp.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>

#define DTBXDEBUG
#ifdef MYDEBUG
#include <math.h>
#include <iostream>
#endif

void SPvpp::SP
(
	unsigned me1aValidp, unsigned me1aQp, unsigned me1aEtap, unsigned me1aPhip, unsigned me1aCSCidp,
	unsigned me1bValidp, unsigned me1bQp, unsigned me1bEtap, unsigned me1bPhip, unsigned me1bCSCidp,
	unsigned me1cValidp, unsigned me1cQp, unsigned me1cEtap, unsigned me1cPhip, unsigned me1cCSCidp,
	unsigned me1dValidp, unsigned me1dQp, unsigned me1dEtap, unsigned me1dPhip, unsigned me1dCSCidp,
	unsigned me1eValidp, unsigned me1eQp, unsigned me1eEtap, unsigned me1ePhip, unsigned me1eCSCidp,
	unsigned me1fValidp, unsigned me1fQp, unsigned me1fEtap, unsigned me1fPhip, unsigned me1fCSCidp,

	unsigned me2aValidp, unsigned me2aQp, unsigned me2aEtap, unsigned me2aPhip,
	unsigned me2bValidp, unsigned me2bQp, unsigned me2bEtap, unsigned me2bPhip,
	unsigned me2cValidp, unsigned me2cQp, unsigned me2cEtap, unsigned me2cPhip,

	unsigned me3aValidp, unsigned me3aQp, unsigned me3aEtap, unsigned me3aPhip,
	unsigned me3bValidp, unsigned me3bQp, unsigned me3bEtap, unsigned me3bPhip,
	unsigned me3cValidp, unsigned me3cQp, unsigned me3cEtap, unsigned me3cPhip,

	unsigned me4aValidp, unsigned me4aQp, unsigned me4aEtap, unsigned me4aPhip,
	unsigned me4bValidp, unsigned me4bQp, unsigned me4bEtap, unsigned me4bPhip,
	unsigned me4cValidp, unsigned me4cQp, unsigned me4cEtap, unsigned me4cPhip,

	unsigned mb1aValidp, unsigned mb1aQp, unsigned mb1aPhip,
	unsigned mb1bValidp, unsigned mb1bQp, unsigned mb1bPhip,
	unsigned mb1cValidp, unsigned mb1cQp, unsigned mb1cPhip,
	unsigned mb1dValidp, unsigned mb1dQp, unsigned mb1dPhip,

	unsigned mb2aValidp, unsigned mb2aQp, unsigned mb2aPhip,
	unsigned mb2bValidp, unsigned mb2bQp, unsigned mb2bPhip,
	unsigned mb2cValidp, unsigned mb2cQp, unsigned mb2cPhip,
	unsigned mb2dValidp, unsigned mb2dQp, unsigned mb2dPhip,

	unsigned& ptHp, unsigned& signHp, unsigned& modeMemHp, unsigned& etaPTHp, unsigned& FRHp, unsigned& phiHp,
	unsigned& ptMp, unsigned& signMp, unsigned& modeMemMp, unsigned& etaPTMp, unsigned& FRMp, unsigned& phiMp,
	unsigned& ptLp, unsigned& signLp, unsigned& modeMemLp, unsigned& etaPTLp, unsigned& FRLp, unsigned& phiLp,

	unsigned& me1idH, unsigned& me2idH, unsigned& me3idH, unsigned& me4idH, unsigned& mb1idH, unsigned& mb2idH,
	unsigned& me1idM, unsigned& me2idM, unsigned& me3idM, unsigned& me4idM, unsigned& mb1idM, unsigned& mb2idM,
	unsigned& me1idL, unsigned& me2idL, unsigned& me3idL, unsigned& me4idL, unsigned& mb1idL, unsigned& mb2idL,

	unsigned mneta0p, unsigned mneta1p, unsigned mneta2p, unsigned mneta3p, unsigned mneta4p, unsigned mneta5p, unsigned mneta6p, unsigned mneta7p, 
	unsigned mxeta0p, unsigned mxeta1p, unsigned mxeta2p, unsigned mxeta3p, unsigned mxeta4p, unsigned mxeta5p, unsigned mxeta6p, unsigned mxeta7p, 
	unsigned etawn0p, unsigned etawn1p, unsigned etawn2p, unsigned etawn3p, unsigned etawn4p, unsigned etawn5p, 

	unsigned etaoff1p, unsigned etaoff2p, unsigned etaoff3p, unsigned etaoff4p,
	unsigned controlp

)
{
 	// create bit indexes
	int beta = BWPHI + BWETAIN;
	int bq   = beta + BWQ;
	int bcscid = bq + BWCSCID;
	int bvalid = bcscid + BWVALID;
	static int zeroEvent = 0;
	static int blanks = 0;
	static bool isItOutput = 0;
	static bool DTB = 0;
	loop ++;
	static int stubCount;

// create delay of one clock for endcap data
	me1ar = me1ap; me1br = me1bp; me1cr = me1cp; me1dr = me1dp; me1er = me1ep; me1fr = me1fp;
	me2ar = me2ap; me2br = me2bp; me2cr = me2cp;
	me3ar = me3ap; me3br = me3bp; me3cr = me3cp;
	me4ar = me4ap; me4br = me4bp; me4cr = me4cp;

	me1ap(bvalid-1) = me1aValidp; me1ap(BWPHI-1, 0) = me1aPhip; me1ap(beta-1, BWPHI) = me1aEtap; me1ap(bq-1, beta) = me1aQp; me1ap(bcscid-1, bq) = me1aCSCidp;
	me1bp(bvalid-1) = me1bValidp; me1bp(BWPHI-1, 0) = me1bPhip; me1bp(beta-1, BWPHI) = me1bEtap; me1bp(bq-1, beta) = me1bQp; me1bp(bcscid-1, bq) = me1bCSCidp;
	me1cp(bvalid-1) = me1cValidp; me1cp(BWPHI-1, 0) = me1cPhip; me1cp(beta-1, BWPHI) = me1cEtap; me1cp(bq-1, beta) = me1cQp; me1cp(bcscid-1, bq) = me1cCSCidp;
	me1dp(bvalid-1) = me1dValidp; me1dp(BWPHI-1, 0) = me1dPhip; me1dp(beta-1, BWPHI) = me1dEtap; me1dp(bq-1, beta) = me1dQp; me1dp(bcscid-1, bq) = me1dCSCidp;
	me1ep(bvalid-1) = me1eValidp; me1ep(BWPHI-1, 0) = me1ePhip; me1ep(beta-1, BWPHI) = me1eEtap; me1ep(bq-1, beta) = me1eQp; me1ep(bcscid-1, bq) = me1eCSCidp;
	me1fp(bvalid-1) = me1fValidp; me1fp(BWPHI-1, 0) = me1fPhip; me1fp(beta-1, BWPHI) = me1fEtap; me1fp(bq-1, beta) = me1fQp; me1fp(bcscid-1, bq) = me1fCSCidp;

	me2ap(bvalid-1) = me2aValidp; me2ap(BWPHI-1, 0) = me2aPhip; me2ap(beta-1, BWPHI) = me2aEtap; me2ap(bq-1, beta) = me2aQp;
	me2bp(bvalid-1) = me2bValidp; me2bp(BWPHI-1, 0) = me2bPhip; me2bp(beta-1, BWPHI) = me2bEtap; me2bp(bq-1, beta) = me2bQp;
	me2cp(bvalid-1) = me2cValidp; me2cp(BWPHI-1, 0) = me2cPhip; me2cp(beta-1, BWPHI) = me2cEtap; me2cp(bq-1, beta) = me2cQp;

	me3ap(bvalid-1) = me3aValidp; me3ap(BWPHI-1, 0) = me3aPhip; me3ap(beta-1, BWPHI) = me3aEtap; me3ap(bq-1, beta) = me3aQp;
	me3bp(bvalid-1) = me3bValidp; me3bp(BWPHI-1, 0) = me3bPhip; me3bp(beta-1, BWPHI) = me3bEtap; me3bp(bq-1, beta) = me3bQp;
	me3cp(bvalid-1) = me3cValidp; me3cp(BWPHI-1, 0) = me3cPhip; me3cp(beta-1, BWPHI) = me3cEtap; me3cp(bq-1, beta) = me3cQp;

	me4ap(bvalid-1) = me4aValidp; me4ap(BWPHI-1, 0) = me4aPhip; me4ap(beta-1, BWPHI) = me4aEtap; me4ap(bq-1, beta) = me4aQp;
	me4bp(bvalid-1) = me4bValidp; me4bp(BWPHI-1, 0) = me4bPhip; me4bp(beta-1, BWPHI) = me4bEtap; me4bp(bq-1, beta) = me4bQp;
	me4cp(bvalid-1) = me4cValidp; me4cp(BWPHI-1, 0) = me4cPhip; me4cp(beta-1, BWPHI) = me4cEtap; me4cp(bq-1, beta) = me4cQp;

	if      (mb1aQp != 0) {mb1ap(BWPHI+BWQB) = 0; mb1ap(BWPHI-1, 0) = mb1aPhip; mb1ap(BWPHI+BWQB-1, BWPHI) = mb1aQp; if(mb1aQr != 0) cout<<"killing a\n";}
	else if (mb1aQr != 0) {mb1ap(BWPHI+BWQB) = 1; mb1ap(BWPHI-1, 0) = mb1aPhir; mb1ap(BWPHI+BWQB-1, BWPHI) = mb1aQr;}
	else mb1ap = 0;

	if      (mb1bQp != 0) {mb1bp(BWPHI+BWQB) = 0; mb1bp(BWPHI-1, 0) = mb1bPhip; mb1bp(BWPHI+BWQB-1, BWPHI) = mb1bQp; if(mb1bQr != 0) cout<<"killing b\n";}
	else if (mb1bQr != 0) {mb1bp(BWPHI+BWQB) = 1; mb1bp(BWPHI-1, 0) = mb1bPhir; mb1bp(BWPHI+BWQB-1, BWPHI) = mb1bQr;}
	else mb1bp = 0;

	mb1aPhir = mb1cPhip; mb1aQr = mb1cQp;
	mb1bPhir = mb1dPhip; mb1bQr = mb1dQp;

	mneta0  = mneta0p; 
	mneta1  = mneta1p; 
	mneta2  = mneta2p; 
	mneta3  = mneta3p; 
	mneta4  = mneta4p; 
	mneta5  = mneta5p; 
	mneta6  = mneta6p; 
	mneta7  = mneta7p; 
	 	   	   	   
	mxeta0  = mxeta0p; 
	mxeta1  = mxeta1p; 
	mxeta2  = mxeta2p; 
	mxeta3  = mxeta3p; 
	mxeta4  = mxeta4p; 
	mxeta5  = mxeta5p; 
	mxeta6  = mxeta6p; 
	mxeta7  = mxeta7p; 
	 	   	   	   
	etawn0  = etawn0p; 
	etawn1  = etawn1p; 
	etawn2  = etawn2p; 
	etawn3  = etawn3p; 
	etawn4  = etawn4p; 
	etawn5  = etawn5p; 

	control = controlp;
	
	
for (int i = 1; i >= 0; i--)
{
		clkp = i;
		beginsystem
			me1ap.wire(BWMEIN-1,0,"me1ap"); // {FR, q[3:0], am, eta[6:0], phi[11:0]}
		me1bp.wire(BWMEIN-1,0,"me1bp");
		me1cp.wire(BWMEIN-1,0,"me1cp");
		me1dp.wire(BWMEIN-1,0,"me1dp");
		me1ep.wire(BWMEIN-1,0,"me1ep");
		me1fp.wire(BWMEIN-1,0,"me1fp");

		me2ap.wire(BWMEIN-1,0,"me2ap");
		me2bp.wire(BWMEIN-1,0,"me2bp");
		me2cp.wire(BWMEIN-1,0,"me2cp");

		me3ap.wire(BWMEIN-1,0,"me3ap");
		me3bp.wire(BWMEIN-1,0,"me3bp");
		me3cp.wire(BWMEIN-1,0,"me3cp");

		me4ap.wire(BWMEIN-1,0,"me4ap");
		me4bp.wire(BWMEIN-1,0,"me4bp");
		me4cp.wire(BWMEIN-1,0,"me4cp");

		Wire_(me1ar, BWMEIN-1,0);
		Wire_(me1br, BWMEIN-1,0);
		Wire_(me1cr, BWMEIN-1,0);
		Wire_(me1dr, BWMEIN-1,0);
		Wire_(me1er, BWMEIN-1,0);
		Wire_(me1fr, BWMEIN-1,0);

		Wire_(me2ar, BWMEIN-1,0);
		Wire_(me2br, BWMEIN-1,0);
		Wire_(me2cr, BWMEIN-1,0);

		Wire_(me3ar, BWMEIN-1,0);
		Wire_(me3br, BWMEIN-1,0);
		Wire_(me3cr, BWMEIN-1,0);

		Wire_(me4ar, BWMEIN-1,0);
		Wire_(me4br, BWMEIN-1,0);
		Wire_(me4cr, BWMEIN-1,0);

		mb1ap.wire(BWMBIN-1,0,"mb1ap"); // {FL, q[2:0], phi[11:0]}
		mb1bp.wire(BWMBIN-1,0,"mb1cp");

		pHp.wire(BWPOUT-1,0,"pHp"); // {FR, phi[11:0], pt[12:0], sign, mode[3:0], eta[3:0]}
		pMp.wire(BWPOUT-1,0,"pMp");
		pLp.wire(BWPOUT-1,0,"pLp");

		idHp.wire(MUIDSIZE - 1, 0, "idHp");
		idMp.wire(MUIDSIZE - 1, 0, "idHp");
		idLp.wire(MUIDSIZE - 1, 0, "idHp");

		Wire_(date, 15,0);
		Wire_(mneta0, BWETAIN-1, 0); 
		Wire_(mneta1, BWETAIN-1, 0); 
		Wire_(mneta2, BWETAIN-1, 0); 
		Wire_(mneta3, BWETAIN-1, 0); 
		Wire_(mneta4, BWETAIN-1, 0); 
		Wire_(mneta5, BWETAIN-1, 0); 
		Wire_(mneta6, BWETAIN-1, 0); 
		Wire_(mneta7, BWETAIN-1, 0); 
		   		 					  
		Wire_(mxeta0, BWETAIN-1, 0); 
		Wire_(mxeta1, BWETAIN-1, 0); 
		Wire_(mxeta2, BWETAIN-1, 0); 
		Wire_(mxeta3, BWETAIN-1, 0); 
		Wire_(mxeta4, BWETAIN-1, 0); 
		Wire_(mxeta5, BWETAIN-1, 0); 
		Wire_(mxeta6, BWETAIN-1, 0); 
		Wire_(mxeta7, BWETAIN-1, 0); 
		   				 
		Wire_(etawn0, BWETAIN, 0); 
		Wire_(etawn1, BWETAIN, 0); 
		Wire_(etawn2, BWETAIN, 0); 
		Wire_(etawn3, BWETAIN, 0); 
		Wire_(etawn4, BWETAIN, 0); 
		Wire_(etawn5, BWETAIN, 0); 

		Wire_(control, 15, 0);
		clkp.wire("clkp");

		spvpp.init("spc", "spvpp");
		spvpp
		(
			me1ar, me1br, me1cr, me1dr, me1er, me1fr,
			me2ar, me2br, me2cr,
			me3ar, me3br, me3cr,
			me4ar, me4br, me4cr,

			mb1ap, mb1bp,
			pHp,   pMp,	  pLp,
			idHp,  idMp,  idLp,

			date,
			mneta0,	mneta1,	mneta2,	mneta3,	mneta4,	mneta5,	mneta6,	mneta7,	 		
			mxeta0,	mxeta1,	mxeta2,	mxeta3,	mxeta4,	mxeta5,	mxeta6,	mxeta7,
			etawn0,	etawn1,	etawn2,	etawn3,	etawn4,	etawn5,

			control,

			clkp
		);

		int bp = 0;

		etaPTHp = pHp(BWETAOUT-1, bp).getint();
		etaPTMp = pMp(BWETAOUT-1, bp).getint();
		etaPTLp = pLp(BWETAOUT-1, bp).getint();

		bp += BWETAOUT;

		modeMemHp = pHp(bp+BWMODE-1, bp).getint();
		modeMemMp = pMp(bp+BWMODE-1, bp).getint();
		modeMemLp = pLp(bp+BWMODE-1, bp).getint();

		bp += BWMODE;

		signHp = pHp(bp).getint();
		signMp = pMp(bp).getint();
		signLp = pLp(bp).getint();

		bp += BWSIGN;

		ptHp = pHp(bp+BWPT-1, bp).getint();
		ptMp = pMp(bp+BWPT-1, bp).getint();
		ptLp = pLp(bp+BWPT-1, bp).getint();

		bp += BWPT;

		phiHp = pHp(bp+BWPHIOUT-1, bp).getint();
		phiMp = pMp(bp+BWPHIOUT-1, bp).getint();
		phiLp = pLp(bp+BWPHIOUT-1, bp).getint();

		bp += BWPHIOUT;

		FRHp = pHp(bp).getint();
		FRMp = pMp(bp).getint();
		FRLp = pLp(bp).getint();


		//Retrieve ints from id code
		bp = 0;

		me1idH = idHp(BWBXID-1, bp).getint();		
		me1idM = idMp(BWBXID-1, bp).getint();
		me1idL = idLp(BWBXID-1, bp).getint();

		bp += BWBXID;

		me2idH = idHp(bp + BWBXID - 1, bp).getint();	
		me2idM = idMp(bp + BWBXID - 1, bp).getint();
		me2idL = idLp(bp + BWBXID - 1, bp).getint();

		bp += BWBXID;

		me3idH = idHp(bp + BWBXID - 1, bp).getint();	
		me3idM = idMp(bp + BWBXID - 1, bp).getint();
		me3idL = idLp(bp + BWBXID - 1, bp).getint();

		bp += BWBXID;

		me4idH = idHp(bp + BWBXID - 1, bp).getint();	
		me4idM = idMp(bp + BWBXID - 1, bp).getint();
		me4idL = idLp(bp + BWBXID - 1, bp).getint();

		bp += BWBXID;

		mb1idH = idHp(bp + BWBXID - 1, bp).getint();
		mb1idM = idMp(bp + BWBXID - 1, bp).getint();
		mb1idL = idLp(bp + BWBXID - 1, bp).getint();

		bp += BWBXID;

		mb2idH = idHp(bp + BWBXID - 1, bp).getint();
		mb2idM = idMp(bp + BWBXID - 1, bp).getint();
		mb2idL = idLp(bp + BWBXID - 1, bp).getint();

		endsystem
}
#ifdef DTBXDEBUG


if( etaPTHp == 0 && etaPTMp == 0 && etaPTLp == 0)
{
	isItOutput = 0;
}

if( me2aQp != 0 || me2bQp != 0 || me2cQp != 0 || me3aQp != 0 || me3bQp != 0 || me3cQp != 0 || etaPTHp != 0 || etaPTMp != 0 || etaPTLp != 0) 
{	
	zeroEvent = 0;
	if(etaPTMp != 0 || etaPTHp != 0 || etaPTLp != 0)
	{
		isItOutput = 1;
	} else {
		isItOutput = 0;
	}
} else {
	zeroEvent++;
//	cout << "Count :" << zeroEvent << endl;
}
if(zeroEvent == 13)
{
	blanks++;
	cout << " Incomplete Track: " << blanks << endl;
}

stubCount = 0;
if( me1aQp != 0 )  	stubCount++;
if( me1bQp != 0 )  	stubCount++;
if( me1cQp != 0 )  	stubCount++;
if( me1dQp != 0 )  	stubCount++;
if( me1eQp != 0 )  	stubCount++;
if( me1fQp != 0 )  	stubCount++;
if( me2aQp != 0 )  	stubCount++;
if( me2bQp != 0 )  	stubCount++;
if( me2cQp != 0 ) 	stubCount++;
if( me3aQp != 0 )  	stubCount++;
if( me3bQp != 0 )  	stubCount++;
if( me3cQp != 0 )  	stubCount++;
if( me4aQp != 0 )  	stubCount++;
if( me4bQp != 0 ) 	stubCount++; 
if( me4cQp != 0 ) 	stubCount++;



if((mb1aQp != 0 || mb1bQp != 0 || mb1cQp != 0 || mb1dQp != 0 || mb2aQp != 0 || mb2bQp != 0 || mb2cQp != 0 || mb2dQp != 0 ) || (DTB == 1 && isItOutput == 1) )
{
		if(DTB == 0)
		{
			DTB = 1;
		} else {
			DTB = 0;
		}
	
      	cout << dec << "\t \t \t" << loop << " " << loop << " " << loop << endl
      	<< "dtbx " << endl 

      	<< "#### INPUTS ####" << endl
 
      	<< me1aValidp << " " <<  me1aQp << " " << me1aPhip << " " << me1aEtap << " " <<  me1aCSCidp << endl
      	<< me1bValidp << " " <<  me1bQp << " " << me1bPhip << " " << me1bEtap << " " <<  me1bCSCidp << endl
      	<< me1cValidp << " " <<  me1cQp << " " << me1cPhip << " " << me1cEtap << " " <<  me1cCSCidp << endl
      	<< me1dValidp << " " <<  me1dQp << " " << me1dPhip << " " << me1dEtap << " " <<  me1dCSCidp << endl
      	<< me1eValidp << " " <<  me1eQp << " " << me1ePhip << " " << me1eEtap << " " <<  me1eCSCidp << endl
      	<< me1fValidp << " " <<  me1fQp << " " << me1fPhip << " " << me1fEtap << " " <<  me1fCSCidp << endl << endl

      	<< me2aValidp << " " <<  me2aQp << " " << me2aPhip << " " << me2aEtap << " 0" << endl
      	<< me2bValidp << " " <<  me2bQp << " " << me2bPhip << " " << me2bEtap << " 0" << endl
      	<< me2cValidp << " " <<  me2cQp << " " << me2cPhip << " " << me2cEtap << " 0" << endl << endl

      	<< me3aValidp << " " <<  me3aQp << " " << me3aPhip << " " << me3aEtap << " 0" << endl
      	<< me3bValidp << " " <<  me3bQp << " " << me3bPhip << " " << me3bEtap << " 0" << endl
      	<< me3cValidp << " " <<  me3cQp << " " << me3cPhip << " " << me3cEtap << " 0" << endl << endl

      	<< me4aValidp << " " <<  me4aQp << " " << me4aPhip << " " << me4aEtap << " 0" << endl
      	<< me4bValidp << " " <<  me4bQp << " " << me4bPhip << " " << me4bEtap << " 0" << endl
      	<< me4cValidp << " " <<  me4cQp << " " << me4cPhip << " " << me4cEtap << " 0" << endl << endl
		
	   	<< mb1aValidp << " " << mb1aQp << " " << mb1aPhip << endl
		<< mb1bValidp << " " << mb1bQp << " " << mb1bPhip << endl
		<< mb1cValidp << " " << mb1cQp << " " << mb1cPhip << endl
		<< mb1dValidp << " " << mb1dQp << " " << mb1dPhip << endl << endl

		<< mb2aValidp << " " << mb2aQp << " " << mb2aPhip << endl
		<< mb2bValidp << " " << mb2bQp << " " << mb2bPhip << endl
		<< mb2cValidp << " " << mb2cQp << " " << mb2cPhip << endl
		<< mb2dValidp << " " << mb2dQp << " " << mb2dPhip << endl << endl



      	<< "#### OUTPUTS ####" << endl

      	<< phiHp << " " << etaPTHp << endl
      	<< phiMp << " " << etaPTMp << endl
      	<< phiLp << " " << etaPTLp << endl << endl

      	<<(me1idH & 3) << " " << (me2idH & 3) << " " <<  (me3idH & 3) << " " <<  (me4idH & 3) << " " <<  (mb1idH & 3) << " " <<  (mb2idH &3) << endl
      	<<(me1idM & 3) << " " << (me2idM & 3) << " " <<  (me3idM & 3) << " " <<  (me4idM & 3) << " " <<  (mb1idM & 3) << " " <<  (mb2idM &3) << endl
      	<<(me1idL & 3) << " " << (me2idL & 3) << " " <<  (me3idL & 3) << " " <<  (me4idL & 3) << " " <<  (mb1idL & 3) << " " <<  (mb2idL &3) << endl << endl


      	<< "#### BXA ####"<< endl <<

      	spvpp.me1[0] << " " <<
      	spvpp.me1[1] << " " <<
      	spvpp.me1[2] << " " <<
      	spvpp.me1[3] << " " <<
      	spvpp.me1[4] << " " <<
      	spvpp.me1[5] << " " << endl <<
      	spvpp.me2[0] << " " <<
      	spvpp.me2[1] << " " <<
      	spvpp.me2[2] << " " << endl <<
      	spvpp.me3[0] << " " <<
      	spvpp.me3[1] << " " <<
      	spvpp.me3[2] << " " << endl <<
      	spvpp.me4[0] << " " <<
      	spvpp.me4[1] << " " <<
      	spvpp.me4[2] << " " << endl <<
      	spvpp.mb1[0] << " " <<
      	spvpp.mb1[1] << " " <<
      	spvpp.mb1[2] << " " <<
      	spvpp.mb1[3] << " " << endl <<
      	pHp << " " << pMp << " " << pLp << endl << 
      	endl;
}

#endif

#ifdef BXADEBUG
 cout << "bxa" << endl << 
	 mb1ap << " " <<
	 spvpp.dmb1[0] << " " <<
	 spvpp.mb1[0] << " " << endl;
#endif
}

