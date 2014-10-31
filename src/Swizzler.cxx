/** @file Swizzler.cxx
 *  @brief mAIDA::Swizzler class implementation
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "Swizzler.h"
#include "Utils.h"
#include <iostream>

mAIDA::Swizzler::Swizzler(const char *fname, const char* tname)
{
  fRealChain = new TChain("physics");
  _out_file  = new TFile(fname,"RECREATE");
  _out_tree  = new TTree(tname,tname);
}

mAIDA::Swizzler::~Swizzler() {}

void mAIDA::Swizzler::Loop()
{
  InitRealChain();
  if ( fRealChain == 0 ) return;
  Long64_t nentries = fRealChain->GetEntries();

  mAIDA::FinalState FinalState;
  _out_tree->Branch("FinalState",&FinalState);
  
  std::cout << "Event: ";
  for ( auto eventid = 0; eventid < nentries; ++eventid ) {

    float SUM_lepton_pt = 0;
    float SUM_jet_pt    = 0;
    
    fRealChain->GetEntry(eventid);
    if ( eventid%10000 == 0 )
      std::cout << eventid << std::endl;

    // The following three loops zip up the vectors in the D3PD ntuple,
    // then create variables to be tied to the current zipped tuple
    // those variables are then used to fill the final state vector.
    
    for ( auto const& tup : mAIDA::zip(*el_E,*el_pt,*el_eta,*el_phi,*el_charge,
				       *el_tight,*el_Etcone20,*el_ptcone30,*el_trackz0pvunbiased) ) {
      float e_E, e_pt, e_eta, e_phi, e_charge;
      int   e_tight;
      float e_Etcone20, e_ptcone30, e_trackz0pvunbiased;
      boost::tie(e_E,e_pt,e_eta,e_phi,e_charge,e_tight,e_Etcone20,
		 e_ptcone30,e_trackz0pvunbiased) = tup;

      if ( mAIDA::good_el(e_tight,e_pt,e_eta,e_Etcone20,e_ptcone30,e_trackz0pvunbiased) ) {
	mAIDA::Lepton el;
	el.Set_pdgId(mAIDA::k_el);
	el.Set_charge(e_charge);
	el.Set_PtEtaPhiE(e_pt,
			 e_eta,
			 e_phi,
			 e_E);
	FinalState.AddLepton(el);
	SUM_lepton_pt += e_pt;
      }
    }


    for ( auto const& tup : mAIDA::zip(*mu_muid_E,*mu_muid_pt,*mu_muid_eta,*mu_muid_phi,
				       *mu_muid_charge,*mu_muid_etcone20,*mu_muid_ptcone30,
				       *mu_muid_id_z0_exPV) ) {
      float u_E, u_pt, u_eta, u_phi, u_charge;
      float u_etcone20, u_ptcone30, u_id_z0_exPV;
      boost::tie(u_E,u_pt,u_eta,u_phi,u_charge,u_etcone20,
		 u_ptcone30,u_id_z0_exPV) = tup;

      if ( mAIDA::good_mu(u_pt,u_eta,u_etcone20,u_ptcone30,u_id_z0_exPV) ) {
	mAIDA::Lepton mu;
	mu.Set_pdgId(mAIDA::k_mu);
	mu.Set_charge(u_charge);
	mu.Set_PtEtaPhiE(u_pt,
			 u_eta,
			 u_phi,
			 u_E);
	FinalState.AddLepton(mu);
	SUM_lepton_pt += u_pt;
      }
    }

    for ( auto const& tup : mAIDA::zip(*jet_AntiKt4LCTopo_pt,*jet_AntiKt4LCTopo_eta,
				       *jet_AntiKt4LCTopo_phi,*jet_AntiKt4LCTopo_E,
				       *jet_AntiKt4LCTopo_flavor_weight_MV1) ) {      
      float j_pt, j_eta, j_phi, j_E, j_MV1;
      boost::tie(j_pt,j_eta,j_phi,j_E,j_MV1) = tup;

      if ( mAIDA::good_jet(j_pt,j_eta) ) {
	mAIDA::Jet jet;
	jet.Set_PtEtaPhiE(j_pt,j_eta,j_phi,j_E);
	jet.Set_MV1(j_MV1);
	FinalState.AddJet(jet);
	SUM_jet_pt += j_pt;
      }
    }
    
    FinalState.Set_HT(SUM_jet_pt + SUM_lepton_pt);
    FinalState.Set_HT_leptons(SUM_lepton_pt);
    FinalState.Set_HT_jets(SUM_jet_pt);
    
    // set other final state private variables
    FinalState.EvaluateSelf();

    // set the MET for the event
    FinalState.Set_MET(MET_RefFinal_tightpp_sumet);
    
    if ( FinalState.Leptons().size() > 1 ) {
      _out_tree->Fill();
    }
    
    FinalState.ClearVecs();
    
  } // for all events

  // and finally write to the tree
  _out_tree->Write();
  _out_file->Close();
  std::cout << std::endl << "Done." << std::endl;
}
