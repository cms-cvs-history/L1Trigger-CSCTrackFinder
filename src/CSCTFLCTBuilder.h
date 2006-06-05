#ifndef CSCTrackFinder_CSCTFLCTBuilder_h
#define CSCTrackFinder_CSCTFLCTBuilder_h

#include <FWCore/ParameterSet/interface/ParameterSet.h>
#include <DataFormats/CSCDigi/interface/CSCCorrelatedLCTDigiCollection.h>

class CSCMuonPortCard;


class CSCTFLCTBuilder
{
 public:
  CSCTFLCTBuilder(const edm::ParameterSet&);
  ~CSCTFLCTBuilder();

  void buildLCTs(const CSCCorrelatedLCTDigiCollection*, 
		 CSCCorrelatedLCTDigiCollection*) const;
  
 private:

  CSCMuonPortCard* m_muonportcard;
  int m_minBX, m_maxBX;

};

#endif
