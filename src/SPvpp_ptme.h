#ifndef _PTME_H_FILE_
#define _PTME_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_SelectPhis : public function
{

public:
	Signal EnableIdA;
	Signal EnableIdB;
	Signal EnableIdC;

	Signal operator()(Signal IdValid);
};
/*
class SPvpp_SelectEta : public function
{

public:
	Signal operator()(Signal IdValid);

};
  */
class SPvpp_Mode : public function
{

public:
	Signal operator()(Signal rank);

};

class SPvpp_DecodeFR : public function
{

public:
	Signal operator()(Signal CSCid, Signal stubn);
};


class SPvpp_ptme: public module
{

public:
	void operator()
	(
	// all etas use only 4 MSBs from the original Eta
		Signal me1a, Signal me1b, Signal me1c, Signal me1d, Signal me1e, Signal me1f,
		Signal me2a, Signal me2b, Signal me2c,
		Signal me3a, Signal me3b, Signal me3c,
		Signal me4a, Signal me4b, Signal me4c,

		Signal rank,
		Signal id1, Signal id2, Signal id3, Signal id4,

		Signal pt,
		Signal sign,
		Signal modeMem,
		Signal etaPT,
		Signal FR,
		Signal phi
	);

	Signal mode;
	Signal a, b;
	Signal modeout, modenew;
	Signal si;
	Signal d, c;
//	Signal SelEta;
	Signal SelPhi;
	Signal IdValid;
	Signal me1FR;

	memory me1Eta, me2Eta, me3Eta, me1Phi, me2Phi, me3Phi, me4Phi, CSCID;

	Signal phiA, phiB, phiC;

	SPvpp_SelectPhis SelectPhisp;
//	SPvpp_SelectEta SelectEtap;
	SPvpp_Mode Modep;
	SPvpp_DecodeFR DecodeFR;

};

#endif
