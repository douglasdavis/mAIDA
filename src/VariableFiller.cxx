/** @file VariableFiller.cxx
 *  @brief mAIDA::VariableFiller class implementation
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "VariableFiller.h"
#include "FinalState.h"
#include <iostream>

namespace mAIDA {

  void VariableFiller::Loop(const char* fname)
  {
    
    TFile *ofile      = new TFile(fname,"RECREATE");
    TTree *mvavartree = new TTree("mvavartree","mvavartree");

    float MET;
    float ht;
    int   njets;
    int   njets_b;

    float ll_pt;
    float sl_pt;
    float lj_pt;
    float sj_pt;

    float ll_eta;
    float sl_eta;
    float lj_eta;
    float sj_eta;

    mvavartree->Branch("ht",     &ht,     "ht/F");
    mvavartree->Branch("MET",    &MET,    "MET/F");
    mvavartree->Branch("njets",  &njets,  "njets/I");
    mvavartree->Branch("njets_b",&njets_b,"njets_b/I");

    mvavartree->Branch("ll_pt",&ll_pt,"ll_pt/F");
    mvavartree->Branch("sl_pt",&sl_pt,"sl_pt/F");
    mvavartree->Branch("lj_pt",&lj_pt,"lj_pt/F");
    mvavartree->Branch("sj_pt",&sj_pt,"sj_pt/F");
    
    mvavartree->Branch("ll_eta",&ll_eta,"ll_eta/F");
    mvavartree->Branch("sl_eta",&sl_eta,"sl_eta/F");
    mvavartree->Branch("lj_eta",&lj_eta,"lj_eta/F");
    mvavartree->Branch("sj_eta",&sj_eta,"sj_eta/F");

    mAIDA::FinalState *fs = new mAIDA::FinalState();
    _in_tree->SetBranchAddress("FinalState",&fs);

    // loop over each final state
    for ( auto ifs = 0; ifs < _in_tree->GetEntries(); ++ifs ) {
      
      _in_tree->GetEntry(ifs);

      // directly readable vars
      MET     = fs->MET();
      njets   = fs->Jets().size();

      // these vars need to be set to zero at the beginning
      // of each iteration because they are summed up
      njets_b = 0;
      ht      = 0;

      // declare particles to be used for
      // tree entries
      mAIDA::Lepton ll; // leading lepton
      mAIDA::Lepton sl; // second lepton
      mAIDA::Jet    lj; // leading jet
      mAIDA::Jet    sj; // second jet

      // var used to determine leading lepton/jet
      float current_max = -9999;

      // loop through all leptons for ll determination and add to ht variable
      for ( auto lep : fs->Leptons() ) {
	ht += lep.pt();
	if ( lep.pt() > current_max ) {
	  current_max = lep.pt();
	  ll = lep;
	}
      }

      // loop through all leptons again to detemine second lepton
      current_max = -9e10;
      for ( auto lep : fs->Leptons() ) {
	if ( ( lep.pt() > current_max ) && ( lep.pt() < ll.pt() ) ) {
	  current_max = lep.pt();
	  sl = lep;
	}
      }

      // if no jets set all the leading jet vars to lame shit
      if ( fs->Jets().size() == 0 ) {
	lj.Set_pt(-99);
	sj.Set_pt(-99);
	lj.Set_eta(-10);
	sj.Set_eta(-10);
      }

      // if only 1 jet set leading jet/second jet to same thing
      if ( fs->Jets().size() == 1 ) {
	lj.Set_eta(fs->Jets().at(0).eta());
	lj.Set_pt(fs->Jets().at(0).pt());
	sj.Set_eta(lj.eta());
	sj.Set_pt(lj.pt());
      }
	
      // loop through all jets for lj determination and add to ht variable
      current_max = -9e10;
      for ( auto jet : fs->Jets() ) {
	ht += jet.pt();
	if ( jet.MV1() > 0.7892 ) {
	  njets_b++;
	}
	if ( jet.pt() > current_max ) {
	  current_max = jet.pt();
	  lj = jet;
	}
      }

      // loop through all jets again to determine second jet
      current_max = -9e10;
      for ( auto jet : fs->Jets() ) {
	if ( ( jet.pt() > current_max ) && ( jet.pt() < lj.pt() ) ) {
	  current_max = jet.pt();
	  sj = jet;
	}
      }

      // print to let user know something bad happened (i.e. leading jet pt
      // should be greater than second jet pt)
      if ( sj.pt() > lj.pt() ) { std::cout << "BAD JET STUFF" << std::endl; }
      if ( sl.pt() > ll.pt() ) { std::cout << "BAD LEP STUFF" << std::endl; }
      
      ll_pt = ll.pt();
      sl_pt = sl.pt();
      lj_pt = lj.pt();
      sj_pt = sj.pt();

      ll_eta = ll.eta();
      sl_eta = sl.eta();
      lj_eta = lj.eta();
      sj_eta = sj.eta();

      mvavartree->Fill();
      
    }

    mvavartree->Write();
    ofile->Close();

  }
  
}
