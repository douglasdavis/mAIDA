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
  _out_file = new TFile(fname,"RECREATE");
  _out_tree = new TTree(tname,tname);
}

mAIDA::Swizzler::~Swizzler() {}

void mAIDA::Swizzler::Loop()
{
  InitRealChain();
  if ( fRealChain == 0 ) return;
  Long64_t nentries = fRealChain->GetEntries();

  mAIDA::FinalState FinalState;
  _out_tree->Branch("FinalState",&FinalState);
  
  for ( auto eventid = 0; eventid < nentries; ++eventid ) {

    FinalState.Falsify();
    
    fRealChain->GetEntry(eventid);
    if ( eventid%1000 == 0 ) std::cout << "Event: " << eventid << std::endl;

    for ( auto iel = 0; iel < el_n; ++iel ) {
      if ( mAIDA::good_el(el_tight->at(iel),el_pt->at(iel),el_eta->at(iel),
			  el_Etcone20->at(iel),el_ptcone30->at(iel),
			  el_trackz0pvunbiased->at(iel)) ) {
	mAIDA::Lepton el;
	el.Set_pdgId(mAIDA::k_el);
	el.Set_charge(el_charge->at(iel));
	el.Set_px(999999);
	el.Set_py(999999);
	el.Set_pz(999999);
	el.Set_PtEtaPhiE(el_pt->at(iel),
			 el_eta->at(iel),
			 el_phi->at(iel),
			 el_E->at(iel));
	FinalState.AddLepton(el);
      } // if pass all the cuts (see 7 TeV AIDA PRD)
    } // for all electrons

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
      } // if pass all cuts (see 7 TeV AIDA PRD)
    } // for all muons

    for ( auto ijet = 0; ijet < jet_AntiKt4LCTopo_n; ++ijet ) {
      if ( mAIDA::good_jet(jet_AntiKt4LCTopo_pt->at(ijet),jet_AntiKt4LCTopo_eta->at(ijet)) ) {
	mAIDA::Jet jet;
	jet.Set_PtEtaPhiE(jet_AntiKt4LCTopo_pt->at(ijet),
			  jet_AntiKt4LCTopo_eta->at(ijet),
			  jet_AntiKt4LCTopo_phi->at(ijet),
			  jet_AntiKt4LCTopo_E->at(ijet));
	jet.Set_MV1(jet_AntiKt4LCTopo_flavor_weight_MV1->at(ijet));
	FinalState.AddJet(jet);
      } // if pass all the cuts (see 7 TeV AIDA PRD)
    } // for all jets

    // set the MET for the event
    FinalState.Set_MET(MET_RefFinal_tightpp_sumet);
    
    // now we do some if statements so we fill the tree with only what we want
    if ( _ssdilepton ) {
      if ( ( FinalState.Leptons().size() == 2 ) &&
	   ( FinalState.Leptons().at(0).charge() + FinalState.Leptons().at(1).charge() != 0 ) ) {
	auto pdgsum = FinalState.Leptons().at(0).pdgId() + FinalState.Leptons().at(1).pdgId();
	std::cout << pdgsum << std::endl;
	if ( pdgsum == 22 ) { FinalState.Set_ee(true); }
	if ( pdgsum == 24 ) { FinalState.Set_eu(true); }
	if ( pdgsum == 26 ) { FinalState.Set_uu(true); }
	FinalState.SetInteractionType("ssdilepton");
	_out_tree->Fill();
      }
    }
    
    if ( _osdilepton ) {
      if ( ( FinalState.Leptons().size() == 2 ) &&
	   ( FinalState.Leptons().at(0).charge() + FinalState.Leptons().at(1).charge() == 0 ) ) {
	auto pdgsum = FinalState.Leptons().at(0).pdgId() + FinalState.Leptons().at(1).pdgId();
	std::cout << pdgsum << std::endl;
	if ( pdgsum == 22 ) { FinalState.Set_ee(true); }
	if ( pdgsum == 24 ) { FinalState.Set_eu(true); }
	if ( pdgsum == 26 ) { FinalState.Set_uu(true); }
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

    FinalState.ClearVecs();
    
  } // for all events

  // and finally write to the tree
  _out_tree->Write();
  _out_file->Close();
  
}
