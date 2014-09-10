// mAIDA
#include "FinalStateFiller.h"
#include "VariableFiller.h"
#include "MVASigBkg.h"
// Boost
#include "boost/program_options.hpp"
// C/C++
#include <iostream>
#include <string>
#include <fstream>
// TMVA
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"

int main(int argc, char *argv[])
{
  boost::program_options::options_description desc("mAIDA");
  desc.add_options()
    ("help,h","Print help message")
    ("final-state-tree,f","flag to make final state tree, requires data-dir, out-file, and 1 of the n-leptons flags")
    ("var-tree,v","flag to make variable tree, requires in-file, out-file")
    ("mva,m","flag to run the mva, requires out-file, signal, blackgrounds")
    ("data-dir,d",boost::program_options::value<std::string>(),"Directory containing ROOT files (required for -f)")
    ("out-file,o",boost::program_options::value<std::string>(),"Output ROOT file name (always required)")
    ("in-file,i", boost::program_options::value<std::string>(),"Input ROOT file name (required for var-tree)")
    ("signal,s",boost::program_options::value<std::string>(),"signal ROOT file required for mva")
    ("backgrounds,b", boost::program_options::value< std::vector<std::string> >()->multitoken(), "background ROOT files required for mva")
    ("ssdilepton","flag for same sign dilepton events")
    ("osdilepton","flag for opposite sign dilepton events")
    ("trilepton", "flag for trilepton events")
    ("fourlepton","flag for fourlepton events");
  
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc,argv,desc),vm);
  boost::program_options::notify(vm);

  if ( vm.count("final-state-tree") ) {

    if ( !vm.count("data-dir") || !vm.count("out-file") ) {
      std::cout << desc << std::endl;
      return 0;
    }
    
    if ( !vm.count("ssdilepton") && !vm.count("osdilepton") &&
	 !vm.count("trilepton")  && !vm.count("fourlepton") ) {
      std::cout << desc << std::endl;
      return 0;
    }
    
    mAIDA::FinalStateFiller fsf(vm["out-file"].as<std::string>().c_str(),"finalstates");
    std::string files = vm["data-dir"].as<std::string>() + "/*.root";
    fsf.AddFile(files.c_str());

    if ( vm.count("trilepton")  ) fsf.Make_trilepton();
    if ( vm.count("fourlepton") ) fsf.Make_fourlepton();
    if ( vm.count("ssdilepton") ) fsf.Make_ssdilepton();
    if ( vm.count("osdilepton") ) fsf.Make_osdilepton();

    fsf.Loop();
    return 0;

  } // if final-state-tree

  else if ( vm.count("var-tree") ) {

    if ( !vm.count("out-file") || !vm.count("in-file") ) {
      std::cout << desc << std::endl;
      return 0;
    }

    mAIDA::VariableFiller vf(vm["in-file"].as<std::string>().c_str());
    vf.Loop(vm["out-file"].as<std::string>().c_str());
    return 0;
    
  } // else if  var-tree

  else if ( vm.count("mva") ) {

    if ( !vm.count("out-file") || !vm.count("signal") || !vm.count("backgrounds") ) {
      std::cout << desc << std::endl;
      return 0;
    }
    
    // setup the sig, bkg manager
    mAIDA::MVASigBkg sb_set;
    sb_set.set_sig(vm["signal"].as<std::string>(),
		   vm["signal"].as<std::string>().c_str(),
		   "mvavartree",1.0);

    // add all the backgrounds from command line arg.
    for ( auto const& ibkg : vm["backgrounds"].as< std::vector<std::string> >() )
      sb_set.add_bkg(ibkg,ibkg.c_str(),"mvavartree",1.0);

    TFile *TMVAFile        = new TFile(vm["out-file"].as<std::string>().c_str(),"RECREATE");
    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification",TMVAFile,
					       "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");

    // make a map which holds the variable name as key, and a mair which is the units and variable type
    // example: name = "ht", units would be "MeV", type would be float, so 'F'
    // map is filled from var list file of that form in that order
    std::map<TString, std::pair<TString,char> > varsUsed;
    std::ifstream infile;
    std::string   temp_var, temp_units;
    char          temp_type;
    infile.open("config/mvalist.txt");
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
    infile.open("config/mvacuts.txt");
    while ( infile >> sc1 >> sc2 )
      cuts[sc1] = sc2;
    std::cout << "Cuts: " << std::endl;
    for ( auto itr : cuts )
      std::cout << itr.first << " " << itr.second << std::endl;
    TCut sig_cut(cuts.at("sig").c_str());
    TCut bkg_cut(cuts.at("bkg").c_str());
    
    // add the signal from the signal background manager set to the factory
    factory->AddSignalTree(sb_set.sig_tree(),sb_set.sig_weight());
    // use the signal background manager function to add the backgrounds to the factorhy
    sb_set.add_bkg_to_factory(factory);

    // now we prepare, book, train, test, and evaluate
    factory->PrepareTrainingAndTestTree(sig_cut,bkg_cut,
					"nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V");  
  
    factory->BookMethod(TMVA::Types::kBDT,"BDT",
			"!H:!V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");

    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    
  } // else if mva
  
  else {
    std::cout << desc << std::endl;
    return 0; 
  }
  
}
