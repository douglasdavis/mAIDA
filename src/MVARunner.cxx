#include "MVARunner.h"
#include "MVASigBkg.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"

mAIDA::MVARunner::MVARunner()
{
  _wbe = false;
}

mAIDA::MVARunner::~MVARunner() {}

void mAIDA::MVARunner::Run()
{
  std::cout << "STARTING RUN" << std::endl;
  mAIDA::MVASigBkg sb_set;
  sb_set.set_sig(_sig_file.c_str(),
		 _sig_file.c_str(),
		 "mvavartree",1.0);

  // add all the bkgs from command line arg.
  for ( auto const& ibkg : _bkg_files )
    sb_set.add_bkg(ibkg,ibkg.c_str(),"mvavartree",1.0);

  // if weight-by-entries flag
  if ( _wbe ) sb_set.weight_by_entries();

  std::cout << "MADE IT TOO WBE" << std::endl;
  
  std::cout << sb_set.sig_tree()->GetEntries() << " " << sb_set.sig_weight() << " " 
	    << sb_set.sig_tree()->GetEntries()*sb_set.sig_weight() << std::endl;
  for ( auto const& sample : sb_set.bkg_trees() ) {
    std::cout << sample.second->GetEntries() << " " << sb_set.bkg_weights().at(sample.first) << " "
	      << sb_set.bkg_weights().at(sample.first)*sample.second->GetEntries() << std::endl;
  }
    
  std::string factory_settings;
  factory_settings = "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification";

  TFile *TMVAFile        = new TFile(_out_file.c_str(),"RECREATE");
  TMVA::Factory *factory = new TMVA::Factory("TMVAClassification",TMVAFile,
					     factory_settings.c_str());

  std::cout << "MADE IT TO THE FACTORY" << std::endl;
  
  // make a map which holds the variable name as key, and a mair which is the units and variable type
  // example: name = "ht", units would be "MeV", type would be float, so 'F'
  // map is filled from var list file of that form in that order

  std::string var_list_file = _var_file;
  std::string cut_list_file = _cut_file;
  std::map<TString, std::pair<TString,char> > varsUsed;
  std::ifstream infile;
  std::string   temp_var, temp_units;
  char          temp_type;
  infile.open(var_list_file.c_str());
  // fill the map with the contents on the confit file
  while ( infile >> temp_var >> temp_units >> temp_type ) {
    std::cout << temp_var << " " << temp_type << " " << temp_units << " " << temp_type << std::endl;
    TString ttemp_var   = temp_var;
    TString ttemp_units = temp_units;
    varsUsed[ttemp_var] = std::make_pair(ttemp_units,temp_type);
  }
  infile.close();

  // now loop through the map to add variables to the factory
  for ( auto const& varitr : varsUsed ) {
    std::cout << varitr.first << " " << varitr.first << " " << varitr.second.first << " " << varitr.second.second << std::endl;
    factory->AddVariable(varitr.first,varitr.first,varitr.second.first,varitr.second.second);
  }

  // this bit sets of the cuts from the cut config file
  std::string sc1, sc2;
  std::map<std::string,std::string> cuts;
  infile.open(cut_list_file.c_str());
  while ( infile >> sc1 >> sc2 )
    cuts[sc1] = sc2;
  std::cout << "Cuts: " << std::endl;
  for ( auto itr : cuts )
    std::cout << itr.first << " " << itr.second << std::endl;
  TCut sig_cut(cuts.at("sig").c_str());
  TCut bkg_cut(cuts.at("bkg").c_str());

  // add the signal from the signal background manager set to the factory
  factory->AddSignalTree(sb_set.sig_tree(),sb_set.sig_weight());
  // use the signal background manager function to add the bkgs to the factorhy
  sb_set.add_bkg_to_factory(factory);

  // now we prepare, book, train, test, and evaluate
  std::string train_test_settings;
  train_test_settings = "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V";
  factory->PrepareTrainingAndTestTree(sig_cut,bkg_cut,
				      train_test_settings.c_str());

  std::string BDT_settings, HMatrix_settings, Fisher_settings, MLP_settings;
  BDT_settings     = "NTrees=400:MaxDepth=2";
  HMatrix_settings = "H:V";
  Fisher_settings  = "H:V:Fisher:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10";
  MLP_settings     = "H:V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:!UseRegulator";
    
  if ( std::find(_methods.begin(), _methods.end(), "BDT") != _methods.end() )
    factory->BookMethod(TMVA::Types::kBDT,"BDT",BDT_settings.c_str());

  if ( std::find(_methods.begin(), _methods.end(), "HMatrix") != _methods.end() )
    factory->BookMethod(TMVA::Types::kHMatrix,"HMatrix",HMatrix_settings.c_str());

  if ( std::find(_methods.begin(), _methods.end(), "FD") != _methods.end() )
    factory->BookMethod(TMVA::Types::kFisher,"Fisher",Fisher_settings.c_str());

  if ( std::find(_methods.begin(), _methods.end(), "MLP") != _methods.end() )
    factory->BookMethod(TMVA::Types::kMLP,"MLP",MLP_settings.c_str());

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();

}
