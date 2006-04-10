/** 
 * Demo analyzer for reading digis.
 * Validates against raw data unpack.
 * author L. Gray 2/26/06 
 * ripped from Jeremy's and Rick's analyzers
 *   
 */

#include <fstream>
#include <iostream>
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

#include <FWCore/MessageLogger/interface/MessageLogger.h>

#include "L1Trigger/CSCTrackFinder/interface/CSCCompareSRLUTs.h"

CSCCompareSRLUTs::CSCCompareSRLUTs(edm::ParameterSet const& conf)
{
  station = conf.getUntrackedParameter<int>("Station",1);
  sector = conf.getUntrackedParameter<int>("Sector",1);
  subsector = conf.getUntrackedParameter<int>("SubSector",1);
  endcap = conf.getUntrackedParameter<int>("Endcap",1);
  binary = conf.getUntrackedParameter<bool>("BinaryInput",false);
  LUTparam = conf.getParameter<edm::ParameterSet>("lutParam");
  
  myLUT = new CSCSectorReceiverLUT(endcap, sector, subsector, station, edm::ParameterSet());
  testLUT = new CSCSectorReceiverLUT(endcap, sector, subsector, station, LUTparam);
}

CSCCompareSRLUTs::~CSCCompareSRLUTs()
{
  delete myLUT;
  delete testLUT;
}

void CSCCompareSRLUTs::analyze(edm::Event const& e, edm::EventSetup const& iSetup) 
{
  // set geometry pointer
  edm::ESHandle<CSCGeometry> pDD;

  iSetup.get<MuonGeometryRecord>().get( pDD );
  CSCTriggerGeometry::setGeometry(pDD);  
  
  
  // test local phi
  // should match for all inputs
  for(unsigned int address = 0; address < 1<<CSCBitWidths::kLocalPhiAddressWidth; ++address)
    {
      unsigned short mLUT, tstLUT;
      CSCSectorReceiverLUT::lclphidat mout, tstout;
      mout = myLUT->localPhi(address);
      tstout = testLUT->localPhi(address);
      mLUT = (*reinterpret_cast<unsigned short*>(&mout));
      tstLUT = (*reinterpret_cast<unsigned short*>(&tstout));
      if(mLUT != tstLUT)
	edm::LogInfo("mismatch|LocalPhi") << mLUT<< " != " << tstLUT;
    }

  double ntot = 0.0, nmatch = 0.0, nwithinone = 0.0;
  //test global eta
  // should match for all valid inputs
  for(int c = CSCTriggerNumbering::minTriggerCscId(); c <= CSCTriggerNumbering::maxTriggerCscId(); ++c)
    {
      CSCSectorReceiverLUT::gbletadat mgEta, tstgEta;

      CSCTriggerGeomManager* geom = CSCTriggerGeometry::get();
      CSCChamber* thechamber = geom->chamber(endcap, station, sector, subsector, c);

      if(thechamber)
	{
	  const CSCLayerGeometry* layergeom = thechamber->layer(3)->geometry();
	  int nWireGroups = layergeom->numberOfWireGroups();

	  for(int wg = 0; wg < nWireGroups; ++wg)
	    for(int phil = 0; phil < 4; ++phil)
	      {

		ntot += 1.0;
		unsigned theadd = (c<<15) | (wg<<8) | (phil << 6) | 0;
		
		mgEta = myLUT->globalEtaME(theadd);
		tstgEta = testLUT->globalEtaME(theadd);
		unsigned short my = (*reinterpret_cast<unsigned short*>(&mgEta));
		unsigned short test = (*reinterpret_cast<unsigned short*>(&tstgEta));
		
		if(my != test)
		  {
		    edm::LogInfo("mismatch:GlobalEta") << c << ' ' << phil << ' ' << wg << ' '
						       << my << " != " << test;
		  }
		else if( my == test )
		  nmatch += 1.0;
		if( my == test + 1 || my == test - 1 )
		  nwithinone += 1.0;
	      }
	}
    }
  edm::LogInfo("MatchingInfo") << "PERCENT MATCHING GLOBAL ETA VALUES: "<< nmatch/ntot;
  edm::LogInfo("MatchingInfo") << "PERCENT WITHIN ONE ETA UNIT: " << nwithinone/ntot;
  edm::LogInfo("MatchingInfo") << "PERCENT ACCEPTABLE: " << (nmatch + nwithinone)/ntot;

}


