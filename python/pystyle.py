import ROOT
from ROOT import gStyle

def normalize_hists(sig,bkg):
    if sig.GetSumw2N() == 0:
        sig.Sumw2()
    if bkg.GetSumw2N() == 0:
        bkg.Sumw2()

    if sig.GetSumOfWeights() != 0:
        dx = (sig.GetXaxis().GetXmax() - sig.GetXaxis().GetXmin())/sig.GetNbinsX()
        sig.Scale(1.0/sig.GetSumOfWeights()/dx)
    if bkg.GetSumOfWeights() != 0:
        dx = (bkg.GetXaxis().GetXmax() - bkg.GetXaxis().GetXmin())/bkg.GetNbinsX()
        bkg.Scale(1.0/bkg.GetSumOfWeights()/dx)

def gstyle():
    ROOT.gROOT.ProcessLine('TGaxis::SetMaxDigits(3);')    
    gStyle.SetFrameBorderMode(0)
    gStyle.SetFrameFillColor(0)
    gStyle.SetCanvasBorderMode(0)
    gStyle.SetCanvasColor(0)
    gStyle.SetPadBorderMode(0)
    gStyle.SetPadColor(0)
    gStyle.SetStatColor(0)
    gStyle.SetTitleFont(22,'')
    gStyle.SetLabelFont(22,'x')
    gStyle.SetTitleFont(22,'x')
    gStyle.SetLabelFont(22,'y')
    gStyle.SetTitleFont(22,'y')
    gStyle.SetLabelFont(22,'z')
    gStyle.SetTitleFont(22,'z')
    gStyle.SetLabelSize(0.048,'x')
    gStyle.SetTitleSize(0.048,'x')
    gStyle.SetLabelSize(0.048,'y')
    gStyle.SetTitleSize(0.048,'y')
    gStyle.SetLabelSize(0.048,'z')
    gStyle.SetTitleSize(0.048,'z')
    gStyle.SetTitleSize(0.048,'')
    gStyle.SetTitleAlign(23)
    gStyle.SetTitleX(0.5)
    gStyle.SetTitleBorderSize(0)
    gStyle.SetTitleFillColor(0)
    gStyle.SetTitleStyle(0)
    gStyle.SetOptStat(0)
    gStyle.SetStatBorderSize(0)
    gStyle.SetStatFont(22)
    gStyle.SetStatFontSize(0.048)
    gStyle.SetStatY(0.9)
    gStyle.SetStatX(0.86)
    gStyle.SetLegendBorderSize(0)
    gStyle.SetLegendFillColor(0)
    gStyle.SetFuncWidth(2)
    gStyle.SetFuncColor(2)
    gStyle.SetPadTopMargin(0.08)
    gStyle.SetPadBottomMargin(0.12)
    gStyle.SetPadLeftMargin(0.12)
    gStyle.SetPadRightMargin(0.06)  
    gStyle.SetCanvasDefX(400)
    gStyle.SetCanvasDefY(20)
    gStyle.SetCanvasDefH(420)
    gStyle.SetCanvasDefW(610)
    gStyle.SetFrameBorderMode(0)
    gStyle.SetFrameLineWidth(2)
    gStyle.SetHistLineWidth(2)
    gStyle.SetTitleOffset(1.16,'y')
    gStyle.SetTitleOffset(1.20,'x')

def hstyle(hist,fill,fillc):
    hist.SetFillStyle(fill)
    hist.SetLineColor(fillc)
    hist.SetFillColor(fillc)
    