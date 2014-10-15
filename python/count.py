#!/usr/bin/env python

import ROOT
import sys

tfile = ROOT.TFile(sys.argv[1],'read')
ttree = tfile.Get('mvavartree')

ee = 0
eu = 0
uu = 0

os   = 0
ss   = 0
tri  = 0
four = 0

for ev in ttree:
    if ev.IS_EE == 1:
        ee = ee + 1
    if ev.IS_EU == 1:
        eu = eu + 1
    if ev.IS_UU == 1:
        uu = uu + 1    
    if ev.IS_OS == 1:
        os = os + 1
    if ev.IS_SS == 1:
        ss = ss + 1
    if ev.IS_TRI == 1:
        tri = tri + 1
    if ev.IS_FOUR == 1:
        four = four + 1    
        
print 'total',ttree.GetEntries()
print 'ee',ee
print 'eu',eu
print 'uu',uu
print 'sum',ee+eu+uu
print 'os',os
print 'ss',ss
print 'tri',tri
print 'four',four
