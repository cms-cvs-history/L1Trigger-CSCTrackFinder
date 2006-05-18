#include <L1Trigger/CSCTrackFinder/interface/CSCMuonPortCard.h>

void CSCMuonPortCard::loadDigis(const CSCCorrelatedLCTDigiCollection& thedigis)
{
  CSCCorrelatedLCTDigiCollection::DigiRangeIterator Citer;

  // First step is to put everything from the digi container into a trigger container.
  // This allows us to sort per BX more easily.
  for(Citer = thedigis.begin(); Citer != thedigis.end(); Citer++)
    {
      CSCCorrelatedLCTDigiCollection::const_iterator Diter = (*Citer).second.first;
      CSCCorrelatedLCTDigiCollection::const_iterator Dend = (*Citer).second.second;

      for(; Diter != Dend; Diter++)
	{
	  CSCTrackStub theStub((*Diter),(*Citer).first);
	  _stubs.push_back(theStub);
	}     
    }  
}

std::vector<CSCTrackStub> CSCMuonPortCard::sort(const unsigned& sector, const unsigned& station, const int& bx)
{
  std::vector<CSCTrackStub> result;
  return result;
}
