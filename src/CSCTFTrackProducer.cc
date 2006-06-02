#include <L1Trigger/CSCTrackFinder/src/CSCTFTrackProducer.h>

#include <vector>
#include <DataFormats/L1CSCTrackFinder/interface/L1Track.h>
#include <DataFormats/CSCDigi/interface/CSCCorrelatedLCTDigiCollection.h>

#include <FWCore/Framework/interface/Handle.h>
#include "FWCore/Framework/interface/Event.h"

CSCTFTrackProducer::CSCTFTrackProducer(const edm::ParameterSet& pset)
{
  my_builder = new CSCTFTrackBuilder(pset);
  produces<std::vector<csc::L1Track> >();
}

CSCTFTrackProducer::~CSCTFTrackProducer()
{
  delete my_builder;
  my_builder = NULL;
}

void CSCTFTrackProducer::produce(edm::Event & e, const edm::EventSetup& c)
{
  edm::Handle<CSCCorrelatedLCTDigiCollection> LCTs;
  std::auto_ptr<std::vector<csc::L1Track> > track_product;

  my_builder->buildTracks(LCTs.product(), track_product.get());
  
  e.put(track_product);
}
