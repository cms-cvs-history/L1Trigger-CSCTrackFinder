#ifndef _PTMB_H_FILE_
#define _PTMB_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_SelectPhisb : public function
{

public:
	Signal EnableIdA;
	Signal EnableIdB;
	Signal EnableIdC;
	Signal operator()(Signal IdValid);
};
/*
class SPvpp_SelectEtab : public function
{

public:
	Signal operator()(Signal IdValid);

};
  */
class SPvpp_Modeb : public function
{

public:
	Signal operator()(Signal rank);

};

class SPvpp_ptmb: public module
{

public:
	void operator()
	(
	// all etas use only 4 MSBs from the original Eta
		Signal me1a, Signal me1b, Signal me1c, Signal me1d, Signal me1e, Signal me1f,
		Signal me2a, Signal me2b, Signal me2c,
		Signal mb1a, Signal mb1b, Signal mb1c, Signal mb1d,
		Signal mb2a, Signal mb2b, Signal mb2c, Signal mb2d,

		Signal rank,
		Signal id1, Signal id2, Signal idb1, Signal idb2,

		Signal pt,
		Signal sign,
		Signal modeMem,
		Signal etaPT,
		Signal FR,
		Signal phi
	);


	Signal mode;
	Signal a, b;
	Signal si;
	Signal d;
//	Signal SelEta;
	Signal SelPhi;
	Signal IdValid;

	memory me1Eta, me2Eta, me1Phi, me2Phi, mb1Phi, mb2Phi;

	Signal phiA, phiB, phiC;

	SPvpp_SelectPhisb SelectPhisbp;
//	SPvpp_SelectEtab SelectEtabp;
	SPvpp_Modeb Modebp;
};


#endif
