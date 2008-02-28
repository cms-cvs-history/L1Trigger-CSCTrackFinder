#ifndef CSCTrackFinder_CSCTFEfficiencies_h
#define CSCTrackFinder_CSCTFEfficiencies_h

/**
 * \author L. Gray 6/17/06
 *
 */

#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include <iostream>
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

//ROOT
#include <TH1F.h>
#include <TH1I.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TCanvas.h>

class CSCTFEfficiencies : public edm::EDAnalyzer {
 public:
  explicit CSCTFEfficiencies(edm::ParameterSet const& conf);
  virtual ~CSCTFEfficiencies() {}
  virtual void analyze(edm::Event const& e, edm::EventSetup const& iSetup);
  virtual void endJob();
  virtual void beginJob(edm::EventSetup const&);
  int ghosts;
  int lostTracks;
  int DebugCounter;
  unsigned haloTrigger;
 private:
  // variables persistent across events should be declared here.
  //
  std::string outFile;//c
  TFile* fAnalysis;//c

  void DeleteHistos();
  Int_t cnttrk, cntGen;

  TH1F* simEta, *simPhi, *simPt, *fidPtDen;
  TH1F* trackedEta, *trackedPhi, *trackedPt, *trackedBx;
  TH1F* matchedPhi, *matchedEta, *matchedPt, *Radius;
  TH1F* EffEtaAll, *EffEtaQ3, *EffEtaQ2, *EffEtaQ1, *EffPhi, *EffPt;
  TH1F* EtaQ3, *EtaQ2, *EtaQ1;
  TH1F* LostPhi, *LostEta;
  TH1F* ghostPhi, *ghostEta, *ghostPt, *ghostRadius;
  TH1F* etaResolution, *phiResolution, *ptResolution;
  TH1F* matchedPt10, *matchedPt20, *matchedPt40, *matchedPt60;
  TH1F* EffPt10, *EffPt20, *EffPt40, *EffPt60;
  TH1F* numEScat, *ghostDelPhi, *ghostDelEta, *ghostTrackRad, *ghostselectPtRes, *ghostdropPtRes ;
  //TH2F* PhiResVPt;
  
};

DEFINE_FWK_MODULE(CSCTFEfficiencies);

#endif