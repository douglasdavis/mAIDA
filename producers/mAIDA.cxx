// mAIDA
#include "Swizzler.h"
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
  // first we set up the how to handle the CL arguments
  // (google boost program options for info on this library)
  namespace bpo = boost::program_options;

  bpo::options_description desc("mAIDA");
  desc.add_options()
    ("help,h",      "Print help message")
    ("fst,f",       "flag to make final state tree (swizzle),\nrequires data-dir, out-file")
    ("var-tree,v",  "flag to make variable tree, requires in-file, out-file, and nleptons flag")
    ("mva,m",       "flag to run the mva, requires out-file, signal, blackgrounds, and a method (see below)")
    ("data-dir,d",  bpo::value<std::string>(),"Directory containing ROOT files (required for -f)")
    ("out-file,o",  bpo::value<std::string>(),"Output ROOT file name (always required)")
    ("in-file,i",   bpo::value<std::string>(),"Input ROOT file name (required for var-tree)")
    ("sig,s",       bpo::value<std::string>(),"sig ROOT file required for mva")
    ("bkgs,b",      bpo::value< std::vector<std::string> >()->multitoken(), "background ROOT files required for mva")
    ("ssdilepton",  "flag for same sign dilepton events")
    ("osdilepton",  "flag for opposite sign dilepton events")
    ("trilepton",   "flag for trilepton events")
    ("fourlepton",  "flag for fourlepton events")
    ("mva-methods", bpo::value<std::vector<std::string> >()->multitoken(),"MVA Methods to use (e.g. BDT, ANN)")
    ("wbe",         "flag to weight MVA ntuples by n-entries");
  
  bpo::variables_map vm;
  bpo::store(bpo::parse_command_line(argc,argv,desc),vm);
  bpo::notify(vm);

  // if the fst flag was used
  if ( vm.count("fst") ) {

    // make sure fst required input exists
    if ( !vm.count("data-dir") || !vm.count("out-file") ) {
      std::cout << desc << std::endl;
      return 0;
    }

    mAIDA::Swizzler swizz(vm["out-file"].as<std::string>().c_str(),"finalstates");
    std::string files = vm["data-dir"].as<std::string>() + "/*.root*";
    swizz.AddFile(files.c_str());

    swizz.Loop();
    return 0;

  } // if fst

  // if the var-tree flag was used
  else if ( vm.count("var-tree") ) {

    // make sure var-tree required input exists 
    if ( !vm.count("out-file") || !vm.count("in-file") ) {
      std::cout << desc << std::endl;
      return 0;
    }
    
    if ( !vm.count("ssdilepton") && !vm.count("osdilepton") &&
	 !vm.count("trilepton")  && !vm.count("fourlepton") ) {
      std::cout << desc << std::endl;
      return 0;
    }

    mAIDA::VariableFiller vf(vm["in-file"].as<std::string>().c_str());
    
    if ( vm.count("ssdilepton") ) vf.set_ss();
    if ( vm.count("ssdilepton") ) vf.set_os();
    if ( vm.count("trilepton")  ) vf.set_tri();
    if ( vm.count("fourlepton") ) vf.set_four();
    
    vf.Loop(vm["out-file"].as<std::string>().c_str());
    return 0;

  } // else if  var-tree

  // if the mva flag was used
  else if ( vm.count("mva") ) {

    // make sure mva required input exists 
    if ( !vm.count("out-file") || !vm.count("sig") || !vm.count("bkgs") || !vm.count("mva-methods") ) {
      std::cout << desc << std::endl;
      return 0;
    }

    // setup the sig, bkg manager
    mAIDA::MVASigBkg sb_set;
    sb_set.set_sig(vm["sig"].as<std::string>(),
		   vm["sig"].as<std::string>().c_str(),
		   "mvavartree",1.0);

    // add all the bkgs from command line arg.
    for ( auto const& ibkg : vm["bkgs"].as< std::vector<std::string> >() )
      sb_set.add_bkg(ibkg,ibkg.c_str(),"mvavartree",1.0);

    // if weight-by-entries flag
    if ( vm.count("wbe") ) sb_set.weight_by_entries();
    
    std::cout << sb_set.sig_tree()->GetEntries() << " " << sb_set.sig_weight() << " " 
	      << sb_set.sig_tree()->GetEntries()*sb_set.sig_weight() << std::endl;
    for ( auto const& sample : sb_set.bkg_trees() ) {
      std::cout << sample.second->GetEntries() << " " << sb_set.bkg_weights().at(sample.first) << " "
		<< sb_set.bkg_weights().at(sample.first)*sample.second->GetEntries() << std::endl;
    }
    
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
    // use the signal background manager function to add the bkgs to the factorhy
    sb_set.add_bkg_to_factory(factory);

    // now we prepare, book, train, test, and evaluate
    factory->PrepareTrainingAndTestTree(sig_cut,bkg_cut,
					"nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V");

    auto methods_vector = vm["mva-methods"].as<std::vector<std::string> >();

    if ( std::find(methods_vector.begin(), methods_vector.end(), "BDT") != methods_vector.end() )
      factory->BookMethod(TMVA::Types::kBDT,"BDT","NTrees=400:MaxDepth=2"); 

    if ( std::find(methods_vector.begin(), methods_vector.end(), "HMatrix") != methods_vector.end() )
      factory->BookMethod(TMVA::Types::kHMatrix,"HMatrix","H:V");

    if ( std::find(methods_vector.begin(), methods_vector.end(), "FD") != methods_vector.end() )
      factory->BookMethod(TMVA::Types::kFisher,"Fisher","H:V:Fisher:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10");

    if ( std::find(methods_vector.begin(), methods_vector.end(), "MLP") != methods_vector.end() )
      factory->BookMethod(TMVA::Types::kMLP,"MLP","H:V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:!UseRegulator");

    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    return 0;
  } // else if mva

  else {
    std::cout << desc << std::endl;
    return 0;
  }

}

////////////////////////////////
////////////////////////////////
// other book method options

// BDT
      //factory->BookMethod(TMVA::Types::kBDT,"BDT",
      //"!H:!V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");

// MLP

// FD

// HMatrix
