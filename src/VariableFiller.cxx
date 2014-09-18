/** @file VariableFiller.cxx
 *  @brief mAIDA::VariableFiller class implementation
 *
 *  This file really only contains the source for the Loop function
 *  which just fills the variable tree for MVA use
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "VariableFiller.h"
#include "FinalState.h"
#include <iostream>
#include <algorithm>

void mAIDA::VariableFiller::Loop(const char* fname)
{
  TFile *ofile      = new TFile(fname,"RECREATE");
  TTree *mvavartree = new TTree("mvavartree","mvavartree");

  float MET;
  float ht;
  float ht_jets;
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

  float m_leptons;
  float m_jets;
    
  mvavartree->Branch("MET",    &MET,    "MET/F");
  mvavartree->Branch("ht",     &ht,     "ht/F");
  mvavartree->Branch("ht_jets",&ht_jets,"ht_jets/F");
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

  mvavartree->Branch("m_leptons",&m_leptons,"m_leptons/F");
  mvavartree->Branch("m_jets",   &m_jets,   "m_jets/F");
    
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
    ht_jets = 0;
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
    for ( const auto& lep : fs->Leptons() ) {
      ht += lep.pt();
      if ( lep.pt() > current_max ) {
	current_max = lep.pt();
	ll = lep;
      }
    }

    // loop through all leptons again to detemine second lepton
    current_max = -9e10;
    for ( const auto& lep : fs->Leptons() ) {
      if ( ( lep.pt() > current_max ) && ( lep.pt() < ll.pt() ) ) {
	current_max = lep.pt();
	sl = lep;
      }
    }

    // if no jets set all the leading jet vars to lame shit
    if ( fs->Jets().size() == 0 ) {
      ht_jets = 0;
      continue;
    }

    // if only 1 jet set leading jet/second jet to same thing
    if ( fs->Jets().size() == 1 ) {
      lj = fs->Jets().at(0);
      sj = fs->Jets().at(0);
    }
	
    // loop through all jets for lj determination and add to ht variable
    // and start summing njets_b
    current_max = -9e10;
    for ( const auto& jet : fs->Jets() ) {
      float temp_m = jet.four_vector().M();
      ht_jets += std::sqrt(temp_m*temp_m + jet.pt()*jet.pt()); // sqrt(pT^2 + m^2)
      ht      += jet.pt();
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
    for ( const auto& jet : fs->Jets() ) {
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

    dR_ll_sl = ll.four_vector().DeltaR(sl.four_vector());
    dR_lj_sj = ll.four_vector().DeltaR(sj.four_vector());
      
    //________________________________________________________________________________
      
    // determine dR_avg_l using the
    // size of the lepton vector
    float dr01, dr02, dr03, dr12, dr13, dr23;
    switch ( fs->Leptons().size() ) {
    case 2:
      dR_avg_l = fs->Leptons().at(0).four_vector().DeltaR(fs->Leptons().at(1).four_vector());
      break;
    case 3:
      dr01 = fs->Leptons().at(0).four_vector().DeltaR(fs->Leptons().at(1).four_vector());
      dr02 = fs->Leptons().at(0).four_vector().DeltaR(fs->Leptons().at(2).four_vector());
      dr12 = fs->Leptons().at(1).four_vector().DeltaR(fs->Leptons().at(2).four_vector());
      dR_avg_l = (dr01+dr02+dr12)/3.0;
      break;
    case 4:
      dr01 = fs->Leptons().at(0).four_vector().DeltaR(fs->Leptons().at(1).four_vector());
      dr02 = fs->Leptons().at(0).four_vector().DeltaR(fs->Leptons().at(2).four_vector());
      dr03 = fs->Leptons().at(0).four_vector().DeltaR(fs->Leptons().at(3).four_vector());
      dr12 = fs->Leptons().at(1).four_vector().DeltaR(fs->Leptons().at(2).four_vector());
      dr13 = fs->Leptons().at(1).four_vector().DeltaR(fs->Leptons().at(3).four_vector());
      dr23 = fs->Leptons().at(2).four_vector().DeltaR(fs->Leptons().at(3).four_vector());
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
      dR_avg_j = fs->Jets().at(0).four_vector().DeltaR(fs->Jets().at(1).four_vector());
    }
    if ( fs->Jets().size() == 3 ) {
      dr01 = fs->Jets().at(0).four_vector().DeltaR(fs->Jets().at(1).four_vector());
      dr02 = fs->Jets().at(0).four_vector().DeltaR(fs->Jets().at(2).four_vector());
      dr12 = fs->Jets().at(1).four_vector().DeltaR(fs->Jets().at(2).four_vector());
      dR_avg_j = (dr01+dr02+dr12)/3.0;
    }
    if ( fs->Jets().size() > 3 ) {
      std::vector<float> jet_dRs;
      for ( const auto& j1 : fs->Jets() ) {
	for ( const auto& j2 : fs->Jets() ) {
	  if ( j1.eta() != j2.eta() ) {
	    if ( std::find(jet_dRs.begin(),jet_dRs.end(),
			   j1.four_vector().DeltaR(j2.four_vector())) != jet_dRs.end() ) {
	      continue;
	    } // if the current dR is in the vector
	    else {
	      jet_dRs.push_back(j1.four_vector().DeltaR(j2.four_vector()));
	    } // if the current dR is not in the vector
	  } // if j1.eta != j2.eta (trying to avoid uneeded compute time
	} // loop over jets again
      } // loop over jets

	// now do the average dR for jets when Njets > 3
      float temp_sum = 0;
      for ( const auto& dritr : jet_dRs )
	temp_sum += dritr;
      dR_avg_j = temp_sum/(float)jet_dRs.size();
    }

    // loops to calculate invariant mass of leptons and jets
    TLorentzVector all_leptons_4v;
    TLorentzVector all_jets_4v;
    for ( const auto& lep : fs->Leptons() )
      all_leptons_4v += lep.four_vector();
    for ( const auto& jet : fs->Jets() )
      all_jets_4v += jet.four_vector();
    m_leptons = all_leptons_4v.M();
    m_jets    = all_jets_4v.M();
      
    mvavartree->Fill();
      
  }
    
  mvavartree->Write();
  ofile->Close();
    
}
