#ifndef CSCTrackFinder_CSCTFEfficiencies_h
#define CSCTrackFinder_CSCTFEfficiencies_h

/** 
 * \author L. Gray 6/17/06 
 *   
 */

#include "PluginManager/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include <iostream>
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Handle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

//ROOT
#include <TH1F.h>
#include <TH1I.h>

class CSCTFEfficiencies : public edm::EDAnalyzer {
 public:
  explicit CSCTFEfficiencies(edm::ParameterSet const& conf);
  virtual ~CSCTFEfficiencies();
  virtual void analyze(edm::Event const& e, edm::EventSetup const& iSetup);
  virtual void endJob();
  virtual void beginJob(edm::EventSetup const&);
 private:
  // variables persistent across events should be declared here.
  //
  Int_t cnttrk, cntGen;

  TH1F* hPtGen, *hPtCSC;

  TH1F* hAllPt, *hPt0, *hPt0q1, *hPt0q2, *hPt10, *hPt20, *hPt40, *hPt60;
  TH1F* hEffPt0, *hEffPt0q1, *hEffPt0q2, *hEffPt10, *hEffPt20, *hEffPt40, *hEffPt60;

  TH1F* hAllEta, *hEtaLoose, *hEtaTight, *hEtaQ1, *hEtaQ2, *hEtaQ3, *hEtaTot;
  TH1F* hEffEtaLoose, *hEffEtaTight, *hEffEtaQ1, *hEffEtaQ2, *hEffEtaQ3, *hEffEtaTot;
};

DEFINE_FWK_MODULE(CSCTFEfficiencies)

#endif
