#!/usr/bin/env python

import ROOT
import argparse
import pystyle

pystyle.gstyle()

parser = argparse.ArgumentParser(description='Plotting from MVA output')
parser.add_argument('-i','--in-file', help='input ROOT file',required=True)
args = vars(parser.parse_args())

jets_nbins = 2
jets_min   = 0
jets_max   = jets_nbins

MET_nbins  = 15
MET_min    = 1
MET_max    = 0

root_file = ROOT.TFile(args['in_file'],'read')


jets_hist   = ROOT.TH1I('jets_hist',';N_{jets};',
                        jets_nbins,jets_min,jets_max)
MET_hist    = ROOT.TH1D('MET_hist',';E_T^{#text{miss}}',
                        MET_nbins,MET_min,MET_max)
phase_space = ROOT.TH2D('phase_space',';MET;N_{jets}',
                        MET_nbins, MET_min, MET_max,
                        jets_nbins,0,jets_nbins)

if jets_nbins == 2:
    for event in root_file.Get('mvavartree'):
        if event.njets > 1:
            phase_space.Fill(event.MET/1e3,1)
            jets_hist.Fill(1)
        if event.njets == 1 or event.njets == 0:
            phase_space.Fill(event.MET/1e3,0)
            jets_hist.Fill(0)
        MET_hist.Fill(event.MET/1e3)
else:
    for event in root_file.Get('mvavartree'):
        phase_space.Fill(event.MET/1e3,event.njets)
        jets_hist.Fill(event.njets)
        MET_hist.Fill(event.MET/1e3)
    
c_ps = ROOT.TCanvas('c_ps','c_ps')
phase_space.Draw('lego')
c_j  = ROOT.TCanvas('c_j','c_j')
jets_hist.Draw()
c_M  = ROOT.TCanvas('c_M','c_M')
MET_hist.Draw()

raw_input('')
