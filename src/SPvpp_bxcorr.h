#ifndef _BXCORR_H_FILE_
#define _BXCORR_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_fsu.h>

class SPvpp_bxcorr : public module
{
 public:
	void operator()
	(
		Signal rank1, Signal rank2, Signal rank3,
		Signal b1, Signal b2, Signal b3,
		Signal id1, Signal id2, Signal id3,
		Signal bc1, Signal bc2, Signal bc3,
		Signal idc1, Signal idc2, Signal idc3,
		Signal pretrig,
		Signal clk
	);

	SPvpp_CountZeroes CountZ;

	memory in;
	memory id;
	memory r;

	Signal Exists;

	Signal m0;
	Signal m1;
	Signal m2;

	Signal i;
	Signal j;

	Signal ilgj;
	memory Larger;
	Signal larg1;

	Signal s;
	Signal stubn;
	Signal stubd;
	memory del2stubs;
	memory del1stubs;


};

#endif
