#include <L1Trigger/CSCTrackFinder/src/CSCTFLCTBuilder.h>
#include <L1Trigger/CSCTrackFinder/interface/CSCMuonPortCard.h>

#include <DataFormats/MuonDetId/interface/CSCTriggerNumbering.h>
#include <DataFormats/MuonDetId/interface/CSCDetId.h>

CSCTFLCTBuilder::CSCTFLCTBuilder(const edm::ParameterSet& pset)
{
  m_minBX = pset.getUntrackedParameter<int>("MinBX",-3);
  m_maxBX = pset.getUntrackedParameter<int>("MaxBX",3);

  m_muonportcard = new CSCMuonPortCard();
}

CSCTFLCTBuilder::~CSCTFLCTBuilder()
{
  delete m_muonportcard; 
  m_muonportcard = NULL;
}

void CSCTFLCTBuilder::buildLCTs(const CSCCorrelatedLCTDigiCollection* input, 
				CSCCorrelatedLCTDigiCollection* output) const
{
  m_muonportcard->loadDigis(*input);

  std::vector<CSCTrackStub> result;
  for(int bx = m_minBX; bx <= m_maxBX; ++bx)
    for(int e = CSCDetId::minEndcapId(); e <= CSCDetId::maxEndcapId(); ++e)
      for(int st = CSCDetId::minStationId(); st <= CSCDetId::maxStationId(); ++st)
	for(int se = CSCTriggerNumbering::minTriggerSectorId(); 
	    se <= CSCTriggerNumbering::maxTriggerSectorId(); ++se)
	  {
	    if(st == 1)
	      {		
		std::vector<CSCTrackStub> subs1, subs2;
		subs1 = m_muonportcard->sort(e, st, se, 1, bx);
		subs2 = m_muonportcard->sort(e, st, se, 2, bx);
		result.insert(result.end(), subs1.begin(), subs1.end());
		result.insert(result.end(), subs2.begin(), subs2.end());		
	      }
	    else
	      {
		std::vector<CSCTrackStub> sector;
		sector = m_muonportcard->sort(e, st, se, 0, bx);
		result.insert(result.end(), sector.begin(), sector.end());
	      }
	  }

  std::vector<CSCTrackStub>::const_iterator itr = result.begin();
  for(; itr != result.end(); itr++)
    {
      output->insertDigi(itr->getDetId(), itr->getDigi());
    }
}
