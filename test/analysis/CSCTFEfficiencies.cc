#include <L1Trigger/CSCTrackFinder/test/analysis/CSCTFEfficiencies.h>

CSCTFEfficiencies::CSCTFEfficiencies(edm::ParameterSet const& conf)
{
}

CSCTFEfficiencies::~CSCTFEfficiencies()
{
  if(hPtGen) delete hPtGen;
  if(hPtCSC) delete hPtCSC;
  if(hAllPt) delete hAllPt;
  if(hPt0) delete hPt0;
  if(hPt0q1) delete hPt0q1;
  if(hPt0q2) delete hPt0q2;
  if(hPt10) delete hPt10;
  if(hPt20) delete hPt20;
  if(hPt40) delete hPt40;
  if(hPt60) delete hPt60;
  if(hEffPt0) delete hEffPt0;
  if(hEffPt0q1) delete hEffPt0q1;
  if(hEffPt0q2) delete hEffPt0q2;
  if(hEffPt10) delete hEffPt10;
  if(hEffPt20) delete hEffPt20;
  if(hEffPt40) delete hEffPt40;
  if(hEffPt60) delete hEffPt60;
  if(hAllEta) delete hAllEta;
  if(hEtaLoose) delete hEtaLoose;
  if(hEtaTight) delete hEtaTight;
  if(hEtaQ1) delete hEtaQ1;
  if(hEtaQ2) delete hEtaQ2;
  if(hEtaQ3) delete hEtaQ3;
  if(hEtaTot) delete hEtaTot;
  if(hEffEtaLoose) delete hEffEtaLoose;
  if(hEffEtaTight) delete hEffEtaTight;
  if(hEffEtaQ1) delete hEffEtaQ1;
  if(hEffEtaQ2) delete hEffEtaQ2;
  if(hEffEtaQ3) delete hEffEtaQ3;
  if(hEffEtaTot) delete hEffEtaTot;
}

void CSCTFEfficiencies::beginJob(edm::EventSetup const& es)
{
  /* Effic Plots */
  /* Effic v Pt */
  hAllPt = new TH1F("hAllPt","Pt",138,2,140);

  hPt0  = new TH1F("hPt0","Pt50",138,2,140);
  hPt0q1  = new TH1F("hPt0q1","Pt50",138,2,140);
  hPt0q2  = new TH1F("hPt0q2","Pt50",138,2,140);
  hPt10 = new TH1F("hPt10","Pt50",138,2,140);
  hPt20 = new TH1F("hPt20","Pt50",138,2,140);
  hPt40 = new TH1F("hPt40","Pt50",138,2,140);
  hPt60 = new TH1F("hPt60","Pt50",138,2,140);

  hEffPt0 = new TH1F("hEffPt0","Efficiency vs. Pt50",138,2,140);
  hEffPt0q1 = new TH1F("hEffPt0q1","Efficiency vs. Pt50",138,2,140);
  hEffPt0q2 = new TH1F("hEffPt0q2","Efficiency vs. Pt50",138,2,140);
  hEffPt10 = new TH1F("hEffPt10","Efficiency vs. Pt50",138,2,140);
  hEffPt20 = new TH1F("hEffPt20","Efficiency vs. Pt50",138,2,140);
  hEffPt40 = new TH1F("hEffPt40","Efficiency vs. Pt50",138,2,140);
  hEffPt60 = new TH1F("hEffPt60","Efficiency vs. Pt50",138,2,140);
  /* Effic v Pt */

  /* Effic v Eta */
  hAllEta = new TH1F("hAllEta","Eta",360,0,2.5);

  hEtaLoose = new TH1F("hEtaLoose","Eta",360,0,2.5);
  hEtaTight = new TH1F("hEtaTight","Eta",360,0,2.5);
  hEtaQ1 = new TH1F("hEtaQ1","Eta, Quality > 0",360,0,2.5);
  hEtaQ2 = new TH1F("hEtaQ2","Eta, Quality > 1",360,0,2.5);
  hEtaQ3 = new TH1F("hEtaQ3","Eta, Quality > 2",360,0,2.5);
  hEtaTot = new TH1F("hEtaTot","Eta all Qualities",360,0,2.5);

  hEffEtaLoose = new TH1F("hEffEtaLoose","Efficiency vs. Eta",360,0,2.5);
  hEffEtaTight = new TH1F("hEffEtaTight","Efficiency vs. Eta",360,0,2.5);
  hEffEtaQ1 = new TH1F("hEffEtaQ1","Efficiency v. Eta Quality == 1",360,0,2.5);
  hEffEtaQ2 = new TH1F("hEffEtaQ2","Efficiency v. Eta Quality == 2",360,0,2.5);
  hEffEtaQ3 = new TH1F("hEffEtaQ3","Efficiency v. Eta Quality == 3",360,0,2.5);
  hEffEtaTot = new TH1F("hEffEtaTot","Efficiency v. Eta Total",360,0,2.5);
  /* Effic v Eta */
  /* Effic Plots */
}

void CSCTFEfficiencies::endJob()
{
  // put code here to write out .ps file
}

void CSCTFEfficiencies::analyze(edm::Event const& e, edm::EventSetup const& es)
{
  // get MC truth and track data here... then run analysis functions
}
