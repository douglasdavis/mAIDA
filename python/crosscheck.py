#!/usr/bin/env python2

import sys

import ROOT
ROOT.gSystem.Load('lib/libmAIDAlib')
from ROOT import mAIDA

the_file = ROOT.TFile(sys.argv[1],'read')
the_tree = the_file.Get('finalstates')

for event in the_tree:
    print '========================================='
    print '-- leading',event.FinalState.LeadingLepton().pt()
    print '-- second ',event.FinalState.SecondLepton().pt()
    for x in event.FinalState.Leptons():
        print '-- weeeeee',x.pt()
