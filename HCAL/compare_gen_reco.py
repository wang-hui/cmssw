import ROOT as rt
import pandas as pd

result = pd.read_csv("result.csv", sep=',', header=0)
reco_h = rt.TH1F("reco_h", "reco energy", 100, 0.0, 100.0)
gen_h = rt.TH1F("gen_h", "truth energy", 100, 0.0, 100.0)
reco_vs_gen_h = rt.TH2F("reco_vs_gen_h", "reco vs gen", 100, 0.0, 100.0, 100, 0.0, 100.0)
ratio_h = rt.TH1F("ratio_h", "reco/gen for gen > 1 GeV", 100, 0.0, 2.0)

Nrows = result.shape[0]
print "total rows: ", Nrows
for i in range(Nrows):
	reco_energy = result["reco energy"][i]
	gen_energy = result["truth energy"][i]
	reco_h.Fill(reco_energy)
	gen_h.Fill(gen_energy)
	reco_vs_gen_h.Fill(reco_energy, gen_energy)
	if gen_energy > 1: ratio_h.Fill(reco_energy / gen_energy)

out_file = rt.TFile("result_test.root","RECREATE")
reco_h.Write()
gen_h.Write()
reco_vs_gen_h.Write()
ratio_h.Write()
out_file.Close()
