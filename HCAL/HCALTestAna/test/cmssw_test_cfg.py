import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras
process = cms.Process("Test", eras.Run2_2018)

# geometry
process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

# global tag
globalTag = '102X_upgrade2018_realistic_v15'
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = globalTag

# source
process.source = cms.Source(
    "PoolSource",
    fileNames  = cms.untracked.vstring( "/store/mc/RunIIAutumn18DR/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/GEN-SIM-RAW/NZSFlatPU28to62_102X_upgrade2018_realistic_v15_ext1-v1/110000/FC39115C-B4B9-C247-A1EC-50A4C0754E62.root" ),
    )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

process.myAna = cms.EDAnalyzer("HCALTestAna")

process.path = cms.Path(process.myAna)
