#include "PluginManager/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "L1Trigger/CSCTrackFinder/src/CSCTFTrackProducer.h"
#include "L1Trigger/CSCTrackFinder/src/CSCTFCandidateProducer.h"

DEFINE_FWK_MODULE(CSCTFTrackProducer)
  DEFINE_ANOTHER_FWK_MODULE(CSCTFCandidateProducer)
