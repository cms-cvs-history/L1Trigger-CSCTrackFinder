#!/usr/bin/env python
import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.maxEvents = cms.untracked.PSet(
	input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring('file:/home/gartner/CMSSW_2_1_0_pre5/src/L1Trigger/CSCTrackFinder/test/SingleMu2to100.root')#,
	#									'/home/gartner/CMSSW_2_1_0_pre5/src/L1Trigger/CSCTrackFinder/test/SingleMu50to100.root'
		#							 )
)

process.load("FWCore.MessageLogger.MessageLogger_cfi")

# Event Setup
################
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")
process.load("CalibMuon.Configuration.DT_FakeConditions_cff")

# L1 Emulator
#############
process.load("Configuration.StandardSequences.SimL1Emulator_cff")
process.load("L1TriggerConfig.DTTPGConfigProducers.L1DTTPGConfig_cff")
process.load("L1TriggerConfig.DTTrackFinder.L1DTTrackFinderConfig_cff")
process.load("L1TriggerConfig.L1CSCTPConfigProducers.L1CSCTriggerPrimitivesConfig_cff")
process.load("L1TriggerConfig.CSCTFConfigProducers.L1CSCTFConfig_cff")
process.load("L1TriggerConfig.L1ScalesProducers.L1MuTriggerScalesConfig_cff")
process.load("L1TriggerConfig.L1ScalesProducers.L1MuTriggerPtScaleConfig_cff")

# LUT Producer
##############
process.load("L1TriggerConfig.CSCTFConfigProducers.CSCTFConfigProducer_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")


# Analysis Module Definition
############################
process.effic = cms.EDAnalyzer("CSCTFEfficiencies",
	OutFile = cms.untracked.string("Outfile.root")
)
	
	
# Path Definition
#################
process.p = cms.Path(process.simCscTriggerPrimitiveDigis*process.simDtTriggerPrimitiveDigis*process.simCsctfTrackDigis*process.simCsctfDigis*process.effic)

	
