#include "PluginManager/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "L1Trigger/CSCTrackFinder/interface/CSCMakeSRLUT.h"
#include "L1Trigger/CSCTrackFinder/interface/CSCCompareSRLUTs.h"

DEFINE_FWK_MODULE(CSCMakeSRLUT)
DEFINE_ANOTHER_FWK_MODULE(CSCCompareSRLUTs)
