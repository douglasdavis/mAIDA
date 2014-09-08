#include "FinalStateFiller.h"
#include "VariableFiller.h"
#include "boost/program_options.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  boost::program_options::options_description desc("mAIDA");
  desc.add_options()
    ("help,h","Print help message")
    ("final-state-tree,f","flag to make final state tree, requires data-dir, out-file, and 1 of the n-leptons flags")
    ("var-tree,v","flag to make variable tree, requires in-file, out-file")
    ("data-dir,d",boost::program_options::value<std::string>(),"Directory containing ROOT files (required)")
    ("out-file,o",boost::program_options::value<std::string>(),"Output ROOT file name (required)")
    ("in-file,i", boost::program_options::value<std::string>(),"Input ROOT file name (required for var-tree)")
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
    
  }
  
  else {
    std::cout << desc << std::endl;
    return 0; 
  }
  
}
