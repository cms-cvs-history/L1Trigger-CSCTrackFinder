#ifndef _FSU_H_FILE_
#define _FSU_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_CountZeroes : public function
{

public:
	Signal operator()(Signal d);
	Signal s, res;
	int mb;

	SPvpp_CountZeroes()
	{
		mb = 0; // 8-bit by default
	}

};

class SPvpp_fsu: public module
{

public:
	void operator()
	(
		Signal me2aRank, Signal phi2a,
		Signal me2bRank, Signal phi2b,
		Signal me2cRank, Signal phi2c,

		Signal me3aRank, Signal phi3a,
		Signal me3bRank, Signal phi3b,
		Signal me3cRank, Signal phi3c,
	
		Signal mb2aRank, Signal phib2a,
		Signal mb2bRank, Signal phib2b,
		Signal mb2cRank, Signal phib2c,

		Signal m0, Signal m1, Signal m2,

		Signal phi_watch_en,
		Signal mindphi,

		Signal clk
	);

		memory rank, phi;
		Signal Exists, survived;
		memory Larger, Large;
		Signal ilgj, larg, larg1;

		Signal i, j, k;
		Signal s;
		memory rankr, phir;
		memory rankrr, phirr;
		Signal dphi, dphir, dphirr;
		memory phi_match, phir_match;

		Signal kill, killr, killrr1, killrr2, killrr3, dlm, rilgrj;

		SPvpp_CountZeroes CountZ;


};

#endif

