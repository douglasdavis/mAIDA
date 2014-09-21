#!/usr/bin/env python

import ROOT
import pystyle

file_WZ = ROOT.TFile('response_WZ_ss.root','read')
tree_WZ = file_WZ.Get('response')

file_ttW = ROOT.TFile('response_ttW_ss.root','read')
tree_ttW = file_ttW.Get('response')

file_ttZ = ROOT.TFile('response_ttZ_ss.root','read')
tree_ttZ = file_ttZ.Get('response')

h2_MET_njets_WZ   = ROOT.TH2F('h2_MET_njets_WZ',  'WZ;E_{T}^{miss} [GeV];N_{jets}',    20,0,2500,8,0,8)
h2_Fisher_BDT_WZ  = ROOT.TH2F('h2_Fisher_BDT_WZ', 'WZ;Fisher Response;BDT Response', 15,-2,2,15,-.6,.6)
h2_MET_njets_ttW  = ROOT.TH2F('h2_MET_njets_ttW', 'ttW;E_{T}^{miss} [GeV];N_{jets}',   20,0,2500,8,0,8)
h2_Fisher_BDT_ttW = ROOT.TH2F('h2_Fisher_BDT_ttW','ttW;Fisher Response;BDT Response',15,-2,2,15,-.6,.6)
h2_MET_njets_ttZ  = ROOT.TH2F('h2_MET_njets_ttZ', 'ttZ;E_{T}^{miss} [GeV];N_{jets}',   20,0,2500,8,0,8)
h2_Fisher_BDT_ttZ = ROOT.TH2F('h2_Fisher_BDT_ttZ','ttZ;Fisher Response;BDT Response',15,-2,2,15,-.6,.6)

def fill_hists(tree,hist1,hist2):
    for event in tree:
        hist1.Fill(event.MET/1.0e3,event.njets_int)
        print event.njets_int
        hist2.Fill(event.Fisher_response,event.BDT_response)
    pystyle.hstyle2(hist1)
    pystyle.hstyle2(hist2)
    
fill_hists(tree_WZ,h2_MET_njets_WZ,h2_Fisher_BDT_WZ)
fill_hists(tree_ttW,h2_MET_njets_ttW,h2_Fisher_BDT_ttW)
fill_hists(tree_ttZ,h2_MET_njets_ttZ,h2_Fisher_BDT_ttZ)

c1 = ROOT.TCanvas()
h2_Fisher_BDT_WZ.Draw("lego")
c2 = ROOT.TCanvas()
h2_Fisher_BDT_ttW.Draw("lego")
c3 = ROOT.TCanvas()
h2_Fisher_BDT_ttZ.Draw("lego")

c4 = ROOT.TCanvas()
h2_MET_njets_WZ.Draw("lego")
c5 = ROOT.TCanvas()
h2_MET_njets_ttW.Draw("lego")
c6 = ROOT.TCanvas()
h2_MET_njets_ttZ.Draw("lego")

raw_input('')
