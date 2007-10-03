#ifndef _TAU2_H_FILE_
#define _TAU2_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>

class SPvpp_Max21 : public function
{

public:
	Signal maxq;
	Signal operator()(Signal me21a, Signal me21b, Signal me21c, Signal me21d, Signal me21e, Signal me21f);

};

class SPvpp_Max : public function
{

public:
	Signal operator()(Signal me);

};

class SPvpp_tau2: public module
{

public:
	void operator()
	(
		Signal me21,
		Signal me23,
		Signal me24,
		Signal idl, Signal idm, Signal idh,
		Signal rank
	);

	Signal e23, e24;
	Signal max21, max23, max24, quality;
	memory e21;

	SPvpp_Max21 Max21p;
	SPvpp_Max Maxp;
};

#endif
