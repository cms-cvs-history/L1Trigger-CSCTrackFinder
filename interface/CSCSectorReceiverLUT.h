#ifndef L1Trigger_CSCSectorReceiverLUT_h
#define L1Trigger_CSCSectorReceiverLUT_h

/**
 * \class CSCSectorReceiverLUT
 * \author Lindsey Gray
 *
 * Provides Look Up Table information for use in the SP Core.
 * Partial port from ORCA.
 */

#include <L1Trigger/CSCTrackFinder/interface/CSCTrackFinderDataTypes.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>

class CSCSectorReceiverLUT
{
 public:

  CSCSectorReceiverLUT(int endcap, int sector, int subsector, int station, const edm::ParameterSet &pset);
  CSCSectorReceiverLUT(const CSCSectorReceiverLUT&);
  ~CSCSectorReceiverLUT();

  CSCSectorReceiverLUT& operator=(const CSCSectorReceiverLUT&);

  ///Geometry Lookup Tables

  lclphidat localPhi(int strip, int pattern, int quality, int lr) const;
  lclphidat localPhi(unsigned address) const;
  lclphidat localPhi(lclphiadd address) const;

  
  gblphidat globalPhiME(int phi_local, int wire_group, int cscid) const;
  gblphidat globalPhiME(unsigned address) const;
  gblphidat globalPhiME(gblphiadd address) const;

  /*
  gblphidat globalPhiMB(int phi_local,int wire_group, int cscid) const;
  gblphidat globalPhiMB(unsigned address) const;
  */

  gbletadat globalEtaME(int phi_bend, int phi_local, int wire_group, int cscid) const;
  gbletadat globalEtaME(unsigned address) const;
  gbletadat globalEtaME(gbletaadd address) const;

  /// Helpers
  std::string encodeFileIndex() const;

 private:
  int _endcap, _sector, _subsector, _station;

  /// Local Phi LUT 
  lclphidat calcLocalPhi(const lclphiadd& address) const;
  
  /// Global Phi LUT
  gblphidat calcGlobalPhiME(const gblphiadd& address) const;
  double getGlobalPhiValue(const unsigned& cscid, const unsigned& wire_group, const unsigned& phi_local) const;

  /// Global Eta LUT
  gbletadat calcGlobalEtaME(const gbletaadd& address) const;
  double getGlobalEtaValue(const unsigned& cscid, const unsigned& wire_group, const unsigned& phi_local) const;

  void fillLocalPhiLUT();
  
  std::string lut_path;
  bool LUTsFromFile;
  bool isBinary;

  /// Arrays for holding read in LUT information.
  /// MB LUT arrays only initialized in ME1
  void readLUTsFromFile();
  
  static bool me_lcl_phi_loaded;
  static lclphidat* me_lcl_phi;
  //gblphidat* me_global_phi, *mb_global_phi;
  gbletadat* me_global_eta;
};

#endif
