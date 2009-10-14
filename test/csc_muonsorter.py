#!/usr/bin/env python
import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
		fileNames = cms.untracked.vstring(
			'file:./310/SingleMuPt2to100.root'
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
