#ifndef _EU2B2_H_FILE_
#define _EU2B2_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_eu2b2: public module
{

public:
	void operator()
	(
		Signal meA,
		Signal mbB,
		Signal eq,
		Signal MinEta,
		Signal MaxEta
    );

	Signal qA, qB, /*amA,*/ eta, phiA, phiB;
	Signal Dphi;
	Signal CSCidA,	validA,	validB;

};

#endif
