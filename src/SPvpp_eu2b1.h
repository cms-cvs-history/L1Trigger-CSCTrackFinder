#ifndef _EU2B1_H_FILE_
#define _EU2B1_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>


class SPvpp_HighPt2b1 : public function
{

public:
	Signal operator()(Signal eta);

};

class SPvpp_MedPt2b1 : public function
{

public:
	Signal operator()(Signal eta);

};

class SPvpp_LowPt2b1 : public function
{

public:
	Signal operator()(Signal eta);

};


class SPvpp_eu2b1: public module
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

	SPvpp_HighPt2b1 HighP2b1;
	SPvpp_MedPt2b1  MedP2b1;
	SPvpp_LowPt2b1  LowP2b1;
};

#endif
