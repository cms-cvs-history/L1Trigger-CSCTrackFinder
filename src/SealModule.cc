#include "PluginManager/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "L1Trigger/CSCTrackFinder/src/CSCMakeSRLUT.h"
#include "L1Trigger/CSCTrackFinder/src/CSCCompareSRLUTs.h"
#include "L1Trigger/CSCTrackFinder/src/CSCTFTrackProducer.h"
#include "L1Trigger/CSCTrackFinder/src/CSCTFCandidateProducer.h"
#include "L1Trigger/CSCTrackFinder/src/CSCTFLCTProducer.h"

DEFINE_FWK_MODULE(CSCMakeSRLUT)
  DEFINE_ANOTHER_FWK_MODULE(CSCCompareSRLUTs)
  DEFINE_ANOTHER_FWK_MODULE(CSCTFTrackProducer)
  DEFINE_ANOTHER_FWK_MODULE(CSCTFCandidateProducer)
  DEFINE_ANOTHER_FWK_MODULE(CSCTFLCTProducer)
