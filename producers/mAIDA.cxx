#include "FinalStateFiller.h"
#include "boost/program_options.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  boost::program_options::options_description desc("mAIDA");
  desc.add_options()
    ("help,h","Print help message")
    ("final-state-tree,fst","flag to make final state tree, requires data-dir, out-name, and 1 of the n-leptons flags")
    ("data-dir,d",boost::program_options::value<std::string>(),"Directory containing ROOT files (required)")
    ("out-name,o",boost::program_options::value<std::string>(),"Output ROOT file name (required)")
    ("ssdilepton","flag for same sign dilepton events")
    ("osdilepton","flag for opposite sign dilepton events")
    ("trilepton","flag for trilepton events")
    ("fourlepton","flag for fourlepton events");
  
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc,argv,desc),vm);
  boost::program_options::notify(vm);

  if ( vm.count("final-state-tree") ) {

    if ( !vm.count("data-dir") || !vm.count("out-name") ) {
      std::cout << desc << std::endl;
      return 0;
    }
    
    if ( !vm.count("ssdilepton") && !vm.count("osdilepton") &&
	 !vm.count("trilepton")  && !vm.count("fourlepton") ) {
      std::cout << desc << std::endl;
      return 0;
    }
    
    mAIDA::FinalStateFiller fsf(vm["out-name"].as<std::string>().c_str(),"finalstates");
    std::string files = vm["data-dir"].as<std::string>() + "/*.root";
    fsf.AddFile(files.c_str());

    if ( vm.count("trilepton")  ) fsf.Make_trilepton();
    if ( vm.count("fourlepton") ) fsf.Make_fourlepton();
    if ( vm.count("ssdilepton") ) fsf.Make_ssdilepton();
    if ( vm.count("osdilepton") ) fsf.Make_osdilepton();

    fsf.Loop();
    return 0;

  } // if final-state-tree
  
  else {
    std::cout << desc << std::endl;
    return 0; 
  }
  
}
