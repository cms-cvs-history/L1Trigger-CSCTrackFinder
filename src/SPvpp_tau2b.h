#ifndef _TAU2B_H_FILE_
#define _TAU2B_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>

class SPvpp_Maxb21 : public function
{

public:
	Signal operator()(Signal mb21a, Signal mb21b, Signal mb21c, Signal mb21d);

};

class SPvpp_Max21b : public function
{

public:
	Signal operator()(Signal me21);

};

class SPvpp_Maxb22 : public function
{

public:
	Signal operator()(Signal mb);

};

class SPvpp_tau2b: public module
{

public:
	void operator()
	(
		Signal mb21,
		Signal mb22,
		Signal me21,
		Signal idl, Signal idm, Signal idh,
		Signal rank,
		Signal bxa_enable,
		Signal clk
	);

	Signal maxb21, max21, maxb22, quality;

	Signal b22, e21;
	memory b21;

	SPvpp_Maxb21 Maxb21p;
	SPvpp_Max21b Max21bp;
	SPvpp_Maxb22 Maxb22p;
};

#endif
