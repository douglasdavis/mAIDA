#!/usr/bin/env python

import ROOT
import sys

tfile = ROOT.TFile(sys.argv[1],'read')
ttree = tfile.Get('mvavartree')

ee=0
eu=0
uu=0

for ev in ttree:
    if ev.is_ee == 1:
        ee=ee+1
    if ev.is_eu == 1:
        eu=eu+1
    if ev.is_uu == 1:
        uu=uu+1    

print ee
print eu
print uu
print ee+eu+uu
print ttree.GetEntries()
