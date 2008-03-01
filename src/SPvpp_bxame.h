#ifndef _BXAME_H_FILE_
#define _BXAME_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_fsu.h>

class SPvpp_bxame : public module
{
public:
	void operator()
	(
		Signal inA,   Signal inB,   Signal inC,	  Signal inD,	  
		Signal outA,  Signal outB,  Signal outC,  Signal outD,  
		Signal bxidA, Signal bxidB, Signal bxidC, Signal bxidD, 
		Signal depth,
		Signal clk
	);

	Signal inArr, inBrr, inCrr, inDrr, inAr, inBr, inCr, inDr;
	Signal id[12];
	memory in, q, Larger;
	Signal Exists, m0, m1, m2, m3, i, j, ilgj, larg1, s, tin;

	SPvpp_CountZeroes CountZ;

	int idoff, mb;

};

#endif
