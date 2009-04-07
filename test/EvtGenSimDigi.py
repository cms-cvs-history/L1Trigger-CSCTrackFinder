#!/usr/bin/env pythonma
import FWCore.ParameterSet.Config as cms

process = cms.Process("GEN")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

# Event Setup
#############
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("Configuration.StandardSequences.MagneticField_cff")

process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FakeConditions_cff")
process.load("L1Trigger.CSCTrackFinder.PtGun_cfi")

# Module Definition for Detector Simulation
###########################################
process.load("Configuration.StandardSequences.Generator_cff")
process.load("Configuration.StandardSequences.Simulation_cff")
process.load("Configuration.StandardSequences.VtxSmearedGauss_cff")
process.load("Configuration.StandardSequences.MixingNoPileUp_cff")
#process.load("Configuration.EventContent.EventContent_cff")

from L1Trigger.Configuration.L1Trigger_EventContent_cff import *


process.FEVT = cms.OutputModule("PoolOutputModule",
	fileName = cms.untracked.string("SingleMuPt2to100.root"),
	outputCommands = cms.untracked.vstring("keep *")	
)

# Run Path Definition
#####################
process.p = cms.Path(process.pgen*process.psim*process.pdigi)
process.outpath = cms.EndPath(process.FEVT)
process.schedule = cms.Schedule(process.p,process.outpath)
