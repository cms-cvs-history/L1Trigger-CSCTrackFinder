#ifndef _EU13_H_FILE_
#define _EU13_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>


class SPvpp_HighPt13 : public function
{

public:
	Signal operator()(Signal eta);

};

class SPvpp_MedPt13 : public function
{

public:
	Signal operator()(Signal eta);

};

class SPvpp_LowPt13 : public function
{

public:
	Signal operator()(Signal eta);

};


class SPvpp_eu13: public module
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

	SPvpp_HighPt13 HighP13;
	SPvpp_MedPt13  MedP13;
	SPvpp_LowPt13  LowP13;
};

#endif
