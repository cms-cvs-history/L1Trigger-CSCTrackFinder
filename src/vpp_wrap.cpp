#include "vpp_generated.h"

void vpp_generated::wrap
(
	unsigned me1aValidp, unsigned me1aQp, unsigned me1aEtap, unsigned me1aPhip,	unsigned me1aCSCidp,
	unsigned me1bValidp, unsigned me1bQp, unsigned me1bEtap, unsigned me1bPhip,	unsigned me1bCSCidp,
	unsigned me1cValidp, unsigned me1cQp, unsigned me1cEtap, unsigned me1cPhip,	unsigned me1cCSCidp,
	unsigned me1dValidp, unsigned me1dQp, unsigned me1dEtap, unsigned me1dPhip,	unsigned me1dCSCidp,
	unsigned me1eValidp, unsigned me1eQp, unsigned me1eEtap, unsigned me1ePhip,	unsigned me1eCSCidp,
	unsigned me1fValidp, unsigned me1fQp, unsigned me1fEtap, unsigned me1fPhip,	unsigned me1fCSCidp,
			 					   				   				   	  			  
	unsigned me2aValidp, unsigned me2aQp, unsigned me2aEtap, unsigned me2aPhip,
	unsigned me2bValidp, unsigned me2bQp, unsigned me2bEtap, unsigned me2bPhip,
	unsigned me2cValidp, unsigned me2cQp, unsigned me2cEtap, unsigned me2cPhip,
			 					   				   				   	  			  
	unsigned me3aValidp, unsigned me3aQp, unsigned me3aEtap, unsigned me3aPhip,
	unsigned me3bValidp, unsigned me3bQp, unsigned me3bEtap, unsigned me3bPhip,
	unsigned me3cValidp, unsigned me3cQp, unsigned me3cEtap, unsigned me3cPhip,
			 					   				   				   	  			  
	unsigned me4aValidp, unsigned me4aQp, unsigned me4aEtap, unsigned me4aPhip,
	unsigned me4bValidp, unsigned me4bQp, unsigned me4bEtap, unsigned me4bPhip,
	unsigned me4cValidp, unsigned me4cQp, unsigned me4cEtap, unsigned me4cPhip,
			 					   									  									  
	unsigned mb1aValidp, unsigned mb1aQp,                    unsigned mb1aPhip,
	unsigned mb1bValidp, unsigned mb1bQp,                    unsigned mb1bPhip,
	unsigned mb1cValidp, unsigned mb1cQp,                    unsigned mb1cPhip,
	unsigned mb1dValidp, unsigned mb1dQp,                    unsigned mb1dPhip,

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
)
{

	// delayed CSC track stubs
	static ULLONG me1ar,me1br,me1cr,me1dr,me1er,me1fr;
	static ULLONG me2ar,me2br,me2cr,me3ar,me3br,me3cr;
	static ULLONG me4ar,me4br,me4cr;

	// delayed DT inputs for serialization
	static ULLONG mb1aPhir, mb1aQr;
	static ULLONG mb1bPhir, mb1bQr;

	// put delayed inputs into the core inputs (internal variables of vpp_generated)
	me1ap = me1ar;
	me1bp = me1br;
	me1cp = me1cr;
	me1dp = me1dr;
	me1ep = me1er;
	me1fp = me1fr;
		 		 
	me2ap = me2ar;
	me2bp = me2br;
	me2cp = me2cr;
		 		 
	me3ap = me3ar;
	me3bp = me3br;
	me3cp = me3cr;
		 		 
	me4ap = me4ar;
	me4bp = me4br;
	me4cp = me4cr;

	// pack CSC inputs into delayed inputs. This delay is necessary to compensate for deserialization of DT inputs in the core
	me1ar = ((me1aValidp&1)<<27) | ((me1aCSCidp&0xf)<<23) | ((me1aQp&0xf)<<19) | ((me1aEtap&0x7f)<<12) |  (me1aPhip&0xfff);
	me1br = ((me1bValidp&1)<<27) | ((me1bCSCidp&0xf)<<23) | ((me1bQp&0xf)<<19) | ((me1bEtap&0x7f)<<12) |  (me1bPhip&0xfff);
	me1cr = ((me1cValidp&1)<<27) | ((me1cCSCidp&0xf)<<23) | ((me1cQp&0xf)<<19) | ((me1cEtap&0x7f)<<12) |  (me1cPhip&0xfff);
	me1dr = ((me1dValidp&1)<<27) | ((me1dCSCidp&0xf)<<23) | ((me1dQp&0xf)<<19) | ((me1dEtap&0x7f)<<12) |  (me1dPhip&0xfff);
	me1er = ((me1eValidp&1)<<27) | ((me1eCSCidp&0xf)<<23) | ((me1eQp&0xf)<<19) | ((me1eEtap&0x7f)<<12) |  (me1ePhip&0xfff);
	me1fr = ((me1fValidp&1)<<27) | ((me1fCSCidp&0xf)<<23) | ((me1fQp&0xf)<<19) | ((me1fEtap&0x7f)<<12) |  (me1fPhip&0xfff);
			  				   	 		 			   		   				  	   				   		   			  				  						  	  	  	  
	me2ar = ((me2aValidp&1)<<27) |                          ((me2aQp&0xf)<<19) | ((me2aEtap&0x7f)<<12) |  (me2aPhip&0xfff);
	me2br = ((me2bValidp&1)<<27) |                          ((me2bQp&0xf)<<19) | ((me2bEtap&0x7f)<<12) |  (me2bPhip&0xfff);
	me2cr = ((me2cValidp&1)<<27) |                          ((me2cQp&0xf)<<19) | ((me2cEtap&0x7f)<<12) |  (me2cPhip&0xfff);
			  				   								   				 	   				   		   			  			 
	me3ar = ((me3aValidp&1)<<27) |                          ((me3aQp&0xf)<<19) | ((me3aEtap&0x7f)<<12) |  (me3aPhip&0xfff);
	me3br = ((me3bValidp&1)<<27) |                          ((me3bQp&0xf)<<19) | ((me3bEtap&0x7f)<<12) |  (me3bPhip&0xfff);
	me3cr = ((me3cValidp&1)<<27) |                          ((me3cQp&0xf)<<19) | ((me3cEtap&0x7f)<<12) |  (me3cPhip&0xfff);
			  				   	 		 				   	   				 	   				   		   			  				 						     	   
	me4ar = ((me4aValidp&1)<<27) |                          ((me4aQp&0xf)<<19) | ((me4aEtap&0x7f)<<12) |  (me4aPhip&0xfff);
	me4br = ((me4bValidp&1)<<27) |                          ((me4bQp&0xf)<<19) | ((me4bEtap&0x7f)<<12) |  (me4bPhip&0xfff);
	me4cr = ((me4cValidp&1)<<27) |                          ((me4cQp&0xf)<<19) | ((me4cEtap&0x7f)<<12) |  (me4cPhip&0xfff);
			  			
	// serialize 4 DT inputs into 2 inputs for the core
	if      (mb1aQp != 0) {mb1ap = ((mb1aQp&0x7)<<12) | (mb1aPhip&0xfff); 
#ifdef MYDEBUG
		if(mb1aQr != 0) cout<<"killing a\n";
#endif
	}
	else if (mb1aQr != 0) {mb1ap = (1 << 15) | ((mb1aQr&0x7)<<12) | (mb1aPhir&0xfff);}
	else mb1ap = 0;

	if      (mb1bQp != 0) {mb1cp = ((mb1bQp&0x7)<<12) | (mb1bPhip&0xfff); 
#ifdef MYDEBUG
		if(mb1bQr != 0) cout<<"killing b\n";
#endif
	}
	else if (mb1bQr != 0) {mb1cp = (1 << 15) | ((mb1bQp&0x7)<<12) | (mb1bPhip&0xfff);}
	else mb1cp = 0;

	mb1aPhir = mb1cPhip; mb1aQr = mb1cQp;
	mb1bPhir = mb1dPhip; mb1bQr = mb1dQp;

	// put all other inputs into core inputs
	mneta0 = mneta0p;
	mneta1 = mneta1p;
	mneta2 = mneta2p;
	mneta3 = mneta3p;
	mneta4 = mneta4p;
	mneta5 = mneta5p;
	mneta6 = mneta6p;
	mneta7 = mneta7p;

	mxeta0 = mxeta0p;
	mxeta1 = mxeta1p;
	mxeta2 = mxeta2p;
	mxeta3 = mxeta3p;
	mxeta4 = mxeta4p;
	mxeta5 = mxeta5p;
	mxeta6 = mxeta6p;
	mxeta7 = mxeta7p;
			 		   
	etawn0 = etawn0p;
	etawn1 = etawn1p;
	etawn2 = etawn2p;
	etawn3 = etawn3p;
	etawn4 = etawn4p;
	etawn5 = etawn5p;

	mindphi     = mindphip    ;
	mindeta_acc = mindeta_accp;
	maxdeta_acc = maxdeta_accp;
	maxdphi_acc = maxdphi_accp;
	control     = controlp    ;

	// drive clock up and down
	for (int i = 1; i >= 0; i--)
	{
		clkp = i;
		run();
	}
	
	// unpack track parameters
	int bp = 0;

	etaPTHp = pHp & 0x1f;
	etaPTMp = pMp & 0x1f;
	etaPTLp = pLp & 0x1f;

	bp += 5;

	modeMemHp = (pHp >> bp) & 0xf;
	modeMemMp = (pMp >> bp) & 0xf;
	modeMemLp = (pLp >> bp) & 0xf;

	bp += 4;

	signHp = (pHp >> bp) & 1;
	signMp = (pMp >> bp) & 1;
	signLp = (pLp >> bp) & 1;

	bp += 1;

	ptHp = (pHp >> bp) & 0x1fff;
	ptMp = (pMp >> bp) & 0x1fff;
	ptLp = (pLp >> bp) & 0x1fff;

	bp += 13;

	phiHp = (pHp >> bp) & 0x1f;
	phiMp = (pMp >> bp) & 0x1f;
	phiLp = (pLp >> bp) & 0x1f;

	bp += 5;

	FRHp = (pHp >> bp) & 1;
	FRMp = (pMp >> bp) & 1;
	FRLp = (pLp >> bp) & 1;

	//Retrieve ints from id codes
	bp = 0;

	me1idH = (idHp >> bp) & 0x3f;
	me1idM = (idMp >> bp) & 0x3f;
	me1idL = (idLp >> bp) & 0x3f;

	bp += 6;

	me2idH = (idHp >> bp) & 0x3f;	
	me2idM = (idMp >> bp) & 0x3f;
	me2idL = (idLp >> bp) & 0x3f;

	bp += 6;

	me3idH = (idHp >> bp) & 0x3f;	
	me3idM = (idMp >> bp) & 0x3f;
	me3idL = (idLp >> bp) & 0x3f;

	bp += 6;

	me4idH = (idHp >> bp) & 0x3f;	
	me4idM = (idMp >> bp) & 0x3f;
	me4idL = (idLp >> bp) & 0x3f;

	bp += 6;

	mb1idH = (idHp >> bp) & 0x3f;
	mb1idM = (idMp >> bp) & 0x3f;
	mb1idL = (idLp >> bp) & 0x3f;

	bp += 6;

	mb2idH = (idHp >> bp) & 0x3f;
	mb2idM = (idMp >> bp) & 0x3f;
	mb2idL = (idLp >> bp) & 0x3f;
}
