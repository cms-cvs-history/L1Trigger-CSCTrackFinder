/** 
 * Demo analyzer for reading digis.
 * Validates against raw data unpack.
 * author L. Gray 2/26/06 
 * ripped from Jeremy's and Rick's analyzers
 *   
 */

#include <fstream>
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Handle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include <Geometry/Records/interface/MuonGeometryRecord.h>

#include "DataFormats/MuonDetId/interface/CSCTriggerNumbering.h"
#include "DataFormats/MuonDetId/interface/CSCDetId.h"

#include "L1Trigger/CSCCommonTrigger/interface/CSCBitWidths.h"
#include "L1Trigger/CSCTrackFinder/interface/CSCSectorReceiverLUT.h"
#include "L1Trigger/CSCCommonTrigger/interface/CSCTriggerGeometry.h"

#include "L1Trigger/CSCTrackFinder/interface/CSCMakeSRLUT.h"

CSCMakeSRLUT::CSCMakeSRLUT(edm::ParameterSet const& conf)
{
  writeLocalPhi = conf.getUntrackedParameter<bool>("WriteLocalPhi",true);
  station = conf.getUntrackedParameter<int>("Station",-1);
  sector = conf.getUntrackedParameter<int>("Sector",-1);
  endcap = conf.getUntrackedParameter<int>("Endcap",-1);
  writeGlobalPhi = conf.getUntrackedParameter<bool>("WriteGlobalPhi",true);
  writeGlobalEta = conf.getUntrackedParameter<bool>("WriteGlobalEta",true);
  binary = conf.getUntrackedParameter<bool>("BinaryOutput",true);
  LUTparam = conf.getParameter<edm::ParameterSet>("lutParam");
  
  //init Sector Receiver LUTs
  for(int e = CSCDetId::minEndcapId(); e <= CSCDetId::maxEndcapId(); ++e)
    for(int se = CSCTriggerNumbering::minTriggerSectorId(); se <= CSCTriggerNumbering::maxTriggerSectorId(); ++se)
      for(int st = CSCDetId::minStationId(); st <= CSCDetId::maxStationId(); ++st)
	{	
	  if(st == 1)
	    for(int ss = CSCTriggerNumbering::minTriggerSubSectorId(); ss <= CSCTriggerNumbering::maxTriggerSubSectorId(); ++ss)
	      {		
		mySR[e-1][se-1][ss-1][st-1] = new CSCSectorReceiverLUT(e,se,ss,st,LUTparam);
	      }
	  else
	    {
	      mySR[e-1][se-1][0][st-1] = new CSCSectorReceiverLUT(e,se,0,st,LUTparam);
	      mySR[e-1][se-1][1][st-1] = mySR[e-1][se-1][0][st-1]; // Save space.
	    }	  
	}
}

CSCMakeSRLUT::~CSCMakeSRLUT()
{
  for(int e = CSCDetId::minEndcapId(); e <= CSCDetId::maxEndcapId(); ++e)
    for(int se = CSCTriggerNumbering::minTriggerSectorId(); se <= CSCTriggerNumbering::maxTriggerSectorId(); ++se)
      for(int ss = CSCTriggerNumbering::minTriggerSubSectorId(); ss <= CSCTriggerNumbering::maxTriggerSubSectorId(); ++ss)
	for(int st = CSCDetId::minStationId(); st <= CSCDetId::maxStationId(); ++st)
	  {  
	    if(mySR[e-1][se-1][ss-1][st-1]) 
	      {
		delete mySR[e-1][se-1][ss-1][st-1];
		mySR[e-1][se-1][ss-1][st-1] = NULL;
	      }
	  }
}

void CSCMakeSRLUT::analyze(edm::Event const& e, edm::EventSetup const& iSetup) 
{
  edm::ESHandle<CSCGeometry> pDD;

  iSetup.get<MuonGeometryRecord>().get( pDD );
  CSCTriggerGeometry::setGeometry(pDD);

  if(writeLocalPhi)
    {
      std::string filename = std::string("LocalPhiLUT") + ((binary) ? std::string(".bin") : std::string(".dat"));
      std::ofstream LocalPhiLUT(filename.c_str());
      for(int i=0; i < 1<<CSCBitWidths::kLocalPhiAddressWidth; ++i)
	{
	  CSCSectorReceiverLUT::lclphidat thedata = mySR[0][0][0][0]->localPhi(i);
	  if(binary) LocalPhiLUT.write(reinterpret_cast<char*>(&thedata), sizeof(unsigned short));
	  else LocalPhiLUT << std::dec << (*reinterpret_cast<unsigned short*>(&thedata)) << std::endl;
	}
    }

  if(writeGlobalPhi)
    {}

  if(writeGlobalEta)
    {
      std::string prefix = "GlobalEtaME";
      std::ofstream GlobalEtaLUT;

      for(int e = CSCDetId::minEndcapId(); e <= CSCDetId::maxEndcapId(); ++e)
	if(endcap == -1 || endcap == e)
	  for(int se = CSCTriggerNumbering::minTriggerSectorId(); se <= CSCTriggerNumbering::maxTriggerSectorId(); ++se)
	    if(sector == -1 || sector == se)
	      for(int st = CSCDetId::minStationId(); st <= CSCDetId::maxStationId(); ++st)
		if(station == -1 || station == st)
		  for(int ss = CSCTriggerNumbering::minTriggerSubSectorId(); ss <= CSCTriggerNumbering::maxTriggerSubSectorId(); ++ss)
		    {
		      
		      CSCSectorReceiverLUT::gbletadat thedata;
		      if(st == 1)
			{		    
			  std::string fname = prefix + mySR[e-1][se-1][ss-1][st-1]->encodeFileIndex() + fileSuffix();
			  GlobalEtaLUT.open(fname.c_str());
			  for(int i=0; i < 1 << CSCBitWidths::kLocalPhiAddressWidth; ++i)
			    {
			      thedata = mySR[e-1][se-1][ss-1][st-1]->globalEtaME(i);
			      if(binary) GlobalEtaLUT.write(reinterpret_cast<char*>(&thedata), sizeof(unsigned short));
			      else GlobalEtaLUT << std::dec << (*reinterpret_cast<unsigned short*>(&thedata)) << std::endl;
			    }
			  GlobalEtaLUT.close();
			}
		      else
			{
			  if(ss == 1)
			    {		
			      std::string fname = prefix + mySR[e-1][se-1][0][st-1]->encodeFileIndex() + fileSuffix();
			      GlobalEtaLUT.open(fname.c_str());
			      for(int i=0; i < 1<<CSCBitWidths::kLocalPhiAddressWidth; ++i)
				{
				  thedata = mySR[e-1][se-1][0][st-1]->globalEtaME(i);
				  if(binary) GlobalEtaLUT.write(reinterpret_cast<char*>(&thedata), sizeof(unsigned short));
				  else GlobalEtaLUT << std::hex << (*reinterpret_cast<unsigned short*>(&thedata)) << std::endl;
				}
			      GlobalEtaLUT.close();
			    }
			}
		    }
    }
}

std::string CSCMakeSRLUT::fileSuffix() const {
  std::string fileName = "";
  fileName += ((binary) ? "LUT.bin" : "LUT.dat");
  return fileName;
}
