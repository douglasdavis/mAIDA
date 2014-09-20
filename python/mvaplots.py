#!/usr/bin/env python

import ROOT
import argparse
import pystyle

pystyle.gstyle()

parser = argparse.ArgumentParser(description='Plotting from MVA output')
parser.add_argument('-i','--in-file', help='input MVA ROOT file',        required=True)
parser.add_argument('-v','--var-file',help='variables list file to plot',required=True)
parser.add_argument('-m','--method',  help='the MVA method used',        required=True)
args = vars(parser.parse_args())

var_file  = open(args['var_file'])
full_list = var_file.readlines()
var_list  = [v.split()[0] for v in full_list]
var_file.close()

infile = ROOT.TFile(args['in_file'])
method = args['method']
prefix = 'Method_'+method+'/'+method+'/'

sfill  = 1001
bfill  = 3254
sfillc = ROOT.TColor.GetColor('#7d99d1')
bfillc = ROOT.TColor.GetColor('#ff0000')
slinec = ROOT.TColor.GetColor('#0000ee')
blinec = ROOT.TColor.GetColor('#ff0000')

bfillc = ROOT.kGray+2
blinec = ROOT.kGray+2

SignalTrain      = infile.Get(prefix+'MVA_'+method+'_Train_S')
BackgroundTrain  = infile.Get(prefix+'MVA_'+method+'_Train_B')
pystyle.normalize_hists(SignalTrain,BackgroundTrain)
pystyle.hstyle(SignalTrain,sfill,sfillc,slinec)
pystyle.hstyle(BackgroundTrain,bfill,bfillc,blinec)

SignalOutput     = infile.Get(prefix+'MVA_'+method+'_S')
BackgroundOutput = infile.Get(prefix+'MVA_'+method+'_B')
SignalOutput.SetTitle(';'+method+' Output;')
BackgroundOutput.SetTitle(';'+method+' Output;')
pystyle.normalize_hists(SignalOutput,BackgroundOutput)
pystyle.hstyle(SignalOutput,sfill,sfillc,slinec)
pystyle.hstyle(BackgroundOutput,bfill,bfillc,blinec)

SignalVarsOutput     = []
BackgroundVarsOutput = []

for var in var_list:
    SignalVarsOutput.append(infile.Get(prefix+var+'__Signal'))
    BackgroundVarsOutput.append(infile.Get(prefix+var+'__Background'))

for hist in SignalVarsOutput:
    hist.SetTitle(';'+hist.GetTitle()+';Normalized')
    pystyle.hstyle(hist,sfill,sfillc,slinec)

for hist in BackgroundVarsOutput:
    hist.SetTitle(';'+hist.GetTitle()+';Normalized')
    pystyle.hstyle(hist,bfill,bfillc,blinec)

R_legend = pystyle.right_legend(SignalOutput,BackgroundOutput,'f')
L_legend = pystyle.left_legend(SignalTrain,BackgroundTrain,'lep')

c_MVA = ROOT.TCanvas('c_MVA','c_MVA')
SignalOutput.Draw('hist')
BackgroundOutput.Draw('hist,same')
R_legend.Draw('same')

c_MVA_train = ROOT.TCanvas('c_MVA_train','c_MVA_train')
SignalOutput.Draw('hist')
BackgroundOutput.Draw('hist,same')
SignalTrain.Draw('e1same')
BackgroundTrain.Draw('e1same')
R_legend.Draw('same')
L_legend.Draw('same')

c_MVA_train.SaveAs('c_MVA_train'+method+'.eps')

cs = [ROOT.TCanvas('c_'+name,'c_'+name) for name in var_list]
for i in xrange(len(cs)):
    cs[i].cd()
    pystyle.normalize_hists(SignalVarsOutput[i],BackgroundVarsOutput[i])
    SignalVarsOutput[i].Draw('hist')
    BackgroundVarsOutput[i].Draw('hist,same')
    #cs[i].SaveAs('c_'+var_list[i]+'.eps')
    
raw_input('')
