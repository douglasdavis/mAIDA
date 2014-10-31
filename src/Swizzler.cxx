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
      std::cout << eventid;
    if ( eventid%2500  == 0 )
      std::cout << ".";

    for ( auto tup : mAIDA::zip(*el_E,*el_pt,*el_eta,*el_phi,*el_charge,
				*el_tight,*el_Etcone20,*el_ptcone30,*el_trackz0pvunbiased) ) {
      float e_E, e_pt, e_eta, e_phi, e_charge;
      int   e_tight;
      float e_Etcone20, e_ptcone30, e_trackz0pvunbiased;
      
      boost::tie(e_E,e_pt,e_eta,e_phi,e_charge,e_tight,e_Etcone20,
		 e_ptcone30,e_trackz0pvunbiased) = tup;

      if ( mAIDA::good_el(e_tight,e_pt,e_eta,
			  e_Etcone20,e_ptcone30,
			  e_trackz0pvunbiased) ) {
      
	mAIDA::Lepton el;
	el.Set_pdgId(mAIDA::k_el);
	el.Set_charge(e_charge);
	el.Set_px(999999);
	el.Set_py(999999);
	el.Set_pz(999999);
	el.Set_PtEtaPhiE(e_pt,
			 e_eta,
			 e_phi,
			 e_E);
	FinalState.AddLepton(el);
	SUM_lepton_pt += e_pt;
      }
    }

    /*
    for ( auto tup : mAIDA::zip(*mu_muid_E,*mu_muid_pt,*mu_muid_eta,*mu_muid_phi,*mu_muid_charge,
				*mu_muid_etcone20,*mu_muid_ptcone30,*mu_muid_id_z0_exPV,
				*mu_muid_px,*mu_muid_py,*mu_muid_pz) ) {
      float u_E, u_pt, u_eta, u_phi, u_charge;
      float u_etcone20, u_ptcone30, u_id_z0_exPV;
      float u_px, u_py, u_pz;
      
      boost::tie(u_E,u_pt,u_eta,u_phi,u_charge,u_etcone20,
		 u_ptcone30,u_id_z0_exPV,
		 u_px,u_py,u_pz) = tup;

      if ( mAIDA::good_mu(u_pt,u_eta,
			  u_etcone20,u_ptcone30,
			  u_id_z0_exPV) ) {
      
	mAIDA::Lepton mu;
	mu.Set_pdgId(mAIDA::k_mu);
	mu.Set_charge(u_charge);
	mu.Set_px(u_px);
	mu.Set_py(u_py);
	mu.Set_pz(u_pz);
	mu.Set_PtEtaPhiE(u_pt,
			 u_eta,
			 u_phi,
			 u_E);
	FinalState.AddLepton(mu);
	SUM_lepton_pt += u_pt;
      }
    }
    */

    /*
    for ( auto imu = 0; imu < mu_muid_n; ++imu ) {
      if ( mAIDA::good_mu(mu_muid_pt->at(imu),mu_muid_eta->at(imu),
			  mu_muid_etcone20->at(imu),mu_muid_ptcone30->at(imu),
			  mu_muid_id_z0_exPV->at(imu)) ) {
	mAIDA::Lepton mu;
	mu.Set_pdgId(mAIDA::k_mu);
	mu.Set_charge(mu_muid_charge->at(imu));
	mu.Set_px(mu_muid_px->at(imu));
	mu.Set_py(mu_muid_py->at(imu));
	mu.Set_pz(mu_muid_pz->at(imu));
	mu.Set_PtEtaPhiE(mu_muid_pt->at(imu),
			 mu_muid_eta->at(imu),
			 mu_muid_phi->at(imu),
			 mu_muid_E->at(imu));
	FinalState.AddLepton(mu);
	SUM_lepton_pt += mu_muid_pt->at(imu);
      } // if pass all cuts (see 7 TeV AIDA PRD)
    } // for all muons
    */


    for ( auto tup : mAIDA::zip(*jet_AntiKt4LCTopo_pt,*jet_AntiKt4LCTopo_eta,
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
    
    /*
    for ( auto ijet = 0; ijet < jet_AntiKt4LCTopo_n; ++ijet ) {
      if ( mAIDA::good_jet(jet_AntiKt4LCTopo_pt->at(ijet),jet_AntiKt4LCTopo_eta->at(ijet)) ) {
	mAIDA::Jet jet;
	jet.Set_PtEtaPhiE(jet_AntiKt4LCTopo_pt->at(ijet),
			  jet_AntiKt4LCTopo_eta->at(ijet),
			  jet_AntiKt4LCTopo_phi->at(ijet),
			  jet_AntiKt4LCTopo_E->at(ijet));
	jet.Set_MV1(jet_AntiKt4LCTopo_flavor_weight_MV1->at(ijet));
	FinalState.AddJet(jet);
	SUM_jet_pt += jet_AntiKt4LCTopo_pt->at(ijet);
      } // if pass all the cuts (see 7 TeV AIDA PRD)
    } // for all jets
    */
    
    FinalState.Set_HT(SUM_jet_pt + SUM_lepton_pt);
    FinalState.Set_HT_leptons(SUM_lepton_pt);
    FinalState.Set_HT_jets(SUM_jet_pt);
    
    // set other final state private variables
    FinalState.EvaluateSelf();

    // set the MET for the event
    FinalState.Set_MET(MET_RefFinal_tightpp_sumet);
    
    if ( FinalState.Leptons().size() > 1 ) {
      //      std::cout << FinalState.Leptons().size() << std::endl;
      _out_tree->Fill();
    }
    
    FinalState.ClearVecs();
    
  } // for all events

  // and finally write to the tree
  _out_tree->Write();
  _out_file->Close();
  std::cout << std::endl << "Done." << std::endl;
}
