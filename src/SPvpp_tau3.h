#ifndef _TAU3_H_FILE_
#define _TAU3_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>

class SPvpp_Max31 : public function
{

public:
	Signal operator()
	(
		Signal me31a,
		Signal me31b,
		Signal me31c,
		Signal me31d,
		Signal me31e,
		Signal me31f
	);

};

class SPvpp_Max3 : public function
{

public:
	Signal operator()(Signal me);

};

class SPvpp_tau3: public module
{

public:
	void operator()
	(
		Signal me31,
		Signal me32,
		Signal me34,
		Signal idl, Signal idm, Signal idh,
		Signal rank
	);

	Signal max31, max32, max34, quality;
	memory e31;
	Signal e32, e34;

	SPvpp_Max31 Max31p;
	SPvpp_Max3 Max3p;
};

#endif
