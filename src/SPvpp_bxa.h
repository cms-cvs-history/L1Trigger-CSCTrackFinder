
#ifndef _BXA_H_FILE_
#define _BXA_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>
#include <L1Trigger/CSCTrackFinder/src/SPvpp_bxame.h>

class SPvpp_bxa : public module
{
public:
	void operator ()
	(
		Signal me1a,  Signal me1b,  Signal me1c,  Signal me1d,  Signal me1e,  Signal me1f,
		Signal me2a,  Signal me2b,  Signal me2c,
		Signal me3a,  Signal me3b,  Signal me3c,
		Signal me4a,  Signal me4b,  Signal me4c,
		Signal mb1a,  Signal mb1b,  Signal mb1c,  Signal mb1d,
		Signal mb2a,  Signal mb2b,  Signal mb2c,  Signal mb2d,

		Signal me1ar, Signal me1br, Signal me1cr, Signal me1dr, Signal me1er, Signal me1fr,
		Signal me2ar, Signal me2br, Signal me2cr,
		Signal me3ar, Signal me3br, Signal me3cr,
		Signal me4ar, Signal me4br, Signal me4cr,
		Signal mb1ar, Signal mb1br, Signal mb1cr, Signal mb1dr,
		Signal mb2ar, Signal mb2br, Signal mb2cr, Signal mb2dr,

		Signal me1abi, Signal me1bbi, Signal me1cbi, Signal me1dbi, Signal me1ebi, Signal me1fbi,
		Signal me2abi, Signal me2bbi, Signal me2cbi,
		Signal me3abi, Signal me3bbi, Signal me3cbi,
		Signal me4abi, Signal me4bbi, Signal me4cbi,
		Signal mb1abi, Signal mb1bbi, Signal mb1cbi, Signal mb1dbi,
		Signal mb2abi, Signal mb2bbi, Signal mb2cbi, Signal mb2dbi,

		Signal depth,

		Signal clkp

	);


	SPvpp_bxame bxame1ac, bxame1df, bxame2, bxame3, bxame4, bxamb1, bxamb2;
	Signal med[5], medb[5];

};

#endif
