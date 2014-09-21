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
    sb = 1.3
    ss = 1.3
    sig.SetMaximum(ROOT.TMath.Max(sig.GetMaximum()*ss,
                                  bkg.GetMaximum()*sb))

        
def gstyle():
    ROOT.gROOT.ProcessLine('TGaxis::SetMaxDigits(3);')    
    gStyle.SetFrameBorderMode(0)
    gStyle.SetFrameFillColor(0)
    gStyle.SetCanvasBorderMode(0)
    gStyle.SetCanvasColor(0)
    gStyle.SetPadBorderMode(0)
    gStyle.SetPadColor(0)
    gStyle.SetStatColor(0)
    gStyle.SetTitleFont(42,'')
    gStyle.SetLabelFont(42,'x')
    gStyle.SetTitleFont(42,'x')
    gStyle.SetLabelFont(42,'y')
    gStyle.SetTitleFont(42,'y')
    gStyle.SetLabelFont(42,'z')
    gStyle.SetTitleFont(42,'z')
    gStyle.SetLabelSize(0.042,'x')
    gStyle.SetTitleSize(0.048,'x')
    gStyle.SetLabelSize(0.042,'y')
    gStyle.SetTitleSize(0.048,'y')
    gStyle.SetLabelSize(0.042,'z')
    gStyle.SetTitleSize(0.048,'z')
    gStyle.SetTitleSize(0.048,'')
    gStyle.SetTitleAlign(23)
    gStyle.SetTitleX(0.5)
    gStyle.SetTitleBorderSize(0)
    gStyle.SetTitleFillColor(0)
    gStyle.SetTitleStyle(0)
    gStyle.SetOptStat(0)
    gStyle.SetStatBorderSize(0)
    gStyle.SetStatFont(42)
    gStyle.SetStatFontSize(0.042)
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

def hstyle(hist,fill,fillc,linec):
    hist.SetFillStyle(fill)
    hist.SetLineColor(linec)
    hist.SetFillColor(fillc)
    hist.SetLineWidth(2)
    hist.SetMarkerColor(linec)
    hist.SetMarkerStyle(8)
    hist.SetMarkerSize(.5)
    hist.GetXaxis().SetLabelSize(0.042)
    hist.GetXaxis().SetLabelFont(42)
    hist.GetXaxis().SetTitleSize(0.048)
    hist.GetXaxis().SetTitleFont(42)
    hist.GetYaxis().SetLabelSize(0.042)
    hist.GetYaxis().SetLabelFont(42)
    hist.GetYaxis().SetTitleSize(0.048)
    hist.GetYaxis().SetTitleFont(42)

def hstyle2(hist):
    hist.GetXaxis().SetLabelSize(0.042)
    hist.GetXaxis().SetLabelFont(42)
    hist.GetXaxis().SetTitleSize(0.048)
    hist.GetXaxis().SetTitleFont(42)
    hist.GetYaxis().SetLabelSize(0.042)
    hist.GetYaxis().SetLabelFont(42)
    hist.GetYaxis().SetTitleSize(0.048)
    hist.GetYaxis().SetTitleFont(42)
    hist.GetXaxis().SetTitleOffset(1.3)
    hist.GetYaxis().SetTitleOffset(1.3)
    
def right_legend(sig,bkg,marker):
    legend = ROOT.TLegend(.73,.80,.93,.91)
    legend.AddEntry(sig,'Signal',marker)
    legend.AddEntry(bkg,'Background',marker)
    legend.SetTextSize(0.046)
    legend.SetTextFont(42)
    legend.SetBorderSize(0)
    legend.SetFillColor(0)
    return legend

def left_legend(sig,bkg,marker):
    legend = ROOT.TLegend(.13,.80,.33,.91)
    legend.AddEntry(sig,'Signal (train)',marker)
    legend.AddEntry(bkg,'Background (train)',marker)
    legend.SetTextSize(0.046)
    legend.SetTextFont(42)
    legend.SetBorderSize(0)
    legend.SetFillColor(0)
    return legend
