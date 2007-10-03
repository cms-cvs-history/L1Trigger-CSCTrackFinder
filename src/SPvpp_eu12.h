#ifndef _EU12_H_FILE_
#define _EU12_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_HighPt12 : public function
{

public:
	Signal operator()(Signal eta);

};

class SPvpp_MedPt12 : public function
{

public:
	Signal operator()(Signal eta);

};

class SPvpp_LowPt12 : public function
{

public:
	Signal operator()(Signal eta);

};


class SPvpp_eu12: public module
{

public:
	void operator()
	(
		Signal meA,
		Signal meB,
		Signal eq,
		Signal passX,
		Signal passY, Signal meY,
		Signal passZ, Signal meZ,
		Signal control
	);

	Signal qA, qB, etaA, etaB, eta, phiA, phiB, validA, validB;

	Signal CSCidA, CSCidB, CSCidY, CSCidZ;

	Signal Dphi;

	SPvpp_HighPt12 HighP12;
	SPvpp_MedPt12  MedP12;
	SPvpp_LowPt12  LowP12;
};

#endif
