#ifndef _BXAME_H_FILE_
#define _BXAME_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_bxame : public module
{
public:
	void operator()
	(
		Signal inAp, Signal inBp, Signal inCp,
		Signal outA, Signal outB, Signal outC,
		Signal validin,
		Signal validout,
		Signal etaoff,
		Signal clk
	);

	Signal inA, inB, inC, inAr, inBr, inCr, validABC;
	Signal etaA, etaB, etaC;

};

#endif
