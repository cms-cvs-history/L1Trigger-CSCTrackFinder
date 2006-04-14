#ifndef _ETAU12_H_FILE_
#define _ETAU12_H_FILE_

#include <L1Trigger/CSCCommonTrigger/interface/vlib.h>
#include <L1Trigger/CSCTrackFinder/src/spbits.h>

class SPvpp_etau12 : public module
{
public:
	void operator()
	(
		Signal meA,
		Signal meB,
		Signal pass,
		Signal MinEta,
		Signal MaxEta,
		Signal EtaWindow
	);

	Signal qA, qB, etaA, etaB, amA, amB, Deta;

};
#endif
