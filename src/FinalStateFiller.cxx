/** @file FinalStateFiller.cxx
 *  @brief mAIDA::FinalStateFiller class implementation
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "FinalStateFiller.h"
#include "Utils.h"
#include <iostream>

mAIDA::FinalStateFiller::FinalStateFiller(const char *fname, const char* tname)
{
  fRealChain = new TChain("physics");
  _out_file = new TFile(fname,"RECREATE");
  _out_tree = new TTree(tname,tname);
}

mAIDA::FinalStateFiller::~FinalStateFiller() {}

void mAIDA::FinalStateFiller::Loop()
{
  InitRealChain();
  if ( fRealChain == 0 ) return;
  Long64_t nentries = fRealChain->GetEntries();

  mAIDA::FinalState FinalState;
  _out_tree->Branch("FinalState",&FinalState);
  
  for ( auto eventid = 0; eventid < nentries; ++eventid ) {
    
    fRealChain->GetEntry(eventid);
    if ( eventid%1000 == 0 ) std::cout << "Event: " << eventid << std::endl;

    for ( auto iel = 0; iel < el_n; ++iel ) {
      if ( mAIDA::good_el(el_pt->at(iel),el_eta->at(iel)) ) {
	mAIDA::Lepton el;
	el.Set_pdgId(mAIDA::k_el);
	el.Set_E(el_E->at(iel));
	el.Set_pt(el_pt->at(iel));
	el.Set_eta(el_eta->at(iel));
	el.Set_phi(el_phi->at(iel));
	el.Set_charge(el_charge->at(iel));
	el.Set_px(999999);
	el.Set_py(999999);
	el.Set_pz(999999);
	FinalState.AddLepton(el);
      } // if pass pt and eta cut
    } // for all electrons

    for ( auto imu = 0; imu < mu_n; ++imu ) {
      if ( mAIDA::good_mu(mu_pt->at(imu),mu_eta->at(imu)) ) {
	mAIDA::Lepton mu;
	mu.Set_pdgId(mAIDA::k_mu);
	mu.Set_E(mu_E->at(imu));
	mu.Set_pt(mu_pt->at(imu));
	mu.Set_eta(mu_eta->at(imu));
	mu.Set_phi(mu_phi->at(imu));
	mu.Set_charge(mu_charge->at(imu));
	mu.Set_px(mu_px->at(imu));
	mu.Set_py(mu_py->at(imu));
	mu.Set_pz(mu_pz->at(imu));
	FinalState.AddLepton(mu);
      } // if pass pt and eta cut
    } // for all muons

    for ( auto ijet = 0; ijet < jet_AntiKt4LCTopo_n; ++ijet ) {
      if ( mAIDA::good_jet(jet_AntiKt4LCTopo_pt->at(ijet),jet_AntiKt4LCTopo_eta->at(ijet)) ) {
	mAIDA::Jet jet;
	jet.Set_E(jet_AntiKt4LCTopo_E->at(ijet));
	jet.Set_pt(jet_AntiKt4LCTopo_pt->at(ijet));
	jet.Set_eta(jet_AntiKt4LCTopo_eta->at(ijet));
	jet.Set_phi(jet_AntiKt4LCTopo_phi->at(ijet));
	jet.Set_MV1(jet_AntiKt4LCTopo_flavor_weight_MV1->at(ijet));
	FinalState.AddJet(jet);
      }
    }

    if ( _ssdilepton ) {
      if ( ( FinalState.Leptons().size() == 2 ) &&
	   ( FinalState.Leptons().at(0).charge() + FinalState.Leptons().at(1).charge() != 0 ) ) {
	FinalState.SetInteractionType("ssdilepton");
	_out_tree->Fill();
      }
    }

    if ( _osdilepton ) {
      if ( ( FinalState.Leptons().size() == 2 ) &&
	   ( FinalState.Leptons().at(0).charge() + FinalState.Leptons().at(1).charge() == 0 ) ) {
	FinalState.SetInteractionType("osdilepton");
	_out_tree->Fill();
      }
    }

    if ( _trilepton ) {
      if ( FinalState.Leptons().size() == 3 ) {
	FinalState.SetInteractionType("trilepton");
	_out_tree->Fill();
      }
    }
    
    if ( _fourlepton ) {
      if ( FinalState.Leptons().size() == 4 ) {
	FinalState.SetInteractionType("fourlepton");
	_out_tree->Fill();
      }
    }

    FinalState.Clear();
    
  } // for all events

  _out_tree->Write();
  _out_file->Close();
  
}

