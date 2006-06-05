#ifndef CSCTrackFinder_CSCTFCandidateProducer_h
#define CSCTrackFinder_CSCTFCandidateProducer_h

#include <string>

#include <FWCore/Framework/interface/EDProducer.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>

class CSCTFCandidateBuilder;

class CSCTFCandidateProducer : public edm::EDProducer
{
 public:

  CSCTFCandidateProducer(const edm::ParameterSet&);

  virtual ~CSCTFCandidateProducer();

  void produce(edm::Event & e, const edm::EventSetup& c);

 private:
  std::string input_module;
  CSCTFCandidateBuilder* my_builder;
};

#endif
