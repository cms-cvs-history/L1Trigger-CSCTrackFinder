#!/usr/bin/env python
import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

readFiles = cms.untracked.vstring()
process.source = cms.Source("PoolSource",
		#fileNames = cms.untracked.vstring('file:./GenSimDigiElectron.root')
		fileNames = readFiles
)

readFiles.extend( [
	'/store/mc/Summer08/BtoJpsiMuMuAODSIM/IDEAL_V9_AODSIM_v1/0000/0080278B-37C0-DD119A85-00E08179177F.root'
])

process.load("FWCore.MessageLogger.MessageLogger_cfi")

# Event Setup
##############
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FakeConditions_cff")

#from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
#GlobalTag.globaltag = ('IDEAL_V5::ALL')

# L1 Emulator
#############
process.load("Configuration.StandardSequences.SimL1Emulator_cff")


# Analysis Module Definition
############################
process.effic = cms.EDAnalyzer("SoftMuAna",
	outFile = cms.untracked.string("Outfile_Elec.root"),
	lctProducer = cms.InputTag("simCscTriggerPrimitiveDigis"),
	cscProducer = cms.InputTag('simCsctfDigis','CSC','')
)
	
process.FEVT = cms.OutputModule("PoolOutputModule",
	fileName = cms.untracked.string("DataStructure.root"),
	outputCommands = cms.untracked.vstring("keep *")
)
	
# Path Definition
#################
process.p = cms.Path(process.SimL1Emulator*process.effic)
#process.outpath = cms.EndPath(process.FEVT)
#process.p = cms.Path(process.simCscTriggerPrimitiveDigis*process.simDtTriggerPrimitiveDigis*process.simCsctfTrackDigis*process.simCsctfDigis)
