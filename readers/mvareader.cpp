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

  float  MET;
  float  N_JETS;
  float  N_JETS_B;
  float  HT;
  float  HT_LEPTONS;
  float  M_LEPTONS;
  float  M_JETS;  

  int    ft_N_JETS;
  int    ft_N_JETS_B;
  reader->AddVariable("HT",        &HT);
  reader->AddVariable("HT_LEPTONS",&HT_LEPTONS);  
  reader->AddVariable("MET",       &MET);
  reader->AddVariable("M_JETS",    &M_JETS);
  reader->AddVariable("M_LEPTONS", &M_LEPTONS);
  reader->AddVariable("N_JETS",    &N_JETS);
  reader->AddVariable("N_JETS_B",  &N_JETS_B);


  reader->BookMVA("BDT method",    "weights/TMVAClassification_BDT.weights.xml");
  reader->BookMVA("Fisher method", "weights/TMVAClassification_Fisher.weights.xml");
  reader->BookMVA("MLP method",    "weights/TMVAClassification_MLP.weights.xml");
  reader->BookMVA("HMatrix method","weights/TMVAClassification_HMatrix.weights.xml");
  
  TFile *file = new TFile(infile);
  TTree *tree = (TTree*)file->Get("mvavartree");

  tree->SetBranchAddress("MET",       &MET);
  tree->SetBranchAddress("N_JETS",    &ft_N_JETS);
  tree->SetBranchAddress("N_JETS_B",  &ft_N_JETS_B);
  tree->SetBranchAddress("HT",        &HT);
  tree->SetBranchAddress("HT_LEPTONS",&HT_LEPTONS);
  tree->SetBranchAddress("M_LEPTONS", &M_LEPTONS);
  tree->SetBranchAddress("M_JETS",    &M_JETS);

  TFile *out_file = new TFile(outfile,"RECREATE");
  TTree *out_tree = new TTree("response","response");
  
  Float_t BDT_response;
  Float_t Fisher_response;
  Float_t MLP_response;
  Float_t HMatrix_response;

  out_tree->Branch("BDT_response",    &BDT_response,    "BDT_response/F");
  out_tree->Branch("Fisher_response", &Fisher_response, "Fisher_response/F");
  out_tree->Branch("MLP_response",    &MLP_response,    "MLP_response/F");
  out_tree->Branch("HMatrix_response",&HMatrix_response,"HMatrix_response/F");

  out_tree->Branch("MET",       &MET,        "MET/F");
  out_tree->Branch("N_JETS",    &ft_N_JETS,  "N_JETS/I");
  out_tree->Branch("N_JETS_B",  &ft_N_JETS_B,"N_JETS_B/I");
  out_tree->Branch("HT",        &HT,         "HT/F");
  out_tree->Branch("HT_LEPTONS",&HT_LEPTONS, "HT_LEPTONS/F");
  out_tree->Branch("M_LEPTONS", &M_LEPTONS,  "M_LEPTONS/F");
  out_tree->Branch("M_JETS",    &M_JETS,     "M_JETS/F");
  
  for ( Long64_t i = 0; i < tree->GetEntries(); ++i ) {
    tree->GetEntry(i);
    
    N_JETS    = ft_N_JETS;
    N_JETS_B  = ft_N_JETS_B;

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
