#!/usr/bin/env python
import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
		fileNames = cms.untracked.vstring(#'/store/relval/CMSSW_3_1_0_pre6/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP_31X_v1/0002/4485DABF-D432-DE11-BF53-000423D94AA8.root',
																			#'/store/relval/CMSSW_3_1_0_pre6/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP_31X_v1/0002/561BF673-D032-DE11-8A92-000423D99EEE.root',
																			#'/store/relval/CMSSW_3_1_0_pre6/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP_31X_v1/0002/727D8867-1733-DE11-8270-000423D6B5C4.root',
																			#'/store/relval/CMSSW_3_1_0_pre6/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP_31X_v1/0002/8843B64C-C432-DE11-BD2C-000423D6CA6E.root',
																			#'/store/relval/CMSSW_3_1_0_pre6/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP_31X_v1/0002/BEA22895-D332-DE11-907F-000423D98B5C.root',
																			#'/store/relval/CMSSW_3_1_0_pre6/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP_31X_v1/0002/C2EBAF45-C232-DE11-928F-001617C3B5D8.root'
																			
																			'file:/data1/JOE/310/SingleMuPtHigh_EtaOverlap.root'
																			
																			#'file:./310/SingleMuPt2to100.root'
																			
																			#'file:./310/genMu_Eta1p9To2p0_Pt0p5To140_1.root'
																			
																			#'file:./genMu_Eta0p9To1p0_Pt0p5To140.root',
																			#'file:./genMu_Eta0p9To1p0_Pt0p5To140_1.root'
	)
)

process.load("FWCore.MessageLogger.MessageLogger_cfi")

# Event Setup
##############
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MixingNoPileUp_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V1::All'

# L1 Emulator
#############
process.load("Configuration.StandardSequences.Simulation_cff")
process.load("Configuration.StandardSequences.SimL1Emulator_cff")
#process.simCsctfTrackDigis.SectorProcessor.PTLUT =	cms.PSet(
#																													LowQualityFlag = cms.untracked.uint32(4),
#																													ReadPtLUT = cms.untracked.bool(True)
#																													PtLUTFile = cms.untracked.FileInPath('L1Trigger/CSCTrackFinder/test/310/LUTS/L1CSCPtLUT.bin'),
#																													isBinary = cms.untracked.bool(True),
#																													PtMethod = cms.untracked.uint32(1)
#																										)


# Analysis Module Definition
############################
process.effic = cms.EDAnalyzer("CSCTFEfficiencies",
	OutFile = cms.untracked.string("Validation.root")
)
	
process.FEVT = cms.OutputModule("PoolOutputModule",
	fileName = cms.untracked.string("test.root"),
	outputCommands = cms.untracked.vstring(	
																					"keep *"
																					#"drop *",
																					#"keep recoGenParticles_*_*_*",
																					#"keep SimTracks_*_*_*",
																					#"keep CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_*_MPCSORTED_*",
																					#"keep L1MuDTChambPhContainer_*_*_*",
																					#"keep csctfTrackStubCSCTriggerContainer_*_*_*",
																					#"keep cscL1TrackCSCDetIdCSCCorrelatedLCTDigiMuonDigiCollectionstdpairs_*_*_*"
																				)
)
	
# Path Definition
#################
#process.p = cms.Path(process.effic)
process.p = cms.Path(process.simCscTriggerPrimitiveDigis*process.simDtTriggerPrimitiveDigis*process.simCsctfTrackDigis*process.simCsctfDigis*process.effic)
#process.p = cms.Path(process.simCscTriggerPrimitiveDigis*process.simDtTriggerPrimitiveDigis*process.simCsctfTrackDigis*process.simCsctfDigis)
#process.outpath = cms.EndPath(process.FEVT)
#process.schedule = cms.Schedule(process.p, process.outpath)
