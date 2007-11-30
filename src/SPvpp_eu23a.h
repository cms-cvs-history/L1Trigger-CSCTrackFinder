#ifndef _EU23A_H_FILE_
#define _EU23A_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_eu23a: public module
{

public:
	void operator()
	(
		Signal meA,
		Signal meB,
		Signal eq,
		Signal MinDeta, 
		Signal MaxDeta, 
		Signal MaxDphi,
//	    Signal control,
		Signal clk
	);

	Signal qA, qB, etaA, etaB, phiA, phiB, amA, amB;
	Signal Deta, Dphi;
	Signal CSCidA,	CSCidB,	validA,	validB;
	Signal eqold, eqnew;

};

#endif
