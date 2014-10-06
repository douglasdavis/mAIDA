#include "TMVA/Reader.h"
#include "TMVA/Tools.h"
#include "TTree.h"
#include "TFile.h"
#include "boost/program_options.hpp"

int main(int argc, char *argv[])
{
  boost::program_options::options_description desc("mAIDA");
  desc.add_options()
    ("help,h",             "Print help message")
    ("in-file,i",          boost::program_options::value<std::string>(),"Input ROOT file name")
    ("out-file,o",         boost::program_options::value<std::string>(),"Output ROOT file name");
  
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc,argv,desc),vm);
  boost::program_options::notify(vm);

  if ( !vm.count("in-file") || !vm.count("out-file") ) {
    std::cout << desc << std::endl;
    return 0;
  }

  const char *infile  = vm["in-file"].as<std::string>().c_str();
  const char *outfile = vm["out-file"].as<std::string>().c_str();
  
  TMVA::Reader *reader = new TMVA::Reader("V:Color:!Silent");
  Float_t ht_jets, ht, MET, m_jets, m_leptons;
  Float_t njets, njets_b;
  Int_t njets_int;
  Float_t dR_ll_lj, dR_sl_lj;
  Float_t dPhi_ll_lj, dPhi_sl_lj;
  
  reader->AddVariable("MET",&MET);
  reader->AddVariable("dPhi_ll_lj",&dPhi_ll_lj);
  reader->AddVariable("dPhi_sl_lj",&dPhi_sl_lj);
  reader->AddVariable("dR_ll_lj",&dR_ll_lj);
  reader->AddVariable("dR_sl_lj",&dR_sl_lj);
  reader->AddVariable("ht",&ht);
  reader->AddVariable("ht_jets",&ht_jets);
  reader->AddVariable("m_jets",&m_jets);
  reader->AddVariable("m_leptons",&m_leptons);
  reader->AddVariable("njets",&njets);
  reader->AddVariable("njets_b",&njets_b);

  reader->BookMVA("BDT method","weights/TMVAClassification_BDT.weights.xml");
  reader->BookMVA("Fisher method","weights/TMVAClassification_Fisher.weights.xml");
  reader->BookMVA("MLP method","weights/TMVAClassification_MLP.weights.xml");
  reader->BookMVA("HMatrix method","weights/TMVAClassification_HMatrix.weights.xml");
  
  TFile *file = new TFile(infile);
  TTree *tree = (TTree*)file->Get("mvavartree");

  Int_t user_njets, user_njets_b;
  tree->SetBranchAddress("MET",&MET);
  tree->SetBranchAddress("ht",&ht);
  tree->SetBranchAddress("ht_jets",&ht_jets);
  tree->SetBranchAddress("m_jets",&m_jets);
  tree->SetBranchAddress("m_leptons",&m_leptons);
  tree->SetBranchAddress("njets",&user_njets);
  tree->SetBranchAddress("njets_b",&user_njets_b);
  tree->SetBranchAddress("dPhi_ll_lj",&dPhi_ll_lj);
  tree->SetBranchAddress("dPhi_sl_lj",&dPhi_sl_lj);
  tree->SetBranchAddress("dR_ll_lj",&dR_ll_lj);
  tree->SetBranchAddress("dR_sl_lj",&dR_sl_lj);

  TFile *out_file = new TFile(outfile,"RECREATE");
  TTree *out_tree = new TTree("response","response");
  
  Float_t BDT_response;
  Float_t Fisher_response;
  Float_t MLP_response;
  Float_t HMatrix_response;

  out_tree->Branch("BDT_response",&BDT_response,"BDT_response/F");
  out_tree->Branch("Fisher_response",&Fisher_response,"Fisher_response/F");
  out_tree->Branch("MLP_response",&MLP_response,"MLP_response/F");
  out_tree->Branch("HMatrix_response",&HMatrix_response,"HMatrix_response/F");
  out_tree->Branch("MET",&MET,"MET/F");
  out_tree->Branch("njets_int",&njets_int,"njets_int/I");
  out_tree->Branch("dR_ll_lj",  &dR_ll_lj,  "dR_ll_lj/F");
  out_tree->Branch("dR_sl_lj",  &dR_sl_lj,  "dR_sl_lj/F");
  out_tree->Branch("dPhi_ll_lj",&dPhi_ll_lj,"dPhi_ll_lj/F");
  out_tree->Branch("dPhi_sl_lj",&dPhi_sl_lj,"dPhi_sl_lj/F");


  for ( Long64_t i = 0; i < tree->GetEntries(); ++i ) {
    tree->GetEntry(i);

    njets_int = (Int_t)user_njets;
    njets     = user_njets;
    njets_b   = user_njets_b;

    BDT_response     = reader->EvaluateMVA("BDT method");
    Fisher_response  = reader->EvaluateMVA("Fisher method");
    MLP_response     = reader->EvaluateMVA("MLP method");
    HMatrix_response = reader->EvaluateMVA("HMatrix method");
    
    out_tree->Fill();    
  }

  out_tree->Write();
  out_file->Close();

  delete reader;
}
