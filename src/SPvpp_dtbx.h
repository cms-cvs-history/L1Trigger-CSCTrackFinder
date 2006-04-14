#ifndef _DTBX_H_FILE_
#define _DTBX_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_dtbx : public module
{
public:
	void operator()
	(
		Signal mb1a,

		Signal mb1ap,
		Signal mb1bp,

		Signal clk
	);

	Signal mb1ar;
};

#endif
