#include <L1Trigger/CSCTrackFinder/src/CSCTFLCTProducer.h>
#include <L1Trigger/CSCTrackFinder/src/CSCTFLCTBuilder.h>

#include <vector>
#include <DataFormats/L1CSCTrackFinder/interface/L1Track.h>
#include <DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h>

#include <FWCore/Framework/interface/Handle.h>
#include <FWCore/Framework/interface/Event.h>

CSCTFLCTProducer::CSCTFLCTProducer(const edm::ParameterSet& pset)
{
  edm::ParameterSet mpc_pset = pset.getParameter<edm::ParameterSet>("MuonPortCard");
  my_builder = new CSCTFLCTBuilder(mpc_pset);
  produces<CSCCorrelatedLCTDigiCollection>();
  input_module = pset.getUntrackedParameter<std::string>("CorrelatedLCTProducer","lctproducer");
}

CSCTFLCTProducer::~CSCTFLCTProducer()
{
  delete my_builder;
  my_builder = NULL;
}

void CSCTFLCTProducer::produce(edm::Event & e, const edm::EventSetup& c)
{
  edm::Handle<CSCCorrelatedLCTDigiCollection> input_lcts;
  std::auto_ptr<CSCCorrelatedLCTDigiCollection> selected_lcts(new CSCCorrelatedLCTDigiCollection());

  e.getByLabel(input_module, input_lcts);

  my_builder->buildLCTs(input_lcts.product(), selected_lcts.get());
  
  e.put(selected_lcts);
}
