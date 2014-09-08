// TMVA
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
// mAIDA
#include "MVASigBkg.h"
// C++
#include <iostream>
#include <fstream>
#include <map>
#include <utility>
// boost
#include "boost/program_options.hpp"


int main(int argc, char *argv[])
{
  boost::program_options::options_description desc("runmva use");
  desc.add_options()
    ("signal,s",     boost::program_options::value<std::string>(),"signal file")
    ("background,b", boost::program_options::value< std::vector<std::string> >()->multitoken(), "background trees")
    ("output-name,o",boost::program_options::value<std::string>(),"output ROOT file name")
    ("var-file,v",   boost::program_options::value<std::string>(),"variable list file");
  
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc,argv,desc),vm);
  boost::program_options::notify(vm);
  
  if ( !vm.count("signal") || !vm.count("background") ||
       !vm.count("ntuple-name") || !vm.count("output-name") ) {
    std::cout << desc << std::endl;
    return 0;
  }

  if ( !vm.count("var-file") ) {
    std::cout << desc << std::endl;
    return 0;
  }
  
  // set up the signal background manager
  IMLA::mva::sigbkg sb_set;
  // add the singla from the command line arguments
  sb_set.set_sig(vm["signal"].as<std::string>(),
		 (vm["signal"].as<std::string>()).c_str(),
		 (vm["ntuple-name"].as<std::string>()).c_str(),1.0);
  
  // add all the backgrounds from the command line arguments
  for ( auto const& bkgitr : vm["background"].as< std::vector<std::string> >() )
    sb_set.add_bkg(bkgitr,bkgitr.c_str(),(vm["ntuple-name"].as<std::string>()).c_str(),1.0);
  
  // establish the TMVA output file with name from command line argument and TMVA factory
  TFile *TMVAFile        = new TFile(vm["output-name"].as<std::string>().c_str(),"RECREATE");
  TMVA::Factory *factory = new TMVA::Factory("TMVAClassification",TMVAFile,
					     "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");

  // make a map which holds the variable name as key, and a mair which is the units and variable type
  // example: name = "jets_m", units would be "MeV", type would be float, so 'F'
  // map is filled from var list file of that form in that order
  std::map<TString, std::pair<TString,char> > varsUsed;
  std::ifstream infile;
  std::string   temp_var, temp_units;
  char          temp_type;
  infile.open(vm["var-file"].as<std::string>().c_str());

  // fill the map with the contents on the confit file
  while ( infile >> temp_var >> temp_units >> temp_type ) {
    std::cout << temp_var << " " << temp_type << " " << temp_units << " " << temp_type << std::endl;
    TString ttemp_var   = temp_var;
    TString ttemp_units = temp_units;
    varsUsed[ttemp_var] = std::make_pair(ttemp_units,temp_type);
  }

  // now loop through the map to add variables to the factory
  for ( auto const& varitr : varsUsed ) {
    std::cout << varitr.first << " " << varitr.first << " " << varitr.second.first << " " << varitr.second.second << std::endl;
    factory->AddVariable(varitr.first,varitr.first,varitr.second.first,varitr.second.second);
  }
  
  // add the signal from the signal background manager set to the factory
  factory->AddSignalTree(sb_set.sig_tree(),sb_set.sig_weight());
  // use the signal background manager function to add the backgrounds to the factorhy
  sb_set.add_bkg_to_factory(factory);

  // cuts on sig/bkg variables
  TCut sig_cut = "";
  TCut bkg_cut = "";

  // now we prepare, book, train, test, and evaluate
  factory->PrepareTrainingAndTestTree(sig_cut,bkg_cut,
				      "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V");  
  
  factory->BookMethod(TMVA::Types::kBDT,"BDT",
		      "!H:!V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();

  return 0;
}
