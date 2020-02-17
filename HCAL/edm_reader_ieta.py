from ROOT import *
from DataFormats.FWLite import Events, Handle
from DataFormats.HcalDetId import *
events = Events ('root://cmsxrootd.fnal.gov////store/mc/RunIIAutumn18DR/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/GEN-SIM-RAW/NZSFlatPU28to62_102X_upgrade2018_realistic_v15_ext1-v1/110000/FC39115C-B4B9-C247-A1EC-50A4C0754E62.root')

handle  = Handle ('vector<PCaloHit>')
label = ("g4SimHits:HcalHits")

for event in events:
    event.getByLabel(label, handle)
    SimHits = handle.product()
    for SimHit in SimHits:
	hid = HcalDetId(SimHit.id())
	ieta = hid.ieta()
	print ieta
