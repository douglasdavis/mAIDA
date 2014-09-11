#!/usr/bin/env python

import ROOT
import argparse
import pystyle

pystyle.gstyle()

parser = argparse.ArgumentParser(description='Plotting from MVA output')
parser.add_argument('-i','--in-file', help='input MVA ROOT file',        required=True)
parser.add_argument('-v','--var-file',help='variables list file to plot',required=True)
parser.add_argument('-t','--type',    help='the type of MVA used',       required=True)
args = vars(parser.parse_args())

var_file  = open(args['var_file'])
full_list = var_file.readlines()
var_list  = [v.split()[0] for v in full_list]
var_file.close()

infile = ROOT.TFile(args['in_file'])
method = args['type']
prefix = 'Method_'+method+'/'+method+'/'

sfill = 3004
bfill = 3005
sfillc = ROOT.kGreen+1
bfillc = ROOT.kAzure+2

SignalOutput     = infile.Get(prefix+'MVA_'+method+'_S')
BackgroundOutput = infile.Get(prefix+'MVA_'+method+'_B')
pystyle.hstyle(SignalOutput,sfill,sfillc)
pystyle.hstyle(BackgroundOutput,bfill,bfillc)

SignalVarsOutput     = []
BackgroundVarsOutput = []

for var in var_list:
    SignalVarsOutput.append(infile.Get(prefix+var+'__Signal'))
    BackgroundVarsOutput.append(infile.Get(prefix+var+'__Background'))
for hist in SignalVarsOutput:
    hist.SetTitle(';'+hist.GetTitle()+';Normalized')
    pystyle.hstyle(hist,sfill,sfillc)
for hist in BackgroundVarsOutput:
    hist.SetTitle(';'+hist.GetTitle()+';Normalized')
    pystyle.hstyle(hist,bfill,bfillc)
    
c_MVA = ROOT.TCanvas()
SignalOutput.Draw('hist')
BackgroundOutput.Draw('hist,same')

cs = [ROOT.TCanvas('c_'+name,'c_'+name) for name in var_list]
for i in xrange(len(cs)):
    cs[i].cd()
    SignalVarsOutput[i].Draw('hist')
    BackgroundVarsOutput[i].Draw('hist,same')

raw_input('')
