#ifndef _EU12OV_H_FILE_
#define _EU12OV_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_eu12_ov: public module
{

public:
	void operator()
	(
		Signal meA,
		Signal meB,
		Signal eq,
		Signal passX,
		Signal passY, Signal meY,
		Signal passZ, Signal meZ
	);

	Signal qA, qB, etaA, etaB, eta, phiA, phiB, validA, validB;

	Signal CSCidA, CSCidB, CSCidY, CSCidZ;

	Signal Dphi;


};

#endif
