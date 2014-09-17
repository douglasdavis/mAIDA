{
  TFile *infile = new TFile("../var_files/os/tt0_os.root.1");
  TTree *intree = (TTree*)infile->Get("mvavartree");

  float MET;
  int   njets;
  intree->SetBranchAddress("MET",  &MET);
  intree->SetBranchAddress("njets",&njets);

  TH1F *h_MET   = new TH1F("h_MET",  ";E_T^{miss} [GeV];",15,0,2e3);
  TH1I *h_njets = new TH1I("h_njets",";N_{jets};"        ,10,0,10);

  for ( int i = 0; i < intree->GetEntries(); ++i ) {
    intree->GetEntry(i);
    h_MET->Fill(MET/1e3);
    h_njets->Fill(njets);
  }

  TCanvas *c_MET = new TCanvas("c_MET","c_MET");
  h_MET->Draw();
  TCanvas *c_njets = new TCanvas("c_njets","c_njets");
  h_njets->Draw();
}
