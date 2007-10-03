#ifndef _EU232434_H_FILE_
#define _EU232434_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_eu23_24_34: public module
{

public:
	void operator()
	(
		Signal meA,
		Signal meB,
		Signal eq,
		Signal MinEta,
		Signal MaxEta,
		Signal EtaWindow,
		Signal control
	);

	Signal qA, qB, etaA, etaB, phiA, phiB, amA, amB;
	Signal Deta, Dphi;
	Signal CSCidA,	CSCidB,	validA,	validB;

};

#endif
