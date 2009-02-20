#include <L1Trigger/CSCTrackFinder/interface/CSCTFSectorProcessor.h>
#include <L1Trigger/CSCTrackFinder/interface/CSCTrackFinderDataTypes.h>
#include <DataFormats/MuonDetId/interface/CSCTriggerNumbering.h>

#include <FWCore/MessageLogger/interface/MessageLogger.h>

#include "CondFormats/L1TObjects/interface/L1MuCSCTFConfiguration.h"
#include "CondFormats/DataRecord/interface/L1MuCSCTFConfigurationRcd.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include <stdlib.h>
#include <sstream>

const std::string CSCTFSectorProcessor::FPGAs[5] = {"F1","F2","F3","F4","F5"};

CSCTFSectorProcessor::CSCTFSectorProcessor(const unsigned& endcap,
					   const unsigned& sector,
					   const edm::ParameterSet& pset,
					   bool tmb07,
					   const L1MuTriggerScales* scales,
					   const L1MuTriggerPtScale* ptScale)
{
  m_endcap = endcap;
  m_sector = sector;
  TMB07    = tmb07;

  // Parameter below should always present in ParameterSet:
  m_latency = pset.getParameter<unsigned>("CoreLatency");
  m_minBX = pset.getParameter<int>("MinBX");
  m_maxBX = pset.getParameter<int>("MaxBX");
  initializeFromPSet = pset.getParameter<bool>("initializeFromPSet");
  if( m_maxBX-m_minBX >= 7 ) edm::LogWarning("CSCTFTrackBuilder::ctor")<<" BX window width >= 7BX. Resetting m_maxBX="<<(m_maxBX=m_minBX+6);

  // All following parameters may appear in either ParameterSet of in EventSetup; uninitialize:
  m_bxa_depth = -1;
  m_allowALCTonly = -1;
  m_allowCLCTonly = -1;
  m_preTrigger = -1;

  for(int index=0; index<6; index++) m_etawin[index] = -1;
  for(int index=0; index<8; index++) m_etamin[index] = -1;
  for(int index=0; index<8; index++) m_etamax[index] = -1;

  m_mindphip=-1;
  m_mindeta_accp=-1;
  m_maxdeta_accp=-1;
  m_maxdphi_accp=-1;

  kill_fiber = -1;
  QualityEnableME1a = -1;
  QualityEnableME1b = -1;
  QualityEnableME1c = -1;
  QualityEnableME1d = -1;
  QualityEnableME1e = -1;
  QualityEnableME1f = -1;
  QualityEnableME2a = -1;
  QualityEnableME2b = -1;
  QualityEnableME2c = -1;
  QualityEnableME3a = -1;
  QualityEnableME3b = -1;
  QualityEnableME3c = -1;
  QualityEnableME4a = -1;
  QualityEnableME4b = -1;
  QualityEnableME4c = -1;

  run_core = -1;
  trigger_on_ME1a = -1;
  trigger_on_ME1b = -1;
  trigger_on_ME2  = -1;
  trigger_on_ME3  = -1;
  trigger_on_ME4  = -1;
  trigger_on_MB1a = -1;
  trigger_on_MB1d = -1;
  singlesTrackPt  = -1;
  singlesTrackOutput = -1;
  rescaleSinglesPhi  = -1;

  if(initializeFromPSet) readParameters(pset);

    edm::ParameterSet srLUTset = pset.getParameter<edm::ParameterSet>("SRLUT");
    for(int i = 1; i <= 4; ++i)
      {
        if(i == 1)
          for(int j = 0; j < 2; j++)
          {
            srLUTs_[FPGAs[j]] = new CSCSectorReceiverLUT(endcap, sector, j+1, i, srLUTset, TMB07);
	      }
          else
            srLUTs_[FPGAs[i]] = new CSCSectorReceiverLUT(endcap, sector, 0, i, srLUTset, TMB07);
      }

  core_ = new CSCTFSPCoreLogic();

  if(initializeFromPSet){
    edm::ParameterSet ptLUTset = pset.getParameter<edm::ParameterSet>("PTLUT");
    ptLUT_ = new CSCTFPtLUT(ptLUTset, scales, ptScale);
    LogDebug("CSCTFSectorProcessor") << "Using stand-alone PT LUT for endcap="<<m_endcap<<", sector="<<m_sector;
  } else {
    ptLUT_=0;
    LogDebug("CSCTFSectorProcessor") << "Looking for PT LUT in EventSetup for endcap="<<m_endcap<<", sector="<<m_sector;
  }
}

void CSCTFSectorProcessor::initialize(const edm::EventSetup& c){
  if(!initializeFromPSet){
    // Only pT lut can be initialized from EventSetup, all front LUTs are initialized locally from their parametrizations
    LogDebug("CSCTFSectorProcessor") << "Initializing pT LUT from EventSetup";
    ptLUT_ = new CSCTFPtLUT(c);

    // Extract from EventSetup alternative (to the one, used in constructor) ParameterSet
    edm::ESHandle<L1MuCSCTFConfiguration> config;
    c.get<L1MuCSCTFConfigurationRcd>().get(config);
    // And initialize only those parameters, which left uninitialized during construction
//std::cout<<"Initializing endcap: "<<m_endcap<<" sector:"<<m_sector<<std::endl<<config.product()->parameters((m_endcap-1)*2+(m_sector-1))<<std::endl;;
    readParameters(config.product()->parameters((m_endcap-1)*2+(m_sector-1)));
  }
  // Check if parameters were not initialized in both: constuctor (from .cf? file) and initialize method (from EventSetup)
  if(m_bxa_depth    <0) throw cms::Exception("CSCTFSectorProcessor")<<"BXAdepth parameter left uninitialized for endcap="<<m_endcap<<", sector="<<m_sector;
  if(m_allowALCTonly<0) throw cms::Exception("CSCTFSectorProcessor")<<"AllowALCTonly parameter left uninitialized for endcap="<<m_endcap<<", sector="<<m_sector;
  if(m_allowCLCTonly<0) throw cms::Exception("CSCTFSectorProcessor")<<"AllowCLCTonly parameter left uninitialized for endcap="<<m_endcap<<", sector="<<m_sector;
  if(m_preTrigger   <0) throw cms::Exception("CSCTFSectorProcessor")<<"PreTrigger parameter left uninitialized for endcap="<<m_endcap<<", sector="<<m_sector;
  if(m_mindphip    <0) throw cms::Exception("CSCTFSectorProcessor")<<"mindphip parameter left uninitialized for endcap="<<m_endcap<<", sector="<<m_sector;
  if(m_mindeta_accp<0) throw cms::Exception("CSCTFSectorProcessor")<<"mindeta_accp parameter left uninitialized for endcap="<<m_endcap<<", sector="<<m_sector;
  if(m_maxdeta_accp<0) throw cms::Exception("CSCTFSectorProcessor")<<"maxdeta_accp parameter left uninitialized for endcap="<<m_endcap<<", sector="<<m_sector;
  if(m_maxdphi_accp<0) throw cms::Exception("CSCTFSectorProcessor")<<"maxdphi_accp parameter left uninitialized for endcap="<<m_endcap<<", sector="<<m_sector;
  for(int index=0; index<8; index++) if(m_etamax[index]<0) throw cms::Exception("CSCTFSectorProcessor")<<"Some ("<<(8-index)<<") of EtaMax parameters left uninitialized for endcap="<<m_endcap<<", sector="<<m_sector;
  for(int index=0; index<8; index++) if(m_etamin[index]<0) throw cms::Exception("CSCTFSectorProcessor")<<"Some ("<<(8-index)<<") of EtaMin parameters left uninitialized for endcap="<<m_endcap<<", sector="<<m_sector;
  for(int index=0; index<6; index++) if(m_etawin[index]<0) throw cms::Exception("CSCTFSectorProcessor")<<"Some ("<<(6-index)<<") of EtaWindows parameters left uninitialized for endcap="<<m_endcap<<", sector="<<m_sector;
  if(kill_fiber     <0) throw cms::Exception("CSCTFTrackBuilder")<<"kill_fiber parameter left uninitialized";
  if(run_core       <0) throw cms::Exception("CSCTFTrackBuilder")<<"run_core parameter left uninitialized";
  if(trigger_on_ME1a<0) throw cms::Exception("CSCTFTrackBuilder")<<"trigger_on_ME1a parameter left uninitialized";
  if(trigger_on_ME1b<0) throw cms::Exception("CSCTFTrackBuilder")<<"trigger_on_ME1b parameter left uninitialized";
  if(trigger_on_ME2 <0) throw cms::Exception("CSCTFTrackBuilder")<<"trigger_on_ME2 parameter left uninitialized";
  if(trigger_on_ME3 <0) throw cms::Exception("CSCTFTrackBuilder")<<"trigger_on_ME3 parameter left uninitialized";
  if(trigger_on_ME4 <0) throw cms::Exception("CSCTFTrackBuilder")<<"trigger_on_ME4 parameter left uninitialized";
  if(trigger_on_MB1a<0) throw cms::Exception("CSCTFTrackBuilder")<<"trigger_on_MB1a parameter left uninitialized";
  if(trigger_on_MB1d<0) throw cms::Exception("CSCTFTrackBuilder")<<"trigger_on_MB1d parameter left uninitialized";
  if( trigger_on_ME1a>0 || trigger_on_ME1b>0 ||trigger_on_ME2>0  ||
      trigger_on_ME3>0  || trigger_on_ME4>0  ||trigger_on_MB1a>0 ||trigger_on_MB1d>0 ){
      if(singlesTrackPt<0) throw cms::Exception("CSCTFTrackBuilder")<<"singlesTrackPt parameter left uninitialized";
      if(singlesTrackOutput<0) throw cms::Exception("CSCTFTrackBuilder")<<"singlesTrackOutput parameter left uninitialized";
      if(rescaleSinglesPhi<0)  throw cms::Exception("CSCTFTrackBuilder")<<"rescaleSinglesPhi parameter left uninitialized";
  }
  if(QualityEnableME1a<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME1a parameter left uninitialized";
  if(QualityEnableME1b<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME1b parameter left uninitialized";
  if(QualityEnableME1c<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME1c parameter left uninitialized";
  if(QualityEnableME1d<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME1d parameter left uninitialized";
  if(QualityEnableME1e<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME1e parameter left uninitialized";
  if(QualityEnableME1f<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME1f parameter left uninitialized";
  if(QualityEnableME2a<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME2a parameter left uninitialized";
  if(QualityEnableME2b<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME2b parameter left uninitialized";
  if(QualityEnableME2c<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME2c parameter left uninitialized";
  if(QualityEnableME3a<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME3a parameter left uninitialized";
  if(QualityEnableME3b<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME3b parameter left uninitialized";
  if(QualityEnableME3c<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME3c parameter left uninitialized";
  if(QualityEnableME4a<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME4a parameter left uninitialized";
  if(QualityEnableME4b<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME4b parameter left uninitialized";
  if(QualityEnableME4c<0) throw cms::Exception("CSCTFTrackBuilder")<<"QualityEnableME4c parameter left uninitialized";
}

void CSCTFSectorProcessor::readParameters(const edm::ParameterSet& pset){
      m_bxa_depth = pset.getParameter<unsigned>("BXAdepth");
      m_allowALCTonly = ( pset.getParameter<bool>("AllowALCTonly") ? 1 : 0 );
      m_allowCLCTonly = ( pset.getParameter<bool>("AllowCLCTonly") ? 1 : 0 );
      m_preTrigger = pset.getParameter<unsigned>("PreTrigger");

  std::vector<unsigned>::const_iterator iter;
  int index=0;
      std::vector<unsigned> etawins = pset.getParameter<std::vector<unsigned> >("EtaWindows");
      for(iter=etawins.begin(),index=0; iter!=etawins.end()&&index<6; iter++,index++) m_etawin[index] = *iter;
      std::vector<unsigned> etamins = pset.getParameter<std::vector<unsigned> >("EtaMin");
      for(iter=etamins.begin(),index=0; iter!=etamins.end()&&index<8; iter++,index++) m_etamin[index] = *iter;
      std::vector<unsigned> etamaxs = pset.getParameter<std::vector<unsigned> >("EtaMax");
      for(iter=etamaxs.begin(),index=0; iter!=etamaxs.end()&&index<8; iter++,index++) m_etamax[index] = *iter;

	  m_mindphip = pset.getParameter<unsigned>("mindphip");
      m_mindeta_accp = pset.getParameter<unsigned>("mindeta_accp");
      m_maxdeta_accp = pset.getParameter<unsigned>("maxdeta_accp");
      m_maxdphi_accp = pset.getParameter<unsigned>("maxdphi_accp");
      kill_fiber = pset.getParameter<unsigned>("kill_fiber");
      run_core = pset.getParameter<bool>("run_core");
      trigger_on_ME1a = pset.getParameter<bool>("trigger_on_ME1a");
      trigger_on_ME1b = pset.getParameter<bool>("trigger_on_ME1b");
      trigger_on_ME2 = pset.getParameter<bool>("trigger_on_ME2");
      trigger_on_ME3 = pset.getParameter<bool>("trigger_on_ME3");
      trigger_on_ME4 = pset.getParameter<bool>("trigger_on_ME4");
      trigger_on_MB1a = pset.getParameter<bool>("trigger_on_MB1a");
      trigger_on_MB1d = pset.getParameter<bool>("trigger_on_MB1d");
      singlesTrackPt = pset.getParameter<unsigned int>("singlesTrackPt");
      singlesTrackOutput = pset.getParameter<unsigned int>("singlesTrackOutput");
      rescaleSinglesPhi  = pset.getParameter<bool>("rescaleSinglesPhi");
      QualityEnableME1a = pset.getParameter<unsigned int>("QualityEnableME1a");
      QualityEnableME1b = pset.getParameter<unsigned int>("QualityEnableME1b");
      QualityEnableME1c = pset.getParameter<unsigned int>("QualityEnableME1c");
      QualityEnableME1d = pset.getParameter<unsigned int>("QualityEnableME1d");
      QualityEnableME1e = pset.getParameter<unsigned int>("QualityEnableME1e");
      QualityEnableME1f = pset.getParameter<unsigned int>("QualityEnableME1f");
      QualityEnableME2a = pset.getParameter<unsigned int>("QualityEnableME2a");
      QualityEnableME2b = pset.getParameter<unsigned int>("QualityEnableME2b");
      QualityEnableME2c = pset.getParameter<unsigned int>("QualityEnableME2c");
      QualityEnableME3a = pset.getParameter<unsigned int>("QualityEnableME3a");
      QualityEnableME3b = pset.getParameter<unsigned int>("QualityEnableME3b");
      QualityEnableME3c = pset.getParameter<unsigned int>("QualityEnableME3c");
      QualityEnableME4a = pset.getParameter<unsigned int>("QualityEnableME4a");
      QualityEnableME4b = pset.getParameter<unsigned int>("QualityEnableME4b");
      QualityEnableME4c = pset.getParameter<unsigned int>("QualityEnableME4c");
}

CSCTFSectorProcessor::~CSCTFSectorProcessor()
{
  for(int i = 0; i < 5; ++i)
    {
      if(srLUTs_[FPGAs[i]]) delete srLUTs_[FPGAs[i]]; // delete the pointer
      srLUTs_[FPGAs[i]] = NULL; // point it at a safe place
    }

  delete core_;
  core_ = NULL;

  if(ptLUT_) delete ptLUT_;
  ptLUT_ = NULL;
}

bool CSCTFSectorProcessor::run(const CSCTriggerContainer<csctf::TrackStub>& stubs)
{

  if( !ptLUT_ )
    throw cms::Exception("Initialize CSC TF LUTs first (missed call to CSCTFTrackProducer::beginJob?)")<<"CSCTFSectorProcessor::run";


  l1_tracks.clear();
  dt_stubs.clear();
  stub_vec_filtered.clear();

  std::vector<csctf::TrackStub> stub_vec = stubs.get();

  /** STEP ZERO
   *  Remove stubs, which were masked out by kill_fiber or QualityEnable parameters
   */
  for(std::vector<csctf::TrackStub>::const_iterator itr=stub_vec.begin(); itr!=stub_vec.end(); itr++)
      switch( itr->station() ){
        case 5: stub_vec_filtered.push_back(*itr); break; // DT stubs get filtered by the core controll register
        case 4:
          switch( itr->getMPCLink() ){
            case 3: if( (kill_fiber&0x4000)==0 && QualityEnableME4c&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            case 2: if( (kill_fiber&0x2000)==0 && QualityEnableME4b&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            case 1: if( (kill_fiber&0x1000)==0 && QualityEnableME4a&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            default: edm::LogWarning("CSCTFSectorProcessor::run()") << "No MPC sorting for LCT: link="<<itr->getMPCLink()<<"\n";
          }
        break;
        case 3:
          switch( itr->getMPCLink() ){
            case 3: if( (kill_fiber&0x0800)==0 && QualityEnableME3c&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            case 2: if( (kill_fiber&0x0400)==0 && QualityEnableME3b&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            case 1: if( (kill_fiber&0x0200)==0 && QualityEnableME3a&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            default: edm::LogWarning("CSCTFSectorProcessor::run()") << "No MPC sorting for LCT: link="<<itr->getMPCLink()<<"\n";
          }
        break;
        case 2:
          switch( itr->getMPCLink() ){
            case 3: if( (kill_fiber&0x0100)==0 && QualityEnableME2c&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            case 2: if( (kill_fiber&0x0080)==0 && QualityEnableME2b&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            case 1: if( (kill_fiber&0x0040)==0 && QualityEnableME2a&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            default: edm::LogWarning("CSCTFSectorProcessor::run()") << "No MPC sorting for LCT: link="<<itr->getMPCLink()<<"\n";
          }
        break;
        case 1:
          switch( itr->getMPCLink() + (3*(CSCTriggerNumbering::triggerSubSectorFromLabels(CSCDetId(itr->getDetId().rawId())) - 1)) ){
            case 6: if( (kill_fiber&0x0020)==0 && QualityEnableME1f&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            case 5: if( (kill_fiber&0x0010)==0 && QualityEnableME1e&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            case 4: if( (kill_fiber&0x0008)==0 && QualityEnableME1d&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            case 3: if( (kill_fiber&0x0004)==0 && QualityEnableME1c&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            case 2: if( (kill_fiber&0x0002)==0 && QualityEnableME1b&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            case 1: if( (kill_fiber&0x0001)==0 && QualityEnableME1a&(1<<itr->getQuality()) ) stub_vec_filtered.push_back(*itr); break;
            default: edm::LogWarning("CSCTFSectorProcessor::run()") << "No MPC sorting for LCT: link="<<itr->getMPCLink()<<"\n";
          }
        break;
        default: edm::LogWarning("CSCTFSectorProcessor::run()") << "Invalid station # encountered: "<<itr->station()<<"\n";
      }

  /** STEP ONE
   *  We take stubs from the MPC and assign their eta and phi
   *  coordinates using the SR Lookup tables.
   *  This is independent of what BX we are on so we can
   *  process one large vector of stubs.
   *  After this we append the stubs gained from the DT system.
   */

  for(std::vector<csctf::TrackStub>::iterator itr=stub_vec_filtered.begin(); itr!=stub_vec_filtered.end(); itr++)
    {
      if(itr->station() != 5)
	{
	  CSCDetId id(itr->getDetId().rawId());
	  unsigned fpga = (id.station() == 1) ? CSCTriggerNumbering::triggerSubSectorFromLabels(id) - 1 : id.station();

          lclphidat lclPhi;
          try {
            lclPhi = srLUTs_[FPGAs[fpga]]->localPhi(itr->getStrip(), itr->getPattern(), itr->getQuality(), itr->getBend());
          } catch( cms::Exception &e ) {
            bzero(&lclPhi,sizeof(lclPhi));
            edm::LogWarning("CSCTFSectorProcessor:run()") << "Exception from LocalPhi LUT in " << FPGAs[fpga]
               << "(strip="<<itr->getStrip()<<",pattern="<<itr->getPattern()<<",quality="<<itr->getQuality()<<",bend="<<itr->getBend()<<")" <<std::endl;
          }
          gblphidat gblPhi;
          try {
            gblPhi = srLUTs_[FPGAs[fpga]]->globalPhiME(lclPhi.phi_local, itr->getKeyWG(), itr->cscid());
		  } catch( cms::Exception &e ) {
            bzero(&gblPhi,sizeof(gblPhi));
            edm::LogWarning("CSCTFSectorProcessor:run()") << "Exception from GlobalPhi LUT in " << FPGAs[fpga]
               << "(phi_local="<<lclPhi.phi_local<<",KeyWG="<<itr->getKeyWG()<<",csc="<<itr->cscid()<<")"<<std::endl;
          }
          gbletadat gblEta;
          try {
            gblEta = srLUTs_[FPGAs[fpga]]->globalEtaME(lclPhi.phi_bend_local, lclPhi.phi_local, itr->getKeyWG(), itr->cscid());
          } catch( cms::Exception &e ) {
            bzero(&gblEta,sizeof(gblEta));
            edm::LogWarning("CSCTFSectorProcessor:run()") << "Exception from GlobalEta LUT in " << FPGAs[fpga]
               << "(phi_bend_local="<<lclPhi.phi_bend_local<<",phi_local="<<lclPhi.phi_local<<",KeyWG="<<itr->getKeyWG()<<",csc="<<itr->cscid()<<")"<<std::endl;
          }

	  itr->setEtaPacked(gblEta.global_eta);
	  itr->setPhiPacked(gblPhi.global_phi);

	  if(itr->station() == 1) dt_stubs.push_back(*itr); // send stubs to DT

	  LogDebug("CSCTFSectorProcessor:run()") << "LCT found, processed by FPGA: " << FPGAs[fpga] << std::endl
						 << " LCT now has (eta, phi) of: (" << itr->etaValue() << "," << itr->phiValue() <<")\n";
	}
    }

  CSCTriggerContainer<csctf::TrackStub> processedStubs(stub_vec_filtered);

  /** STEP TWO
   *  We take the stubs filled by the SR LUTs and load them
   *  for processing into the SP core logic.
   *  After loading we run and then retrieve any tracks generated.
   */

  std::vector<csc::L1Track> tftks;

  if(run_core){
    core_->loadData(processedStubs, m_endcap, m_sector, m_minBX, m_maxBX);

    if( core_->run(m_endcap, m_sector, m_latency,
                   m_etamin[0], m_etamin[1], m_etamin[2], m_etamin[3],
                   m_etamin[4], m_etamin[5], m_etamin[6], m_etamin[7],
                   m_etamax[0], m_etamax[1], m_etamax[2], m_etamax[3],
                   m_etamax[4], m_etamax[5], m_etamax[6], m_etamax[7],
                   m_etawin[0], m_etawin[1], m_etawin[2],
                   m_etawin[3], m_etawin[4], m_etawin[5],
                   m_mindphip,  m_mindeta_accp,  m_maxdeta_accp, m_maxdphi_accp,
                   m_bxa_depth, m_allowALCTonly, m_allowCLCTonly, m_preTrigger,
                   m_minBX, m_maxBX) )
      {
        l1_tracks = core_->tracks();
      }

    tftks = l1_tracks.get();

    /** STEP THREE
     *  Now that we have the found tracks from the core,
     *  we must assign their Pt.
     */

    std::vector<csc::L1Track>::iterator titr = tftks.begin();

    for(; titr != tftks.end(); titr++)
      {
        ptadd thePtAddress(titr->ptLUTAddress());
        ptdat thePtData = ptLUT_->Pt(thePtAddress);

        if(thePtAddress.track_fr)
        {
          titr->setRank(thePtData.front_rank);
          titr->setChargeValidPacked(thePtData.charge_valid_front);
	    }
        else
        {
          titr->setRank(thePtData.rear_rank);
          titr->setChargeValidPacked(thePtData.charge_valid_rear);
        }
    }
  } //end of if(run_core)

  l1_tracks = tftks;


    // Add-on for singles:
    CSCTriggerContainer<csctf::TrackStub> myStubContainer[7]; //[BX]
    // Loop over CSC LCTs if triggering on them:
    if( trigger_on_ME1a || trigger_on_ME1b || trigger_on_ME2 || trigger_on_ME3 || trigger_on_ME4 || trigger_on_MB1a || trigger_on_MB1d )
        for(std::vector<csctf::TrackStub>::iterator itr=stub_vec_filtered.begin(); itr!=stub_vec_filtered.end(); itr++){
              int station = itr->station()-1;
              int subSector = CSCTriggerNumbering::triggerSubSectorFromLabels(CSCDetId(itr->getDetId().rawId()));
              int mpc = ( subSector ? subSector-1 : station+1 );
              if( (mpc==0&&trigger_on_ME1a) || (mpc==1&&trigger_on_ME1b) ||
                  (mpc==2&&trigger_on_ME2)  || (mpc==3&&trigger_on_ME3)  ||
                  (mpc==4&&trigger_on_ME4)  ||
                  (mpc==5&& ( (trigger_on_MB1a&&subSector%2==1) || (trigger_on_MB1d&&subSector%2==0) ) ) ){
                  int bx = itr->getBX() - m_minBX;
                  if( bx<0 || bx>=7 ) edm::LogWarning("CSCTFTrackBuilder::buildTracks()") << " LCT BX is out of ["<<m_minBX<<","<<m_maxBX<<") range: "<<itr->getBX();
                  else
                     if( itr->isValid() ) myStubContainer[bx].push_back(*itr);
              }
        }

    // Core's input was loaded in a relative time window BX=[0-7)
    // To relate it to time window of tracks (centred at BX=0) we introduce a shift:
    int shift = (m_maxBX + m_minBX)/2 - m_minBX;

    // Now we put tracks from singles in a certain bx
    //   if there were no tracks from the core in this endcap/sector/bx
    CSCTriggerContainer<csc::L1Track> tracksFromSingles;
    for(int bx=0; bx<7; bx++)
       if( myStubContainer[bx].get().size() ){ // VP in this bx
          bool coreTrackExists = false;
          // tracks are not ordered to be accessible by bx => loop them all
          std::vector<csc::L1Track> tracks = l1_tracks.get();
          for(std::vector<csc::L1Track>::iterator trk=tracks.begin(); trk<tracks.end(); trk++)
             if( trk->BX()         == bx-shift &&
                 trk->outputLink() == singlesTrackOutput ){
                 coreTrackExists = true;
                 break;
             }
             if( coreTrackExists == false ){
                 csc::L1TrackId trackId(m_endcap,m_sector);
                 csc::L1Track   track(trackId);
                 track.setRank(singlesTrackPt&0x1F);
                 track.setBx(bx-shift);
                 track.setPtPacked(singlesTrackPt);
                 track.setQualityPacked((singlesTrackPt&0x60)>>5);
                 track.setChargeValidPacked((singlesTrackPt&0x80)>>7);
                 track.setPtLUTAddress(11<<16);
                 //CSCCorrelatedLCTDigiCollection singles;
                 std::vector<csctf::TrackStub> stubs = myStubContainer[bx].get();
                 // Select best quality stub, and assign its eta/phi coordinates to the track
                 int qualityME=0, qualityMB=0, ME=100, MB=100;
                 std::vector<csctf::TrackStub>::const_iterator bestStub=stubs.end();
                 for(std::vector<csctf::TrackStub>::const_iterator st_iter=stubs.begin(); st_iter!=stubs.end(); st_iter++){
                     int station = st_iter->station()-1;
                     int subSector = CSCTriggerNumbering::triggerSubSectorFromLabels(CSCDetId(st_iter->getDetId().rawId()));
                     int mpc = ( subSector ? subSector-1 : station+1 );
                     // Sort MB stubs first (priority: quality OR MB1a > MB1b for the same quality)
                     if( mpc==5 && (st_iter->getQuality()>qualityMB || (st_iter->getQuality()==qualityMB&&subSector<MB)) ){
                         qualityMB = st_iter->getQuality();
                         MB        = subSector;
                         if(ME>4) bestStub = st_iter; // do not select this stub if ME already had any candidate
                     }
                     // Sort ME stubs (priority: quality OR ME1a > ME1b > ME2 > ME3 > ME4 for the same quality)
                     if( mpc<5  && (st_iter->getQuality()>qualityME || (st_iter->getQuality()==qualityME && mpc<ME)) ) {
                         qualityME = st_iter->getQuality();
                         ME        = mpc;
                         bestStub  = st_iter;
                     }
                 }
                 unsigned rescaled_phi = unsigned(24*(bestStub->phiPacked()>>5)/128.);
                 unsigned unscaled_phi =              bestStub->phiPacked()>>7       ;
				 track.setPhiPacked(rescaleSinglesPhi?rescaled_phi:unscaled_phi);
                 track.setEtaPacked((bestStub->etaPacked()>>2)&0x1f);
                 //   singles.insertDigi(CSCDetId(st_iter->getDetId().rawId()),*st_iter);
                 //tracksFromSingles.push_back(L1CSCTrack(track,singles));
                 tracksFromSingles.push_back(track);
             }
       }
	std::vector<csc::L1Track> single_tracks = tracksFromSingles.get();
    if( single_tracks.size() ) l1_tracks.push_many(single_tracks);
    // End of add-on for singles

  return (l1_tracks.get().size() > 0);
}

