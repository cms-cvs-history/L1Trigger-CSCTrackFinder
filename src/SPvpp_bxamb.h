#ifndef _BXAMB_H_FILE_
#define _BXAMB_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_bxamb : public module
{
public:
	void operator()
	(
		Signal inAp, Signal inBp, Signal inCp, Signal inDp,
		Signal outA, Signal outB, Signal outC, Signal outD,
		Signal validin,
		Signal validout,
		Signal clk
	);

	Signal inA, inB, inC, inD, inAr, inBr, inCr, inDr, validABCD, vA, vB, vC, vD;

};
#endif
