#!/usr/bin/env python
import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
		fileNames = cms.untracked.vstring(
			'/store/relval/CMSSW_3_5_5/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V25-v1/0006/185B139D-DC37-DF11-B027-0018F3D09708.root',
			'/store/relval/CMSSW_3_5_5/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V25-v1/0006/284ED12D-DB37-DF11-A6C4-001A92810AA6.root',
			'/store/relval/CMSSW_3_5_5/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V25-v1/0006/3221C82B-DC37-DF11-8D28-001A928116B8.root',
			'/store/relval/CMSSW_3_5_5/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V25-v1/0006/3C16119A-DA37-DF11-8638-003048679168.root',
			'/store/relval/CMSSW_3_5_5/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V25-v1/0006/60B7A69B-DD37-DF11-9F1F-001A92971B68.root',
			'/store/relval/CMSSW_3_5_5/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V25-v1/0006/6669BAAA-D537-DF11-B987-0018F3D09630.root',
			'/store/relval/CMSSW_3_5_5/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V25-v1/0006/AC7AC12D-DB37-DF11-9EAD-0018F3D096EE.root',
			'/store/relval/CMSSW_3_5_5/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V25-v1/0006/C2CE571B-DE37-DF11-8FC5-001A92971ADC.root',
			'/store/relval/CMSSW_3_5_5/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V25-v1/0006/D0D16F2F-D837-DF11-A231-0018F3D0965C.root',
			'/store/relval/CMSSW_3_5_5/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V25-v1/0006/EAE7DD2C-DD37-DF11-B782-003048678F1C.root',
			'/store/relval/CMSSW_3_5_5/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V25-v1/0006/F4168C9C-DB37-DF11-AD5A-003048679168.root'
	
			#'file:./SingleMuPtHigh_EtaOverlap.root'
	),
	#skipEvents=cms.untracked.uint32(173)
)

process.load("FWCore.MessageLogger.MessageLogger_cfi")

# Event Setup
##############
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MixingNoPileUp_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.Simulation_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'START3X_V25::All'

# L1 Emulator
#############
import L1Trigger.CSCTrackFinder.csctfTrackDigis_cfi
process.joeTrackOut = L1Trigger.CSCTrackFinder.csctfTrackDigis_cfi.csctfTrackDigis.clone()
process.joeTrackOut.SectorReceiverInput = 'simCscTriggerPrimitiveDigis:MPCSORTED'
process.joeTrackOut.DTproducer = 'simDtTriggerPrimitiveDigis'
#process.joeTrackOut.SectorProcessor.trigger_on_ME1a = True
#process.joeTrackOut.SectorProcessor.trigger_on_ME1b = True
#process.joeTrackOut.SectorProcessor.mindeta113_accp = 25
import L1Trigger.CSCTrackFinder.csctfDigis_cfi
process.joeOut = L1Trigger.CSCTrackFinder.csctfDigis_cfi.csctfDigis.clone()
process.joeOut.CSCTrackProducer = 'joeTrackOut'

# Analysis Module Definition
############################
process.effic = cms.EDAnalyzer("CSCTFEfficiencies",
	OutFile = cms.untracked.string("Validation.root")
)
	
process.FEVT = cms.OutputModule("PoolOutputModule",
	fileName = cms.untracked.string("test.root"),
	outputCommands = cms.untracked.vstring(	
		"keep *"
	)
)
	
# Path Definition
#################
process.p = cms.Path(process.joeTrackOut*process.joeOut*process.effic)
#process.p = cms.Path(process.simCscTriggerPrimitiveDigis*process.simDtTriggerPrimitiveDigis*process.simCsctfTrackDigis*process.simCsctfDigis*process.effic)
#process.p = cms.Path(process.simCscTriggerPrimitiveDigis*process.simDtTriggerPrimitiveDigis*process.simCsctfTrackDigis*process.simCsctfDigis)
#process.outpath = cms.EndPath(process.FEVT)
#process.schedule = cms.Schedule(process.p, process.outpath)
