#ifndef _FSU_H_FILE_
#define _FSU_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>

class SPvpp_CountZeroes : public function
{

public:
	Signal operator()(Signal d);

};

class SPvpp_fsu: public module
{

public:
	void operator()
	(
		Signal me2aRank, Signal me2aId1, Signal me2aId3, Signal me2aId4,
		Signal me2bRank, Signal me2bId1, Signal me2bId3, Signal me2bId4,
		Signal me2cRank, Signal me2cId1, Signal me2cId3, Signal me2cId4,

		Signal me3aRank, Signal me3aId1, Signal me3aId2, Signal me3aId4,
		Signal me3bRank, Signal me3bId1, Signal me3bId2, Signal me3bId4,
		Signal me3cRank, Signal me3cId1, Signal me3cId2, Signal me3cId4,

		Signal mb2aRank, Signal mb2aId1, Signal mb2aIdb1, Signal mb2aIdb2,
		Signal mb2bRank, Signal mb2bId1, Signal mb2bIdb1, Signal mb2bIdb2,
		Signal mb2cRank, Signal mb2cId1, Signal mb2cIdb1, Signal mb2cIdb2,

		Signal m0, Signal m1, Signal m2
	);

		memory rank, Id1, Id2, Id3, Id4;
		Signal CommonStub, Exists;
		memory Larger;
		Signal ilgj, larg, larg1;

		Signal i, j, k;
		Signal s;

		SPvpp_CountZeroes CountZ;

		Signal Id1i, Id2i, Id3i, Id4i, Id1j, Id2j, Id3j, Id4j;

};

#endif

