/** @file VariableFiller.cxx
 *  @brief mAIDA::VariableFiller class implementation
 *
 *  This file really only contains the source for the Loop function
 *  which just fills the variable tree for MVA use
 *  Therefore I break the function into sections cause it's pretty dense
 *  Just remember its one function with a lot going on for determining
 *  different variables
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "VariableFiller.h"
#include "FinalState.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>

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

    float dR_ll_sl;
    float dR_lj_sj;

    float dR_avg_l;
    float dR_avg_j;
    
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

    mvavartree->Branch("dR_ll_sl",&dR_ll_sl,"dR_ll_sl/F");
    mvavartree->Branch("dR_lj_sj",&dR_lj_sj,"dR_lj_sj/F");

    mvavartree->Branch("dR_avg_l",&dR_avg_l,"dR_avg_l/F");
    mvavartree->Branch("dR_avg_j",&dR_avg_j,"dR_avg_j/F");
    
    mAIDA::FinalState *fs = new mAIDA::FinalState();
    _in_tree->SetBranchAddress("FinalState",&fs);

    // ________________________________________________________________________________
    
    // loop over each final state
    for ( auto ifs = 0; ifs < _in_tree->GetEntries(); ++ifs ) {      
      _in_tree->GetEntry(ifs);

      // first we get some easily definable variables
      // directly readable vars
      MET     = fs->MET();
      njets   = fs->Jets().size();

      // these vars need to be set to zero at the beginning
      // of each iteration because they are summed up
      njets_b = 0;
      ht      = 0;

      //________________________________________________________________________________
      
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
      // and start summing njets_b
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

      dR_ll_sl = mAIDA::get_dR(ll.phi(),sl.phi(),ll.eta(),sl.eta());
      dR_lj_sj = mAIDA::get_dR(lj.phi(),sj.phi(),lj.eta(),sj.eta());

      //________________________________________________________________________________
      
      // determine dR_avg_l using the
      // size of the lepton vector
      float dr01, dr02, dr03, dr12, dr13, dr23;
      switch ( fs->Leptons().size() ) {
      case 2:
	dR_avg_l = mAIDA::get_dR(fs->Leptons().at(0).phi(),fs->Leptons().at(1).phi(),
				 fs->Leptons().at(0).eta(),fs->Leptons().at(1).eta());
	break;
      case 3:
	dr01 = mAIDA::get_dR(fs->Leptons().at(0).phi(),fs->Leptons().at(1).phi(),
			     fs->Leptons().at(0).eta(),fs->Leptons().at(1).eta());
	dr02 = mAIDA::get_dR(fs->Leptons().at(0).phi(),fs->Leptons().at(2).phi(),
			     fs->Leptons().at(0).eta(),fs->Leptons().at(2).eta());
	dr12 = mAIDA::get_dR(fs->Leptons().at(1).phi(),fs->Leptons().at(2).phi(),
			     fs->Leptons().at(1).eta(),fs->Leptons().at(2).eta());
	dR_avg_l = (dr01+dr02+dr12)/3.0;
	break;
      case 4:
	dr01 = mAIDA::get_dR(fs->Leptons().at(0).phi(),fs->Leptons().at(1).phi(),
			     fs->Leptons().at(0).eta(),fs->Leptons().at(1).eta());
	dr02 = mAIDA::get_dR(fs->Leptons().at(0).phi(),fs->Leptons().at(2).phi(),
			     fs->Leptons().at(0).eta(),fs->Leptons().at(2).eta());
	dr03 = mAIDA::get_dR(fs->Leptons().at(0).phi(),fs->Leptons().at(3).phi(),
			     fs->Leptons().at(0).eta(),fs->Leptons().at(3).eta());
	dr12 = mAIDA::get_dR(fs->Leptons().at(1).phi(),fs->Leptons().at(2).phi(),
			     fs->Leptons().at(1).eta(),fs->Leptons().at(2).eta());
	dr13 = mAIDA::get_dR(fs->Leptons().at(1).phi(),fs->Leptons().at(3).phi(),
			     fs->Leptons().at(1).eta(),fs->Leptons().at(3).eta());
	dr23 = mAIDA::get_dR(fs->Leptons().at(2).phi(),fs->Leptons().at(3).phi(),
			     fs->Leptons().at(2).eta(),fs->Leptons().at(3).eta());
	dR_avg_l = (dr01+dr02+dr03+dr12+dr13+dr23)/6.0;
	break;
      default:
	std::cout << "bad number of leptons!" << std::endl;
	return;
	break;
      }

      if ( fs->Jets().size() == 0 ) {
	dR_avg_j = -999;
      }
      if ( fs->Jets().size() == 1 ) {
	dR_avg_j = 0;
      }
      if ( fs->Jets().size() == 2 ) {
	dR_avg_j = mAIDA::get_dR(fs->Jets().at(0).phi(),fs->Jets().at(1).phi(),
				 fs->Jets().at(0).eta(),fs->Jets().at(1).eta());
      }
      if ( fs->Jets().size() == 3 ) {
	dr01 = mAIDA::get_dR(fs->Jets().at(0).phi(),fs->Jets().at(1).phi(),
			     fs->Jets().at(0).eta(),fs->Jets().at(1).eta());
	dr02 = mAIDA::get_dR(fs->Jets().at(0).phi(),fs->Jets().at(2).phi(),
			     fs->Jets().at(0).eta(),fs->Jets().at(2).eta());
	dr12 = mAIDA::get_dR(fs->Jets().at(1).phi(),fs->Jets().at(2).phi(),
			     fs->Jets().at(1).eta(),fs->Jets().at(2).eta());
	dR_avg_j = (dr01+dr02+dr12)/3.0;
      }
      if ( fs->Jets().size() > 3 ) {
	std::vector<float> jet_dRs;
	for ( auto const j1 : fs->Jets() ) {
	  for ( auto const j2 : fs->Jets() ) {
	    if ( j1.eta() != j2.eta() ) {
	      if ( std::find(jet_dRs.begin(),jet_dRs.end(),
			     mAIDA::get_dR(j1.phi(),j2.phi(),j1.eta(),j2.eta())) != jet_dRs.end() ) {
		continue;
	      } // if the current dR is in the vector
	      else {
		jet_dRs.push_back(mAIDA::get_dR(j1.phi(),j2.phi(),j1.eta(),j2.eta()));
	      } // if the current dR is not in the vector
	    } // if j1.eta != j2.eta (trying to avoid uneeded compute time
	  } // loop over jets again
	} // loop over jets

	// now do the average dR for jets when Njets > 3
	float temp_sum = 0;
	for ( auto const dritr : jet_dRs )
	  temp_sum += dritr;
	dR_avg_j = temp_sum/(float)jet_dRs.size();
      }
      
      mvavartree->Fill();
      
    }
    
    mvavartree->Write();
    ofile->Close();
    
  }
  
}
