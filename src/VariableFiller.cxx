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

void mAIDA::VariableFiller::Loop()
{
  mAIDA::FinalState *fs = new FinalState();
  _in_tree->SetBranchAddress("FinalState",&fs);

  for ( auto iev = 0; iev < _in_tree->GetEntries(); ++iev ) {
    // fetch final state for current event
    _in_tree->GetEntry(iev);

    // the 0/1 flags for flavors/sgn need to be set to 0 for each iteration
    IS_EE = 0;
    IS_EU = 0;
    IS_UU = 0;
    IS_SS = 0;
    IS_OS = 0;

    IS_TRI  = 0;
    IS_FOUR = 0;

    // 0 flag for counting b-jets
    N_JETS_B = 0;
    
    // do flavoring/signing for dilepton
    if ( fs->Leptons().size() == 2 ) {
      if ( fs->chargeSum()       == 0  ) IS_OS = 1;
      if ( fabs(fs->chargeSum()) == 2  ) IS_SS = 1;
      if ( fabs(fs->pdgIdSum())  == 22 ) IS_EE = 1;
      if ( fabs(fs->pdgIdSum())  == 24 ) IS_EU = 1;
      if ( fabs(fs->pdgIdSum())  == 26 ) IS_UU = 1;
    }
    
    if ( fs->Leptons().size() == 3 ) IS_TRI  = 1;
    if ( fs->Leptons().size() == 4 ) IS_FOUR = 1;
    
    // some immediately available variables straight from final state getters
    MET        = fs->MET();
    N_JETS     = fs->Jets().size();
    HT         = fs->HT();
    HT_LEPTONS = fs->HT_leptons();
    HT_JETS    = fs->HT_jets();

    // get some physics object deltas
    DR_LL_LJ   = fs->LeadingLepton().four_vector().DeltaR(fs->LeadingJet().four_vector());
    DR_LL_SL   = fs->LeadingLepton().four_vector().DeltaR(fs->SecondLepton().four_vector());
    DPHI_LL_LJ = fs->LeadingLepton().four_vector().DeltaPhi(fs->LeadingJet().four_vector());
    DPHI_LL_SL = fs->LeadingLepton().four_vector().DeltaPhi(fs->SecondLepton().four_vector());

    // code to get number of b jets and do four vector combinations
    TLorentzVector all_leptons_4v;
    TLorentzVector all_jets_4v;
    for ( auto const &jet : fs->Jets() ) {
      all_jets_4v += jet.four_vector();
      if ( jet.MV1() > 0.7892 ) N_JETS_B++;
    }
    for ( auto const &lepton : fs->Leptons() ) {
      all_leptons_4v += lepton.four_vector();
    }

    M_JETS    = all_jets_4v.M();
    M_LEPTONS = all_leptons_4v.M();

    _out_tree->Fill();
    
  } // all events in tree

  _out_tree->Write();
  _out_file->Close();
  
} // loop function



/*







  void mAIDA::VariableFiller::Loop(const char* fname)
  {
  mAIDA::FinalState *fs = new mAIDA::FinalState();
  _in_tree->SetBranchAddress("FinalState",&fs);

  TFile *ofile      = new TFile(fname,"RECREATE");
  TTree *mvavartree = new TTree("mvavartree","mvavartree");

  int n_lep;
  
  int   is_ee;
  int   is_eu;
  int   is_uu;
  
  float MET;
  float ht;
  float ht_jets;
  int   njets;
  int   njets_b;

  float ll_pt;
  float sl_pt;
  float lj_pt;
  float sj_pt;

  float dR_ll_lj;
  float dR_sl_lj;
  float dR_ll_sl;
  float dR_lj_sj;

  float dPhi_ll_lj;
  float dPhi_sl_lj;

  float dR_avg_l;
  float dR_avg_j;

  float m_leptons;
  float m_jets;

  mvavartree->Branch("n_lep",&n_lep,"n_lep/I");
  
  mvavartree->Branch("MET",    &MET,    "MET/F");
  mvavartree->Branch("ht",     &ht,     "ht/F");
  mvavartree->Branch("ht_jets",&ht_jets,"ht_jets/F");
  mvavartree->Branch("njets",  &njets,  "njets/I");
  mvavartree->Branch("njets_b",&njets_b,"njets_b/I");

  mvavartree->Branch("ll_pt",&ll_pt,"ll_pt/F");
  mvavartree->Branch("sl_pt",&sl_pt,"sl_pt/F");
  mvavartree->Branch("lj_pt",&lj_pt,"lj_pt/F");
  mvavartree->Branch("sj_pt",&sj_pt,"sj_pt/F");

  mvavartree->Branch("dR_ll_lj",&dR_ll_lj,"dR_ll_lj/F");
  mvavartree->Branch("dR_sl_lj",&dR_sl_lj,"dR_sl_lj/F");
  mvavartree->Branch("dR_ll_sl",&dR_ll_sl,"dR_ll_sl/F");
  mvavartree->Branch("dR_lj_sj",&dR_lj_sj,"dR_lj_sj/F");

  mvavartree->Branch("dPhi_ll_lj",&dPhi_ll_lj,"dPhi_ll_lj/F");
  mvavartree->Branch("dPhi_sl_lj",&dPhi_sl_lj,"dPhi_sl_lj/F");

  mvavartree->Branch("dR_avg_l",&dR_avg_l,"dR_avg_l/F");
  mvavartree->Branch("dR_avg_j",&dR_avg_j,"dR_avg_j/F");

  mvavartree->Branch("m_leptons",&m_leptons,"m_leptons/F");
  mvavartree->Branch("m_jets",   &m_jets,   "m_jets/F");

  mvavartree->Branch("is_ee",&is_ee,"is_ee/I");
  mvavartree->Branch("is_eu",&is_eu,"is_eu/I");
  mvavartree->Branch("is_uu",&is_uu,"is_uu/I");
  
  // loop over each final state
  for ( auto ifs = 0; ifs < _in_tree->GetEntries(); ++ifs ) {      
  std::cout << fs->Leptons().size() << std::endl;
  n_lep = fs->Leptons().size();
  // these vars need to be set to zero at the beginning
  // of each iteration because they are summed up or they are 0/1 flag
  njets_b = 0;
  ht      = 0;
  ht_jets = 0;

  is_ee = 0;
  is_eu = 0;
  is_uu = 0;

  _in_tree->GetEntry(ifs);

  // first we get some easily definable variables
  // directly readable vars
  MET     = fs->MET();
  njets   = fs->Jets().size();

  // lepton flavor combinations,
  // of course only matters for dilepton
  // mva can cut on only wanted certain combinations
  // REDO THIS
        
  // declare particles to be used for
  // tree entries
  mAIDA::Lepton ll; // leading lepton
  mAIDA::Lepton sl; // second lepton
  mAIDA::Jet    lj; // leading jet
  mAIDA::Jet    sj; // second jet

  // var used to determine leading lepton/jet
  float current_max = -9999;

  // loop through all leptons for ll determination and add to ht variable
  for ( auto const& lep : fs->Leptons() ) {
  ht += lep.pt();
  if ( lep.pt() > current_max ) {
  current_max = lep.pt();
  ll = lep;
  }
  }

  // loop through all leptons again to detemine second lepton
  current_max = -9e10;
  for ( auto const& lep : fs->Leptons() ) {
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
  for ( auto const& jet : fs->Jets() ) {
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
  for ( auto const& jet : fs->Jets() ) {
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

  dR_ll_sl = ll.four_vector().DeltaR(sl.four_vector());
  dR_lj_sj = ll.four_vector().DeltaR(sj.four_vector());

  dR_ll_lj = ll.four_vector().DeltaR(lj.four_vector());
  dR_sl_lj = sl.four_vector().DeltaR(lj.four_vector());

  dPhi_ll_lj = ll.four_vector().DeltaPhi(lj.four_vector());
  dPhi_sl_lj = sl.four_vector().DeltaPhi(lj.four_vector());
      
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
  for ( auto const& j1 : fs->Jets() ) {
  for ( auto const& j2 : fs->Jets() ) {
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
  for ( auto const& dritr : jet_dRs )
  temp_sum += dritr;
  dR_avg_j = temp_sum/(float)jet_dRs.size();
  }

  // loops to calculate invariant mass of leptons and jets
  TLorentzVector all_leptons_4v;
  TLorentzVector all_jets_4v;
  for ( auto const& lep : fs->Leptons() )
  all_leptons_4v += lep.four_vector();
  for ( auto const& jet : fs->Jets() )
  all_jets_4v += jet.four_vector();
  m_leptons = all_leptons_4v.M();
  m_jets    = all_jets_4v.M();
    
  auto charge_sum = fs->Leptons().at(0).charge() + fs->Leptons().at(1).charge();
  auto pdg_sum    = fs->Leptons().at(0).pdgId()  + fs->Leptons().at(1).pdgId();
    
  if ( fs->Leptons().size() == 2 ) {
  if ( pdg_sum == 22 )
  is_ee = 1;
  if ( pdg_sum == 24 )
  is_eu = 1;
  if ( pdg_sum == 26 )
  is_uu = 1;
  }

  if ( _ss )
  if ( fs->Leptons().size() == 2 )
  if ( std::fabs(charge_sum) != 0 )
  mvavartree->Fill();
    
  if ( _os )
  if ( fs->Leptons().size() == 2 )
  if ( std::fabs(charge_sum) == 0 )
  mvavartree->Fill();
    
  if ( _tri )
  if ( fs->Leptons().size() == 3 )
  mvavartree->Fill();
    
  if ( _four )
  if ( fs->Leptons().size() == 4 )
  mvavartree->Fill();
    
  }
    
  mvavartree->Write();
  ofile->Close();
    
  }
*/
