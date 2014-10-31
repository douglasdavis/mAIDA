import ROOT
ROOT.gSystem.Load('lib/libmAIDAlib')
from ROOT import mAIDA

file1 = ROOT.TFile('WUT.root','read')
file2 = ROOT.TFile('WEE.root','read')

tree1 = file1.Get('finalstates')
tree2 = file2.Get('finalstates')

list1 = [x.FinalState.Leptons().at(1).pt() for x in tree1]
list2 = [x.FinalState.Leptons().at(1).pt() for x in tree2]

for n,m in zip(list1,list2):
    print n,'\t',m,'\t',n-m
