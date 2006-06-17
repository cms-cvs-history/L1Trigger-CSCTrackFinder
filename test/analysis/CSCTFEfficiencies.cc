#include <L1Trigger/CSCTrackFinder/test/analysis/CSCTFEfficiencies.h>

#include <SimDataFormats/Track/interface/EmbdSimTrackContainer.h>
#include <DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h>

#include <TMath.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TF1.h>

namespace csctf_analysis
{
  Double_t thresh(Double_t* pt, Double_t* par)
  {
    Double_t fitval = (0.5*TMath::Erf((pt[0]/par[0] + 1.0)/(TMath::Sqrt(2.0)*par[1])) +
		       0.5*TMath::Erf((pt[0]/par[0] - 1.0)/(TMath::Sqrt(2.0)*par[1])) )
                      *(par[2] + par[3]*pt[0]);
    return fitval;
  }
}

CSCTFEfficiencies::CSCTFEfficiencies(edm::ParameterSet const& conf)
{
  cnttrk = 0;
  cntGen = 0;
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
  //fill efficiency plots.
  // Efficiency vs. Pt
  hEffPt0->Divide(hPt0, hAllPt);
  hEffPt0q1->Divide(hPt0q1, hAllPt);
  hEffPt0q2->Divide(hPt0q2, hAllPt);
  hEffPt10->Divide(hPt10, hAllPt);
  hEffPt20->Divide(hPt20, hAllPt);
  hEffPt40->Divide(hPt40, hAllPt);
  hEffPt60->Divide(hPt60, hAllPt);

  // Efficiency vs. Eta
  hEffEtaLoose->Divide(hEtaLoose, hAllEta);
  hEffEtaTight->Divide(hEtaTight, hAllEta);
  hEffEtaQ1->Divide(hEtaQ1, hAllEta);
  hEffEtaQ2->Divide(hEtaQ2, hAllEta);
  hEffEtaQ3->Divide(hEtaQ3, hAllEta);
  hEffEtaTot->Divide(hEtaTot, hAllEta);

  // draw graphs and write out to .ps file
  TCanvas* c1 = new TCanvas("c1");

  TF1* fitThresh = new TF1("fitThresh", csctf_analysis::thresh, 0, 100, 4);
  fitThresh->SetParNames("Pt50","Resol","Constant","Slope");

  fitThresh->SetLineColor(1);
  hEffPt0->Fit("fitThresh");

  fitThresh->SetLineColor(4);
  hEffPt10->Fit("fitThresh");

  fitThresh->SetLineColor(3);
  hEffPt20->Fit("fitThresh");

  fitThresh->SetLineColor(6);
  hEffPt40->Fit("fitThresh");

  fitThresh->SetLineColor(2);
  hEffPt60->Fit("fitThresh");

  hEffPt0->GetXaxis()->SetTitle("Pt (Gev/c)");
  hEffPt0->GetYaxis()->SetTitle("Efficiency");
  hEffPt0->SetMaximum(1.0);
  
  hEffPt0->SetMarkerColor(1);
  hEffPt0->SetMarkerStyle(24);
  hEffPt0->Draw("P");

  hEffPt10->SetMarkerColor(4);
  hEffPt10->SetMarkerStyle(20);
  hEffPt10->Draw("same P");

  hEffPt20->SetMarkerColor(3);
  hEffPt20->SetMarkerStyle(22);
  hEffPt20->Draw("same P");
  
  hEffPt40->SetMarkerColor(6);
  hEffPt40->SetMarkerStyle(21);
  hEffPt40->Draw("same P");

  hEffPt60->SetMarkerColor(2);
  hEffPt60->SetMarkerStyle(23);
  hEffPt60->Draw("same P");

  c1->Print("CSCTFEfficiencies.ps(");

  hEffEtaQ1->SetTitle("Efficiency vs. Eta");
  hEffEtaQ1->GetXaxis()->SetTitle("|Eta|");
  hEffEtaQ1->GetYaxis()->SetTitle("Efficiency");
  hEffEtaQ1->SetMaximum(1.0);

  hEffEtaQ1->SetFillColor(1);
  hEffEtaQ2->SetFillColor(4);
  hEffEtaQ3->SetFillColor(3);

  hEffEtaQ1->Draw();
  hEffEtaQ2->Draw("same");
  hEffEtaQ3->Draw("same");

  c1->Print("CSCTFEfficiencies.ps");

  hEffEtaLoose->Draw();

  c1->Print("CSCTFEfficiencies.ps");

  hEffEtaTight->Draw();

  c1->Print("CSCTFEfficiencies.ps)");

  std::cout << "Tracks: " << cnttrk << std::endl;
  std::cout << "Gen   : " << cntGen << std::endl;

  delete c1;
  delete fitThresh;

}

void CSCTFEfficiencies::analyze(edm::Event const& e, edm::EventSetup const& es)
{
  // initialize various counters
  Int_t netaq1 = 0, netaq2 = 0, netaq3 = 0, netatot = 0;
  Int_t nLoose = 0, nTight = 0;
  Int_t nPt0 = 0, nPt0q1 = 0, nPt0q2 = 0;
  Int_t nPt10 = 0, nPt20 = 0, nPt40 = 0, nPt60 = 0;
  
  // get MC truth and track data here... then run analysis functions
  edm::Handle<edm::EmbdSimTrackContainer> simTracks;
  edm::Handle<std::vector<L1MuRegionalCand> > tfTracks;

  e.getByLabel("csctfmuonsorter","CSC", tfTracks);
  e.getByLabel("SimG4Object",simTracks);

  edm::EmbdSimTrackContainer::const_iterator simTrk = simTracks->begin();
  std::vector<L1MuRegionalCand>::const_iterator tfTrk;


  for(; simTrk != simTracks->end(); simTrk++)
    {
      HepLorentzVector mom = simTrk->momentum();

      if( simTrk->type() != 0 && mom.t() > 0.2 )
	if(mom.perp() > 2 && simTracks->size() < 300) // make necessary cuts
	  if(fabs(simTrk->type()) == 13)
	    {
	      ++cntGen;

	      double genPhi = (mom.phi() > 0) ? mom.phi() : mom.phi() + 2*M_PI;
	      double genEta = mom.pseudoRapidity();
	      
	      std::cout << "Sim Muon: Pt " << mom.perp() << " GeV, Eta " << genEta
			<< " , Phi " << genPhi << std::endl;
	      	      
	      if( fabs(genEta)>= 1.2 && fabs(genEta) < 2.1 )
		hAllPt->Fill( mom.perp() );

	      if( mom.perp() >= 10 ) hAllEta->Fill( fabs(genEta) );

	      tfTrk = tfTracks->begin();
	      for(; tfTrk != tfTracks->end(); tfTrk++)
		{
		  std::cout << "TF Muon: Pt " << tfTrk->ptValue() << " GeV, Eta " << tfTrk->etaValue() 
			    << " Phi " << tfTrk->phiValue() << std::endl;
		  // quick and dirty track matching..
		  if(sqrt(pow((tfTrk->etaValue() - genEta),2.) + 
			  pow((tfTrk->phiValue() - genPhi),2.)) < .3357)
		    {
		      ++cnttrk;
		      /* Efficiency vs. Eta */
		      if(tfTrk->quality() > 0 && mom.perp() >= 10)
			{
			  ++netaq1;
			  ++netatot;
			}
		      if(tfTrk->quality() > 1 && mom.perp() >= 10) ++netaq2;
		      if(tfTrk->quality() > 2 && mom.perp() >= 10) ++netaq3;
		      
		      if((tfTrk->quality() > 0 || tfTrk->eta_packed() < 8) && mom.perp() >= 10) ++nLoose;
		      if(tfTrk->quality() > 2 && mom.perp() >= 10) ++nTight;

		      /* Efficiency vs. Pt */
		      if(fabs(genEta) >= 1.2 && fabs(genEta) < 2.1)
			{
			  if(tfTrk->quality() > 0 && tfTrk->ptValue() >= 0)
			    {
			      ++nPt0;
			      if(tfTrk->quality() > 1) ++nPt0q1;
			      if(tfTrk->quality() > 2) ++nPt0q2;
			    }
			  if(tfTrk->quality() > 0 && tfTrk->ptValue() >= 10) ++nPt10;
			  if(tfTrk->quality() > 0 && tfTrk->ptValue() >= 20) ++nPt20;
			  if(tfTrk->quality() > 0 && tfTrk->ptValue() >= 40) ++nPt40;
			  if(tfTrk->quality() > 0 && tfTrk->ptValue() >= 60) ++nPt60;
			}
		    }
		}
	      // fill histos
	      if(nPt0 > 0)
		{
		  hPt0->Fill(mom.perp());
		  if(nPt0q1 > 0) hPt0q1->Fill(mom.perp());
		  if(nPt0q2 > 0) hPt0q2->Fill(mom.perp());
		}
	      if(nPt10 > 0) hPt10->Fill(mom.perp());
	      if(nPt20 > 0) hPt20->Fill(mom.perp());
	      if(nPt40 > 0) hPt40->Fill(mom.perp());
	      if(nPt60 > 0) hPt60->Fill(mom.perp());

	      if(nLoose > 0) hEtaLoose->Fill(fabs(genEta));
	      if(nTight > 0) hEtaTight->Fill(fabs(genEta));
	      if(netaq1 > 0) hEtaQ1->Fill(fabs(genEta));
	      if(netaq2 > 0) hEtaQ2->Fill(fabs(genEta));
	      if(netaq3 > 0) hEtaQ3->Fill(fabs(genEta));
	      if(netatot > 0) hEtaTot->Fill(fabs(genEta));
	    } // |partid| == 13
    } // simTrk loop
}
