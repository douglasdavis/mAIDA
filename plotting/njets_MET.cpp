#include <iostream>
#include "TApplication.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TChain.h"

int main(int argc, char *argv[])
{
  TChain *intree = new TChain("mvavartree");
  std::string fname = argv[1];
  intree->Add(fname.c_str());

  float MET;
  int   njets;
  intree->SetBranchAddress("MET",  &MET);
  intree->SetBranchAddress("njets",&njets);

  TH1F *h_MET   = new TH1F("h_MET",  ";E_{T}^{miss} [GeV];",15,0,2e3);
  TH1I *h_njets = new TH1I("h_njets",";N_{jets};"        ,10,0,10);

  TH2F *h_ps = new TH2F("h_ps",";E_{T}^{miss};N_{jets}",
			20,0,2e3,
			10,0,10);

  for ( int i = 0; i < intree->GetEntries(); ++i ) {
    intree->GetEntry(i);
    h_MET->Fill(MET/1e3);
    h_njets->Fill(njets);
    h_ps->Fill(MET,njets);
  }

  TApplication tapp("tapp",&argc,argv);
  TCanvas *c_MET = new TCanvas("c_MET","c_MET");
  h_MET->Draw();
  TCanvas *c_njets = new TCanvas("c_njets","c_njets");
  h_njets->Draw();
  TCanvas *c_ps = new TCanvas("c_ps","c_ps");
  c_ps->Draw();
  tapp.Run();
  return 0;
}
