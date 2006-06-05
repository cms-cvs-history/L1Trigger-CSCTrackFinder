#ifndef CSCTrackFinder_CSCTFLCTProducer_h
#define CSCTrackFinder_CSCTFLCTProducer_h

#include <string>

#include <FWCore/Framework/interface/EDProducer.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>

#include <L1Trigger/CSCTrackFinder/src/CSCTFLCTBuilder.h>

class CSCTFLCTProducer : public edm::EDProducer
{
 public:

  CSCTFLCTProducer(const edm::ParameterSet&);

  virtual ~CSCTFLCTProducer();

  void produce(edm::Event & e, const edm::EventSetup& c);

 private:
  CSCTFLCTBuilder* my_builder;
  std::string input_module;
};

#endif
