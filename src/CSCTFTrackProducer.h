#ifndef CSCTrackFinder_CSCTFTrackProducer_h
#define CSCTrackFinder_CSCTFTrackProducer_h

#include <FWCore/Framework/interface/EDProducer.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>

#include <L1Trigger/CSCTrackFinder/src/CSCTFTrackBuilder.h>

class CSCTFTrackProducer : public edm::EDProducer
{
 public:

  CSCTFTrackProducer(const edm::ParameterSet&);

  virtual ~CSCTFTrackProducer();

  void produce(edm::Event & e, const edm::EventSetup& c);

 private:
  CSCTFTrackBuilder* my_builder;
};

#endif
