#ifndef _MUONMUX_H_FILE_
#define _MUONMUX_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_ScalePhi:public function
{
public:
	Signal operator()(Signal phi);
	char h7[10];
	char * itoh7(int i);

};

class SPvpp_MuonMux: public module
{

public:
	void operator()
	(
		Signal m0, Signal m1, Signal m2,
		Signal pt0, Signal sign0, Signal modeMem0, Signal etaPT0, Signal FR0, Signal phi0,
		Signal pt1, Signal sign1, Signal modeMem1, Signal etaPT1, Signal FR1, Signal phi1,
		Signal pt2, Signal sign2, Signal modeMem2, Signal etaPT2, Signal FR2, Signal phi2,
		Signal pt3, Signal sign3, Signal modeMem3, Signal etaPT3, Signal FR3, Signal phi3,
		Signal pt4, Signal sign4, Signal modeMem4, Signal etaPT4, Signal FR4, Signal phi4,
		Signal pt5, Signal sign5, Signal modeMem5, Signal etaPT5, Signal FR5, Signal phi5,
		Signal pt6, Signal sign6, Signal modeMem6, Signal etaPT6, Signal FR6, Signal phi6,
		Signal pt7, Signal sign7, Signal modeMem7, Signal etaPT7, Signal FR7, Signal phi7,
		Signal pt8, Signal sign8, Signal modeMem8, Signal etaPT8, Signal FR8, Signal phi8,

		Signal id0, Signal id1, Signal id2, Signal id3, Signal id4, Signal id5,
		Signal id6, Signal id7, Signal id8,

		Signal ptH, Signal signH, Signal modeMemH, Signal etaPTH, Signal FRH, Signal phiH,
		Signal ptM, Signal signM, Signal modeMemM, Signal etaPTM, Signal FRM, Signal phiM,
		Signal ptL, Signal signL, Signal modeMemL, Signal etaPTL, Signal FRL, Signal phiL,
		Signal idH, Signal idM, Signal idL
	);

	SPvpp_ScalePhi ScalePhi;
	memory pt;
	Signal sign;
	memory modeMem;
	memory etaPT;
	Signal FR;
	memory phi;
	Signal i;
	memory id;
	Signal phiHs, phiMs, phiLs;


};

#endif
