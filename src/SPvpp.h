#include <L1Trigger/CSCTrackFinder/src/SPvpp_sp.h>

#ifndef _FILE_SPvpp_FILE
#define _FILE_SPvpp_FILE

class SPvpp
{
public:


	void SP                                        
	(                                                                   
	unsigned me1aValidp, unsigned me1aQp, unsigned me1aEtap, unsigned me1aPhip,	/*unsigned me1aAmp,*/ unsigned me1aCSCidp, 
	unsigned me1bValidp, unsigned me1bQp, unsigned me1bEtap, unsigned me1bPhip,	/*unsigned me1bAmp,*/ unsigned me1bCSCidp, 
	unsigned me1cValidp, unsigned me1cQp, unsigned me1cEtap, unsigned me1cPhip,	/*unsigned me1cAmp,*/ unsigned me1cCSCidp, 
	unsigned me1dValidp, unsigned me1dQp, unsigned me1dEtap, unsigned me1dPhip,	/*unsigned me1dAmp,*/ unsigned me1dCSCidp, 
	unsigned me1eValidp, unsigned me1eQp, unsigned me1eEtap, unsigned me1ePhip,	/*unsigned me1eAmp,*/ unsigned me1eCSCidp, 
	unsigned me1fValidp, unsigned me1fQp, unsigned me1fEtap, unsigned me1fPhip,	/*unsigned me1fAmp,*/ unsigned me1fCSCidp, 
					     				        		        			                
	unsigned me2aValidp, unsigned me2aQp, unsigned me2aEtap, unsigned me2aPhip,	/*unsigned me2aAmp,*/  
	unsigned me2bValidp, unsigned me2bQp, unsigned me2bEtap, unsigned me2bPhip,	/*unsigned me2bAmp,*/  
	unsigned me2cValidp, unsigned me2cQp, unsigned me2cEtap, unsigned me2cPhip,	/*unsigned me2cAmp,*/  
					     				        		        			                
	unsigned me3aValidp, unsigned me3aQp, unsigned me3aEtap, unsigned me3aPhip,	/*unsigned me3aAmp,*/  
	unsigned me3bValidp, unsigned me3bQp, unsigned me3bEtap, unsigned me3bPhip,	/*unsigned me3bAmp,*/  
	unsigned me3cValidp, unsigned me3cQp, unsigned me3cEtap, unsigned me3cPhip,	/*unsigned me3cAmp,*/  
					     				        		        			                
	unsigned me4aValidp, unsigned me4aQp, unsigned me4aEtap, unsigned me4aPhip,	/*unsigned me4aAmp,*/  
	unsigned me4bValidp, unsigned me4bQp, unsigned me4bEtap, unsigned me4bPhip,	/*unsigned me4bAmp,*/  
	unsigned me4cValidp, unsigned me4cQp, unsigned me4cEtap, unsigned me4cPhip,	/*unsigned me4cAmp,*/  
					     				                                                    
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

	unsigned mindphip,
	unsigned mindeta_accp, unsigned maxdeta_accp, unsigned maxdphi_accp,
	unsigned controlp

	);  

public:
	SPvpp_sp spvpp;

	Signal
		me1ap,
		me1bp,
		me1cp,
		me1dp,
		me1ep,
		me1fp,
		
		me2ap,
		me2bp,
		me2cp,
		
		me3ap,
		me3bp,
		me3cp,
		
		me4ap,
		me4bp,
		me4cp,
		
		
		mb1ap,
		mb1bp,
		mb1cp,
		mb1dp,
		
		mb2ap,
		mb2bp,
		mb2cp,
		mb2dp,
		
		me1ar, 
		me1br, 
		me1cr, 
		me1dr, 
		me1er, 
		me1fr, 
		
		me2ar, 
		me2br, 
		me2cr, 
		
		me3ar, 
		me3br, 
		me3cr, 
		
		me4ar, 
		me4br, 
		me4cr,
		
		pHp,
		pMp,
		pLp,

		mneta0,	mneta1,	mneta2,	mneta3,	mneta4,	mneta5,	mneta6,	mneta7,	 		
		mxeta0,	mxeta1,	mxeta2,	mxeta3,	mxeta4,	mxeta5,	mxeta6,	mxeta7,
		etawn0,	etawn1,	etawn2,	etawn3,	etawn4,	etawn5,

		date, control, mindphi,
		mindeta_acc, maxdeta_acc, maxdphi_acc,
		
		clkp;
	
	Signal idHp, idMp, idLp;

	unsigned
		mb1aQr, mb1aPhir, 
		mb1bQr, mb1bPhir;
		

};

#endif
