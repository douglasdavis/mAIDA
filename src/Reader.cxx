/** @file Reader.cxx
 *  @brief mAIDA::Reader class implementation
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "mAIDA/Reader.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

namespace mAIDA {

  Reader::Reader(TTree *tree, const char* in_file_name) : fChain(0) 
  {
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    /*
      if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(in_file_name);
      if (!f || !f->IsOpen()) {
      f = new TFile(in_file_name);
      }
      f->GetObject("physics",tree);

      }
    */
    //  Init(tree);
  }

  Reader::~Reader()
  {
    if (!fChain) return;
    delete fChain->GetCurrentFile();
  }

  Int_t Reader::GetEntry(Long64_t entry)
  {
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
  }

  Long64_t Reader::LoadTree(Long64_t entry)
  {
    // Set the environment to read one entry
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
    }
    return centry;
  }

  Bool_t Reader::Notify()
  {
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
  }

  void Reader::Show(Long64_t entry)
  {
    // Print contents of entry.
    // If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
  }

  Int_t Reader::Cut(Long64_t entry)
  {
    // This function may be called from Loop.
    // returns  1 if entry is accepted.
    // returns -1 otherwise.
    return 1;
  }

  void Reader::AddFiles(const std::vector<std::string>& file_names_vector)
  {
    for ( auto const& filen : file_names_vector ) {
      std::cout << "Adding file " << filen << std::endl;
      fRealChain->Add(filen.c_str());
    }
  }

  void Reader::AddFile(const char* file_name)
  {
    fRealChain->Add(file_name);
  }

  void Reader::InitRealChain()
  {
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    // Set object pointer
    trig_EF_el_EF_e24vh_medium1 = 0;
    trig_EF_el_EF_e24vhi_medium1 = 0;
    trig_EF_el_EF_e60_medium1 = 0;
    trig_EF_trigmuonef_EF_mu24_tight = 0;
    trig_EF_trigmuonef_EF_mu24i_tight = 0;
    trig_EF_trigmuonef_EF_mu36_tight = 0;
    musp_eta = 0;
    musp_phi = 0;
    musp_innerSegments = 0;
    musp_middleSegments = 0;
    musp_outerSegments = 0;
    el_E = 0;
    el_pt = 0;
    el_eta = 0;
    el_phi = 0;
    el_charge = 0;
    el_author = 0;
    el_isEM = 0;
    el_isEMLoose = 0;
    el_isEMMedium = 0;
    el_isEMTight = 0;
    el_OQ = 0;
    el_type = 0;
    el_origin = 0;
    el_typebkg = 0;
    el_originbkg = 0;
    el_truth_type = 0;
    el_truth_matched = 0;
    el_medium = 0;
    el_tight = 0;
    el_loosePP = 0;
    el_mediumPP = 0;
    el_tightPP = 0;
    el_Ethad = 0;
    el_Ethad1 = 0;
    el_f1 = 0;
    el_Emax2 = 0;
    el_wstot = 0;
    el_emaxs1 = 0;
    el_weta2 = 0;
    el_f3 = 0;
    el_Etcone20 = 0;
    el_Etcone30 = 0;
    el_ptcone30 = 0;
    el_deltaeta1 = 0;
    el_deltaphi2 = 0;
    el_deltaphiRescaled = 0;
    el_expectHitInBLayer = 0;
    el_trackd0_physics = 0;
    el_reta = 0;
    el_rphi = 0;
    el_etap = 0;
    el_refittedTrack_author = 0;
    el_refittedTrack_LMqoverp = 0;
    el_cl_E = 0;
    el_cl_pt = 0;
    el_cl_eta = 0;
    el_cl_phi = 0;
    el_etas2 = 0;
    el_trackphi = 0;
    el_tracktheta = 0;
    el_trackqoverp = 0;
    el_tracketa = 0;
    el_nBLHits = 0;
    el_nPixHits = 0;
    el_nTRTHits = 0;
    el_nPixelDeadSensors = 0;
    el_nSCTDeadSensors = 0;
    el_nBLayerOutliers = 0;
    el_nPixelOutliers = 0;
    el_nSCTOutliers = 0;
    el_nTRTOutliers = 0;
    el_expectBLayerHit = 0;
    el_nSiHits = 0;
    el_TRTHighTHitsRatio = 0;
    el_TRTHighTOutliersRatio = 0;
    el_trackd0pvunbiased = 0;
    el_trackz0pvunbiased = 0;
    el_tracksigd0pvunbiased = 0;
    el_Unrefittedtrack_phi = 0;
    el_Unrefittedtrack_pt = 0;
    el_Unrefittedtrack_eta = 0;
    el_MI10_max40_ptsum = 0;
    el_trk_index = 0;
    el_GSF_trk_index = 0;
    mu_E = 0;
    mu_pt = 0;
    mu_eta = 0;
    mu_phi = 0;
    mu_px = 0;
    mu_py = 0;
    mu_pz = 0;
    mu_charge = 0;
    mu_author = 0;
    mu_etcone20 = 0;
    mu_etcone30 = 0;
    mu_ptcone30 = 0;
    mu_momentumBalanceSignificance = 0;
    mu_energyLossPar = 0;
    mu_energyLossType = 0;
    mu_isStandAloneMuon = 0;
    mu_isCombinedMuon = 0;
    mu_isSegmentTaggedMuon = 0;
    mu_tight = 0;
    mu_id_z0_exPV = 0;
    mu_ms_phi = 0;
    mu_ms_theta = 0;
    mu_ms_qoverp = 0;
    mu_id_phi = 0;
    mu_id_theta = 0;
    mu_id_qoverp = 0;
    mu_me_theta = 0;
    mu_me_qoverp = 0;
    mu_nBLHits = 0;
    mu_nPixHits = 0;
    mu_nSCTHits = 0;
    mu_nTRTHits = 0;
    mu_nPixHoles = 0;
    mu_nSCTHoles = 0;
    mu_nTRTOutliers = 0;
    mu_nPixelDeadSensors = 0;
    mu_nSCTDeadSensors = 0;
    mu_expectBLayerHit = 0;
    mu_nprecisionLayers = 0;
    mu_trackphi = 0;
    mu_tracktheta = 0;
    mu_trackqoverp = 0;
    mu_trackd0beam = 0;
    mu_truth_type = 0;
    mu_truth_barcode = 0;
    mu_truth_matched = 0;
    mu_MI10_max40_ptsum = 0;
    mu_muid_E = 0;
    mu_muid_pt = 0;
    mu_muid_eta = 0;
    mu_muid_phi = 0;
    mu_muid_px = 0;
    mu_muid_py = 0;
    mu_muid_pz = 0;
    mu_muid_charge = 0;
    mu_muid_author = 0;
    mu_muid_etcone20 = 0;
    mu_muid_etcone30 = 0;
    mu_muid_ptcone30 = 0;
    mu_muid_energyLossPar = 0;
    mu_muid_energyLossType = 0;
    mu_muid_isStandAloneMuon = 0;
    mu_muid_isCombinedMuon = 0;
    mu_muid_isSegmentTaggedMuon = 0;
    mu_muid_tight = 0;
    mu_muid_id_z0_exPV = 0;
    mu_muid_id_theta_exPV = 0;
    mu_muid_id_qoverp_exPV = 0;
    mu_muid_ms_phi = 0;
    mu_muid_ms_theta = 0;
    mu_muid_ms_qoverp = 0;
    mu_muid_id_phi = 0;
    mu_muid_id_theta = 0;
    mu_muid_id_qoverp = 0;
    mu_muid_me_theta = 0;
    mu_muid_me_qoverp = 0;
    mu_muid_nBLHits = 0;
    mu_muid_nPixHits = 0;
    mu_muid_nSCTHits = 0;
    mu_muid_nTRTHits = 0;
    mu_muid_nPixHoles = 0;
    mu_muid_nSCTHoles = 0;
    mu_muid_nTRTOutliers = 0;
    mu_muid_nPixelDeadSensors = 0;
    mu_muid_nSCTDeadSensors = 0;
    mu_muid_expectBLayerHit = 0;
    mu_muid_trackphi = 0;
    mu_muid_tracktheta = 0;
    mu_muid_trackqoverp = 0;
    mu_muid_trackd0beam = 0;
    mu_muid_trackd0pvunbiased = 0;
    mu_muid_tracksigd0pvunbiased = 0;
    mu_muid_truth_type = 0;
    mu_muid_truth_barcode = 0;
    mu_muid_truth_matched = 0;
    mu_muid_MI10_max40_ptsum = 0;
    el_MET_tightpp_wpx = 0;
    el_MET_tightpp_wpy = 0;
    el_MET_tightpp_wet = 0;
    el_MET_tightpp_statusWord = 0;
    mu_muid_MET_tightpp_wpx = 0;
    mu_muid_MET_tightpp_wpy = 0;
    mu_muid_MET_tightpp_wet = 0;
    mu_muid_MET_tightpp_statusWord = 0;
    jet_AntiKt4LCTopo_MET_tightpp_wpx = 0;
    jet_AntiKt4LCTopo_MET_tightpp_wpy = 0;
    jet_AntiKt4LCTopo_MET_tightpp_wet = 0;
    jet_AntiKt4LCTopo_MET_tightpp_statusWord = 0;
    el_MET_mediumpp_wpx = 0;
    el_MET_mediumpp_wpy = 0;
    el_MET_mediumpp_wet = 0;
    el_MET_mediumpp_statusWord = 0;
    mu_muid_MET_mediumpp_wpx = 0;
    mu_muid_MET_mediumpp_wpy = 0;
    mu_muid_MET_mediumpp_wet = 0;
    mu_muid_MET_mediumpp_statusWord = 0;
    jet_AntiKt4LCTopo_MET_mediumpp_wpx = 0;
    jet_AntiKt4LCTopo_MET_mediumpp_wpy = 0;
    jet_AntiKt4LCTopo_MET_mediumpp_wet = 0;
    jet_AntiKt4LCTopo_MET_mediumpp_statusWord = 0;
    jet_AntiKt4LCTopo_E = 0;
    jet_AntiKt4LCTopo_pt = 0;
    jet_AntiKt4LCTopo_eta = 0;
    jet_AntiKt4LCTopo_phi = 0;
    jet_AntiKt4LCTopo_EtaOrigin = 0;
    jet_AntiKt4LCTopo_PhiOrigin = 0;
    jet_AntiKt4LCTopo_MOrigin = 0;
    jet_AntiKt4LCTopo_BCH_CORR_CELL = 0;
    jet_AntiKt4LCTopo_BCH_CORR_JET = 0;
    jet_AntiKt4LCTopo_SamplingMax = 0;
    jet_AntiKt4LCTopo_fracSamplingMax = 0;
    jet_AntiKt4LCTopo_isUgly = 0;
    jet_AntiKt4LCTopo_isBadLooseMinus = 0;
    jet_AntiKt4LCTopo_emfrac = 0;
    jet_AntiKt4LCTopo_emscale_E = 0;
    jet_AntiKt4LCTopo_emscale_pt = 0;
    jet_AntiKt4LCTopo_emscale_m = 0;
    jet_AntiKt4LCTopo_emscale_eta = 0;
    jet_AntiKt4LCTopo_emscale_phi = 0;
    jet_AntiKt4LCTopo_ActiveAreaPx = 0;
    jet_AntiKt4LCTopo_ActiveAreaPy = 0;
    jet_AntiKt4LCTopo_ActiveAreaPz = 0;
    jet_AntiKt4LCTopo_ActiveAreaE = 0;
    jet_AntiKt4LCTopo_jvtxf = 0;
    jet_AntiKt4LCTopo_constscale_E = 0;
    jet_AntiKt4LCTopo_constscale_pt = 0;
    jet_AntiKt4LCTopo_constscale_m = 0;
    jet_AntiKt4LCTopo_constscale_eta = 0;
    jet_AntiKt4LCTopo_constscale_phi = 0;
    jet_AntiKt4LCTopo_flavor_weight_IP3D = 0;
    jet_AntiKt4LCTopo_flavor_weight_JetFitterCOMBNN = 0;
    jet_AntiKt4LCTopo_flavor_weight_MV1 = 0;
    jet_AntiKt4LCTopo_flavor_weight_SV0 = 0;
    jet_AntiKt4LCTopo_flavor_weight_SV1 = 0;
    jet_AntiKt4LCTopo_flavor_truth_label = 0;
    jet_AntiKt4LCTopo_flavor_component_jfitcomb_pu = 0;
    jet_AntiKt4LCTopo_flavor_component_jfitcomb_pb = 0;
    jet_AntiKt4LCTopo_flavor_component_jfitcomb_pc = 0;
    jet_AntiKt4LCTopo_nTrk_pv0_1GeV = 0;
    jet_AntiKt4LCTopo_trackWIDTH_pv0_1GeV = 0;
    jet_AntiKt4LCTopo_TrackAssoc_index = 0;
    AntiKt4Truth_E = 0;
    AntiKt4Truth_pt = 0;
    AntiKt4Truth_eta = 0;
    AntiKt4Truth_phi = 0;
    cl_lc_pt = 0;
    cl_lc_eta = 0;
    cl_lc_phi = 0;
    trk_pt = 0;
    trk_eta = 0;
    trk_d0_wrtPV = 0;
    trk_z0_wrtPV = 0;
    trk_phi_wrtPV = 0;
    trk_theta_wrtPV = 0;
    trk_qoverp_wrtPV = 0;
    trk_nPixHits = 0;
    trk_nSCTHits = 0;
    trkpt4_pt = 0;
    trkpt4_eta = 0;
    trkpt4_phi_wrtPV = 0;
    trkpt4_err_qoverp_wrtPV = 0;
    vxp_z = 0;
    vxp_type = 0;
    vxp_nTracks = 0;
    mc_pt = 0;
    mc_m = 0;
    mc_eta = 0;
    mc_phi = 0;
    mc_status = 0;
    mc_barcode = 0;
    mc_pdgId = 0;
    mc_charge = 0;
    mc_child_index = 0;
    mc_parent_index = 0;
    mcVx_z = 0;
    muonTruth_barcode = 0;
    muonTruth_type = 0;
    muonTruth_origin = 0;
    mcevt_weight = 0;
    trig_EF_el_eta = 0;
    trig_EF_el_phi = 0;
    trig_EF_trigmuonef_track_n = 0;
    trig_EF_trigmuonef_track_CB_pt = 0;
    trig_EF_trigmuonef_track_CB_eta = 0;
    trig_EF_trigmuonef_track_CB_phi = 0;
    GSF_trk_trk_index = 0;

    fRealChain->SetBranchAddress("EF_e24vh_medium1", &EF_e24vh_medium1, &b_EF_e24vh_medium1);
    fRealChain->SetBranchAddress("EF_e24vhi_medium1", &EF_e24vhi_medium1, &b_EF_e24vhi_medium1);
    fRealChain->SetBranchAddress("EF_e60_medium1", &EF_e60_medium1, &b_EF_e60_medium1);
    fRealChain->SetBranchAddress("EF_mu24_tight", &EF_mu24_tight, &b_EF_mu24_tight);
    fRealChain->SetBranchAddress("EF_mu24i_tight", &EF_mu24i_tight, &b_EF_mu24i_tight);
    fRealChain->SetBranchAddress("EF_mu36_tight", &EF_mu36_tight, &b_EF_mu36_tight);
    fRealChain->SetBranchAddress("trig_EF_el_EF_e24vh_medium1", &trig_EF_el_EF_e24vh_medium1, &b_trig_EF_el_EF_e24vh_medium1);
    fRealChain->SetBranchAddress("trig_EF_el_EF_e24vhi_medium1", &trig_EF_el_EF_e24vhi_medium1, &b_trig_EF_el_EF_e24vhi_medium1);
    fRealChain->SetBranchAddress("trig_EF_el_EF_e60_medium1", &trig_EF_el_EF_e60_medium1, &b_trig_EF_el_EF_e60_medium1);
    fRealChain->SetBranchAddress("trig_EF_trigmuonef_EF_mu24_tight", &trig_EF_trigmuonef_EF_mu24_tight, &b_trig_EF_trigmuonef_EF_mu24_tight);
    fRealChain->SetBranchAddress("trig_EF_trigmuonef_EF_mu24i_tight", &trig_EF_trigmuonef_EF_mu24i_tight, &b_trig_EF_trigmuonef_EF_mu24i_tight);
    fRealChain->SetBranchAddress("trig_EF_trigmuonef_EF_mu36_tight", &trig_EF_trigmuonef_EF_mu36_tight, &b_trig_EF_trigmuonef_EF_mu36_tight);
    fRealChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
    fRealChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
    fRealChain->SetBranchAddress("lbn", &lbn, &b_lbn);
    fRealChain->SetBranchAddress("averageIntPerXing", &averageIntPerXing, &b_averageIntPerXing);
    fRealChain->SetBranchAddress("mc_channel_number", &mc_channel_number, &b_mc_channel_number);
    fRealChain->SetBranchAddress("coreFlags", &coreFlags, &b_coreFlags);
    fRealChain->SetBranchAddress("larError", &larError, &b_larError);
    fRealChain->SetBranchAddress("tileError", &tileError, &b_tileError);
    fRealChain->SetBranchAddress("Eventshape_rhoKt4EM", &Eventshape_rhoKt4EM, &b_Eventshape_rhoKt4EM);
    fRealChain->SetBranchAddress("Eventshape_rhoKt4LC", &Eventshape_rhoKt4LC, &b_Eventshape_rhoKt4LC);
    fRealChain->SetBranchAddress("musp_eta", &musp_eta, &b_musp_eta);
    fRealChain->SetBranchAddress("musp_phi", &musp_phi, &b_musp_phi);
    fRealChain->SetBranchAddress("musp_innerSegments", &musp_innerSegments, &b_musp_innerSegments);
    fRealChain->SetBranchAddress("musp_middleSegments", &musp_middleSegments, &b_musp_middleSegments);
    fRealChain->SetBranchAddress("musp_outerSegments", &musp_outerSegments, &b_musp_outerSegments);
    fRealChain->SetBranchAddress("el_n", &el_n, &b_el_n);
    fRealChain->SetBranchAddress("el_E", &el_E, &b_el_E);
    fRealChain->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
    fRealChain->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
    fRealChain->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
    fRealChain->SetBranchAddress("el_charge", &el_charge, &b_el_charge);
    fRealChain->SetBranchAddress("el_author", &el_author, &b_el_author);
    fRealChain->SetBranchAddress("el_isEM", &el_isEM, &b_el_isEM);
    fRealChain->SetBranchAddress("el_isEMLoose", &el_isEMLoose, &b_el_isEMLoose);
    fRealChain->SetBranchAddress("el_isEMMedium", &el_isEMMedium, &b_el_isEMMedium);
    fRealChain->SetBranchAddress("el_isEMTight", &el_isEMTight, &b_el_isEMTight);
    fRealChain->SetBranchAddress("el_OQ", &el_OQ, &b_el_OQ);
    fRealChain->SetBranchAddress("el_type", &el_type, &b_el_type);
    fRealChain->SetBranchAddress("el_origin", &el_origin, &b_el_origin);
    fRealChain->SetBranchAddress("el_typebkg", &el_typebkg, &b_el_typebkg);
    fRealChain->SetBranchAddress("el_originbkg", &el_originbkg, &b_el_originbkg);
    fRealChain->SetBranchAddress("el_truth_type", &el_truth_type, &b_el_truth_type);
    fRealChain->SetBranchAddress("el_truth_matched", &el_truth_matched, &b_el_truth_matched);
    fRealChain->SetBranchAddress("el_medium", &el_medium, &b_el_medium);
    fRealChain->SetBranchAddress("el_tight", &el_tight, &b_el_tight);
    fRealChain->SetBranchAddress("el_loosePP", &el_loosePP, &b_el_loosePP);
    fRealChain->SetBranchAddress("el_mediumPP", &el_mediumPP, &b_el_mediumPP);
    fRealChain->SetBranchAddress("el_tightPP", &el_tightPP, &b_el_tightPP);
    fRealChain->SetBranchAddress("el_Ethad", &el_Ethad, &b_el_Ethad);
    fRealChain->SetBranchAddress("el_Ethad1", &el_Ethad1, &b_el_Ethad1);
    fRealChain->SetBranchAddress("el_f1", &el_f1, &b_el_f1);
    fRealChain->SetBranchAddress("el_Emax2", &el_Emax2, &b_el_Emax2);
    fRealChain->SetBranchAddress("el_wstot", &el_wstot, &b_el_wstot);
    fRealChain->SetBranchAddress("el_emaxs1", &el_emaxs1, &b_el_emaxs1);
    fRealChain->SetBranchAddress("el_weta2", &el_weta2, &b_el_weta2);
    fRealChain->SetBranchAddress("el_f3", &el_f3, &b_el_f3);
    fRealChain->SetBranchAddress("el_Etcone20", &el_Etcone20, &b_el_Etcone20);
    fRealChain->SetBranchAddress("el_Etcone30", &el_Etcone30, &b_el_Etcone30);
    fRealChain->SetBranchAddress("el_ptcone30", &el_ptcone30, &b_el_ptcone30);
    fRealChain->SetBranchAddress("el_deltaeta1", &el_deltaeta1, &b_el_deltaeta1);
    fRealChain->SetBranchAddress("el_deltaphi2", &el_deltaphi2, &b_el_deltaphi2);
    fRealChain->SetBranchAddress("el_deltaphiRescaled", &el_deltaphiRescaled, &b_el_deltaphiRescaled);
    fRealChain->SetBranchAddress("el_expectHitInBLayer", &el_expectHitInBLayer, &b_el_expectHitInBLayer);
    fRealChain->SetBranchAddress("el_trackd0_physics", &el_trackd0_physics, &b_el_trackd0_physics);
    fRealChain->SetBranchAddress("el_reta", &el_reta, &b_el_reta);
    fRealChain->SetBranchAddress("el_rphi", &el_rphi, &b_el_rphi);
    fRealChain->SetBranchAddress("el_etap", &el_etap, &b_el_etap);
    fRealChain->SetBranchAddress("el_refittedTrack_author", &el_refittedTrack_author, &b_el_refittedTrack_author);
    fRealChain->SetBranchAddress("el_refittedTrack_LMqoverp", &el_refittedTrack_LMqoverp, &b_el_refittedTrack_LMqoverp);
    fRealChain->SetBranchAddress("el_cl_E", &el_cl_E, &b_el_cl_E);
    fRealChain->SetBranchAddress("el_cl_pt", &el_cl_pt, &b_el_cl_pt);
    fRealChain->SetBranchAddress("el_cl_eta", &el_cl_eta, &b_el_cl_eta);
    fRealChain->SetBranchAddress("el_cl_phi", &el_cl_phi, &b_el_cl_phi);
    fRealChain->SetBranchAddress("el_etas2", &el_etas2, &b_el_etas2);
    fRealChain->SetBranchAddress("el_trackphi", &el_trackphi, &b_el_trackphi);
    fRealChain->SetBranchAddress("el_tracktheta", &el_tracktheta, &b_el_tracktheta);
    fRealChain->SetBranchAddress("el_trackqoverp", &el_trackqoverp, &b_el_trackqoverp);
    fRealChain->SetBranchAddress("el_tracketa", &el_tracketa, &b_el_tracketa);
    fRealChain->SetBranchAddress("el_nBLHits", &el_nBLHits, &b_el_nBLHits);
    fRealChain->SetBranchAddress("el_nPixHits", &el_nPixHits, &b_el_nPixHits);
    fRealChain->SetBranchAddress("el_nTRTHits", &el_nTRTHits, &b_el_nTRTHits);
    fRealChain->SetBranchAddress("el_nPixelDeadSensors", &el_nPixelDeadSensors, &b_el_nPixelDeadSensors);
    fRealChain->SetBranchAddress("el_nSCTDeadSensors", &el_nSCTDeadSensors, &b_el_nSCTDeadSensors);
    fRealChain->SetBranchAddress("el_nBLayerOutliers", &el_nBLayerOutliers, &b_el_nBLayerOutliers);
    fRealChain->SetBranchAddress("el_nPixelOutliers", &el_nPixelOutliers, &b_el_nPixelOutliers);
    fRealChain->SetBranchAddress("el_nSCTOutliers", &el_nSCTOutliers, &b_el_nSCTOutliers);
    fRealChain->SetBranchAddress("el_nTRTOutliers", &el_nTRTOutliers, &b_el_nTRTOutliers);
    fRealChain->SetBranchAddress("el_expectBLayerHit", &el_expectBLayerHit, &b_el_expectBLayerHit);
    fRealChain->SetBranchAddress("el_nSiHits", &el_nSiHits, &b_el_nSiHits);
    fRealChain->SetBranchAddress("el_TRTHighTHitsRatio", &el_TRTHighTHitsRatio, &b_el_TRTHighTHitsRatio);
    fRealChain->SetBranchAddress("el_TRTHighTOutliersRatio", &el_TRTHighTOutliersRatio, &b_el_TRTHighTOutliersRatio);
    fRealChain->SetBranchAddress("el_trackd0pvunbiased", &el_trackd0pvunbiased, &b_el_trackd0pvunbiased);
    fRealChain->SetBranchAddress("el_trackz0pvunbiased", &el_trackz0pvunbiased, &b_el_trackz0pvunbiased);
    fRealChain->SetBranchAddress("el_tracksigd0pvunbiased", &el_tracksigd0pvunbiased, &b_el_tracksigd0pvunbiased);
    fRealChain->SetBranchAddress("el_Unrefittedtrack_phi", &el_Unrefittedtrack_phi, &b_el_Unrefittedtrack_phi);
    fRealChain->SetBranchAddress("el_Unrefittedtrack_pt", &el_Unrefittedtrack_pt, &b_el_Unrefittedtrack_pt);
    fRealChain->SetBranchAddress("el_Unrefittedtrack_eta", &el_Unrefittedtrack_eta, &b_el_Unrefittedtrack_eta);
    fRealChain->SetBranchAddress("el_MI10_max40_ptsum", &el_MI10_max40_ptsum, &b_el_MI10_max40_ptsum);
    fRealChain->SetBranchAddress("el_trk_index", &el_trk_index, &b_el_trk_index);
    fRealChain->SetBranchAddress("el_GSF_trk_index", &el_GSF_trk_index, &b_el_GSF_trk_index);
    fRealChain->SetBranchAddress("mu_n", &mu_n, &b_mu_n);
    fRealChain->SetBranchAddress("mu_E", &mu_E, &b_mu_E);
    fRealChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
    fRealChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
    fRealChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
    fRealChain->SetBranchAddress("mu_px", &mu_px, &b_mu_px);
    fRealChain->SetBranchAddress("mu_py", &mu_py, &b_mu_py);
    fRealChain->SetBranchAddress("mu_pz", &mu_pz, &b_mu_pz);
    fRealChain->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
    fRealChain->SetBranchAddress("mu_author", &mu_author, &b_mu_author);
    fRealChain->SetBranchAddress("mu_etcone20", &mu_etcone20, &b_mu_etcone20);
    fRealChain->SetBranchAddress("mu_etcone30", &mu_etcone30, &b_mu_etcone30);
    fRealChain->SetBranchAddress("mu_ptcone30", &mu_ptcone30, &b_mu_ptcone30);
    fRealChain->SetBranchAddress("mu_momentumBalanceSignificance", &mu_momentumBalanceSignificance, &b_mu_momentumBalanceSignificance);
    fRealChain->SetBranchAddress("mu_energyLossPar", &mu_energyLossPar, &b_mu_energyLossPar);
    fRealChain->SetBranchAddress("mu_energyLossType", &mu_energyLossType, &b_mu_energyLossType);
    fRealChain->SetBranchAddress("mu_isStandAloneMuon", &mu_isStandAloneMuon, &b_mu_isStandAloneMuon);
    fRealChain->SetBranchAddress("mu_isCombinedMuon", &mu_isCombinedMuon, &b_mu_isCombinedMuon);
    fRealChain->SetBranchAddress("mu_isSegmentTaggedMuon", &mu_isSegmentTaggedMuon, &b_mu_isSegmentTaggedMuon);
    fRealChain->SetBranchAddress("mu_tight", &mu_tight, &b_mu_tight);
    fRealChain->SetBranchAddress("mu_id_z0_exPV", &mu_id_z0_exPV, &b_mu_id_z0_exPV);
    fRealChain->SetBranchAddress("mu_ms_phi", &mu_ms_phi, &b_mu_ms_phi);
    fRealChain->SetBranchAddress("mu_ms_theta", &mu_ms_theta, &b_mu_ms_theta);
    fRealChain->SetBranchAddress("mu_ms_qoverp", &mu_ms_qoverp, &b_mu_ms_qoverp);
    fRealChain->SetBranchAddress("mu_id_phi", &mu_id_phi, &b_mu_id_phi);
    fRealChain->SetBranchAddress("mu_id_theta", &mu_id_theta, &b_mu_id_theta);
    fRealChain->SetBranchAddress("mu_id_qoverp", &mu_id_qoverp, &b_mu_id_qoverp);
    fRealChain->SetBranchAddress("mu_me_theta", &mu_me_theta, &b_mu_me_theta);
    fRealChain->SetBranchAddress("mu_me_qoverp", &mu_me_qoverp, &b_mu_me_qoverp);
    fRealChain->SetBranchAddress("mu_nBLHits", &mu_nBLHits, &b_mu_nBLHits);
    fRealChain->SetBranchAddress("mu_nPixHits", &mu_nPixHits, &b_mu_nPixHits);
    fRealChain->SetBranchAddress("mu_nSCTHits", &mu_nSCTHits, &b_mu_nSCTHits);
    fRealChain->SetBranchAddress("mu_nTRTHits", &mu_nTRTHits, &b_mu_nTRTHits);
    fRealChain->SetBranchAddress("mu_nPixHoles", &mu_nPixHoles, &b_mu_nPixHoles);
    fRealChain->SetBranchAddress("mu_nSCTHoles", &mu_nSCTHoles, &b_mu_nSCTHoles);
    fRealChain->SetBranchAddress("mu_nTRTOutliers", &mu_nTRTOutliers, &b_mu_nTRTOutliers);
    fRealChain->SetBranchAddress("mu_nPixelDeadSensors", &mu_nPixelDeadSensors, &b_mu_nPixelDeadSensors);
    fRealChain->SetBranchAddress("mu_nSCTDeadSensors", &mu_nSCTDeadSensors, &b_mu_nSCTDeadSensors);
    fRealChain->SetBranchAddress("mu_expectBLayerHit", &mu_expectBLayerHit, &b_mu_expectBLayerHit);
    fRealChain->SetBranchAddress("mu_nprecisionLayers", &mu_nprecisionLayers, &b_mu_nprecisionLayers);
    fRealChain->SetBranchAddress("mu_trackphi", &mu_trackphi, &b_mu_trackphi);
    fRealChain->SetBranchAddress("mu_tracktheta", &mu_tracktheta, &b_mu_tracktheta);
    fRealChain->SetBranchAddress("mu_trackqoverp", &mu_trackqoverp, &b_mu_trackqoverp);
    fRealChain->SetBranchAddress("mu_trackd0beam", &mu_trackd0beam, &b_mu_trackd0beam);
    fRealChain->SetBranchAddress("mu_truth_type", &mu_truth_type, &b_mu_truth_type);
    fRealChain->SetBranchAddress("mu_truth_barcode", &mu_truth_barcode, &b_mu_truth_barcode);
    fRealChain->SetBranchAddress("mu_truth_matched", &mu_truth_matched, &b_mu_truth_matched);
    fRealChain->SetBranchAddress("mu_MI10_max40_ptsum", &mu_MI10_max40_ptsum, &b_mu_MI10_max40_ptsum);
    fRealChain->SetBranchAddress("mu_muid_n", &mu_muid_n, &b_mu_muid_n);
    fRealChain->SetBranchAddress("mu_muid_E", &mu_muid_E, &b_mu_muid_E);
    fRealChain->SetBranchAddress("mu_muid_pt", &mu_muid_pt, &b_mu_muid_pt);
    fRealChain->SetBranchAddress("mu_muid_eta", &mu_muid_eta, &b_mu_muid_eta);
    fRealChain->SetBranchAddress("mu_muid_phi", &mu_muid_phi, &b_mu_muid_phi);
    fRealChain->SetBranchAddress("mu_muid_px", &mu_muid_px, &b_mu_muid_px);
    fRealChain->SetBranchAddress("mu_muid_py", &mu_muid_py, &b_mu_muid_py);
    fRealChain->SetBranchAddress("mu_muid_pz", &mu_muid_pz, &b_mu_muid_pz);
    fRealChain->SetBranchAddress("mu_muid_charge", &mu_muid_charge, &b_mu_muid_charge);
    fRealChain->SetBranchAddress("mu_muid_author", &mu_muid_author, &b_mu_muid_author);
    fRealChain->SetBranchAddress("mu_muid_etcone20", &mu_muid_etcone20, &b_mu_muid_etcone20);
    fRealChain->SetBranchAddress("mu_muid_etcone30", &mu_muid_etcone30, &b_mu_muid_etcone30);
    fRealChain->SetBranchAddress("mu_muid_ptcone30", &mu_muid_ptcone30, &b_mu_muid_ptcone30);
    fRealChain->SetBranchAddress("mu_muid_energyLossPar", &mu_muid_energyLossPar, &b_mu_muid_energyLossPar);
    fRealChain->SetBranchAddress("mu_muid_energyLossType", &mu_muid_energyLossType, &b_mu_muid_energyLossType);
    fRealChain->SetBranchAddress("mu_muid_isStandAloneMuon", &mu_muid_isStandAloneMuon, &b_mu_muid_isStandAloneMuon);
    fRealChain->SetBranchAddress("mu_muid_isCombinedMuon", &mu_muid_isCombinedMuon, &b_mu_muid_isCombinedMuon);
    fRealChain->SetBranchAddress("mu_muid_isSegmentTaggedMuon", &mu_muid_isSegmentTaggedMuon, &b_mu_muid_isSegmentTaggedMuon);
    fRealChain->SetBranchAddress("mu_muid_tight", &mu_muid_tight, &b_mu_muid_tight);
    fRealChain->SetBranchAddress("mu_muid_id_z0_exPV", &mu_muid_id_z0_exPV, &b_mu_muid_id_z0_exPV);
    fRealChain->SetBranchAddress("mu_muid_id_theta_exPV", &mu_muid_id_theta_exPV, &b_mu_muid_id_theta_exPV);
    fRealChain->SetBranchAddress("mu_muid_id_qoverp_exPV", &mu_muid_id_qoverp_exPV, &b_mu_muid_id_qoverp_exPV);
    fRealChain->SetBranchAddress("mu_muid_ms_phi", &mu_muid_ms_phi, &b_mu_muid_ms_phi);
    fRealChain->SetBranchAddress("mu_muid_ms_theta", &mu_muid_ms_theta, &b_mu_muid_ms_theta);
    fRealChain->SetBranchAddress("mu_muid_ms_qoverp", &mu_muid_ms_qoverp, &b_mu_muid_ms_qoverp);
    fRealChain->SetBranchAddress("mu_muid_id_phi", &mu_muid_id_phi, &b_mu_muid_id_phi);
    fRealChain->SetBranchAddress("mu_muid_id_theta", &mu_muid_id_theta, &b_mu_muid_id_theta);
    fRealChain->SetBranchAddress("mu_muid_id_qoverp", &mu_muid_id_qoverp, &b_mu_muid_id_qoverp);
    fRealChain->SetBranchAddress("mu_muid_me_theta", &mu_muid_me_theta, &b_mu_muid_me_theta);
    fRealChain->SetBranchAddress("mu_muid_me_qoverp", &mu_muid_me_qoverp, &b_mu_muid_me_qoverp);
    fRealChain->SetBranchAddress("mu_muid_nBLHits", &mu_muid_nBLHits, &b_mu_muid_nBLHits);
    fRealChain->SetBranchAddress("mu_muid_nPixHits", &mu_muid_nPixHits, &b_mu_muid_nPixHits);
    fRealChain->SetBranchAddress("mu_muid_nSCTHits", &mu_muid_nSCTHits, &b_mu_muid_nSCTHits);
    fRealChain->SetBranchAddress("mu_muid_nTRTHits", &mu_muid_nTRTHits, &b_mu_muid_nTRTHits);
    fRealChain->SetBranchAddress("mu_muid_nPixHoles", &mu_muid_nPixHoles, &b_mu_muid_nPixHoles);
    fRealChain->SetBranchAddress("mu_muid_nSCTHoles", &mu_muid_nSCTHoles, &b_mu_muid_nSCTHoles);
    fRealChain->SetBranchAddress("mu_muid_nTRTOutliers", &mu_muid_nTRTOutliers, &b_mu_muid_nTRTOutliers);
    fRealChain->SetBranchAddress("mu_muid_nPixelDeadSensors", &mu_muid_nPixelDeadSensors, &b_mu_muid_nPixelDeadSensors);
    fRealChain->SetBranchAddress("mu_muid_nSCTDeadSensors", &mu_muid_nSCTDeadSensors, &b_mu_muid_nSCTDeadSensors);
    fRealChain->SetBranchAddress("mu_muid_expectBLayerHit", &mu_muid_expectBLayerHit, &b_mu_muid_expectBLayerHit);
    fRealChain->SetBranchAddress("mu_muid_trackphi", &mu_muid_trackphi, &b_mu_muid_trackphi);
    fRealChain->SetBranchAddress("mu_muid_tracktheta", &mu_muid_tracktheta, &b_mu_muid_tracktheta);
    fRealChain->SetBranchAddress("mu_muid_trackqoverp", &mu_muid_trackqoverp, &b_mu_muid_trackqoverp);
    fRealChain->SetBranchAddress("mu_muid_trackd0beam", &mu_muid_trackd0beam, &b_mu_muid_trackd0beam);
    fRealChain->SetBranchAddress("mu_muid_trackd0pvunbiased", &mu_muid_trackd0pvunbiased, &b_mu_muid_trackd0pvunbiased);
    fRealChain->SetBranchAddress("mu_muid_tracksigd0pvunbiased", &mu_muid_tracksigd0pvunbiased, &b_mu_muid_tracksigd0pvunbiased);
    fRealChain->SetBranchAddress("mu_muid_truth_type", &mu_muid_truth_type, &b_mu_muid_truth_type);
    fRealChain->SetBranchAddress("mu_muid_truth_barcode", &mu_muid_truth_barcode, &b_mu_muid_truth_barcode);
    fRealChain->SetBranchAddress("mu_muid_truth_matched", &mu_muid_truth_matched, &b_mu_muid_truth_matched);
    fRealChain->SetBranchAddress("mu_muid_MI10_max40_ptsum", &mu_muid_MI10_max40_ptsum, &b_mu_muid_MI10_max40_ptsum);
    fRealChain->SetBranchAddress("MET_RefEle_tightpp_etx", &MET_RefEle_tightpp_etx, &b_MET_RefEle_tightpp_etx);
    fRealChain->SetBranchAddress("MET_RefEle_tightpp_ety", &MET_RefEle_tightpp_ety, &b_MET_RefEle_tightpp_ety);
    fRealChain->SetBranchAddress("MET_RefEle_tightpp_sumet", &MET_RefEle_tightpp_sumet, &b_MET_RefEle_tightpp_sumet);
    fRealChain->SetBranchAddress("MET_RefEle_mediumpp_etx", &MET_RefEle_mediumpp_etx, &b_MET_RefEle_mediumpp_etx);
    fRealChain->SetBranchAddress("MET_RefEle_mediumpp_ety", &MET_RefEle_mediumpp_ety, &b_MET_RefEle_mediumpp_ety);
    fRealChain->SetBranchAddress("MET_RefEle_mediumpp_sumet", &MET_RefEle_mediumpp_sumet, &b_MET_RefEle_mediumpp_sumet);
    fRealChain->SetBranchAddress("MET_RefJet_tightpp_etx", &MET_RefJet_tightpp_etx, &b_MET_RefJet_tightpp_etx);
    fRealChain->SetBranchAddress("MET_RefJet_tightpp_ety", &MET_RefJet_tightpp_ety, &b_MET_RefJet_tightpp_ety);
    fRealChain->SetBranchAddress("MET_RefJet_tightpp_sumet", &MET_RefJet_tightpp_sumet, &b_MET_RefJet_tightpp_sumet);
    fRealChain->SetBranchAddress("MET_RefJet_mediumpp_etx", &MET_RefJet_mediumpp_etx, &b_MET_RefJet_mediumpp_etx);
    fRealChain->SetBranchAddress("MET_RefJet_mediumpp_ety", &MET_RefJet_mediumpp_ety, &b_MET_RefJet_mediumpp_ety);
    fRealChain->SetBranchAddress("MET_RefJet_mediumpp_sumet", &MET_RefJet_mediumpp_sumet, &b_MET_RefJet_mediumpp_sumet);
    fRealChain->SetBranchAddress("MET_CellOut_tightpp_etx", &MET_CellOut_tightpp_etx, &b_MET_CellOut_tightpp_etx);
    fRealChain->SetBranchAddress("MET_CellOut_tightpp_ety", &MET_CellOut_tightpp_ety, &b_MET_CellOut_tightpp_ety);
    fRealChain->SetBranchAddress("MET_CellOut_tightpp_sumet", &MET_CellOut_tightpp_sumet, &b_MET_CellOut_tightpp_sumet);
    fRealChain->SetBranchAddress("MET_CellOut_mediumpp_etx", &MET_CellOut_mediumpp_etx, &b_MET_CellOut_mediumpp_etx);
    fRealChain->SetBranchAddress("MET_CellOut_mediumpp_ety", &MET_CellOut_mediumpp_ety, &b_MET_CellOut_mediumpp_ety);
    fRealChain->SetBranchAddress("MET_CellOut_mediumpp_sumet", &MET_CellOut_mediumpp_sumet, &b_MET_CellOut_mediumpp_sumet);
    fRealChain->SetBranchAddress("MET_Muon_Total_Muid_tightpp_etx", &MET_Muon_Total_Muid_tightpp_etx, &b_MET_Muon_Total_Muid_tightpp_etx);
    fRealChain->SetBranchAddress("MET_Muon_Total_Muid_tightpp_ety", &MET_Muon_Total_Muid_tightpp_ety, &b_MET_Muon_Total_Muid_tightpp_ety);
    fRealChain->SetBranchAddress("MET_Muon_Total_Muid_tightpp_sumet", &MET_Muon_Total_Muid_tightpp_sumet, &b_MET_Muon_Total_Muid_tightpp_sumet);
    fRealChain->SetBranchAddress("MET_Muon_Total_Muid_mediumpp_etx", &MET_Muon_Total_Muid_mediumpp_etx, &b_MET_Muon_Total_Muid_mediumpp_etx);
    fRealChain->SetBranchAddress("MET_Muon_Total_Muid_mediumpp_ety", &MET_Muon_Total_Muid_mediumpp_ety, &b_MET_Muon_Total_Muid_mediumpp_ety);
    fRealChain->SetBranchAddress("MET_Muon_Total_Muid_mediumpp_sumet", &MET_Muon_Total_Muid_mediumpp_sumet, &b_MET_Muon_Total_Muid_mediumpp_sumet);
    fRealChain->SetBranchAddress("MET_RefGamma_tightpp_etx", &MET_RefGamma_tightpp_etx, &b_MET_RefGamma_tightpp_etx);
    fRealChain->SetBranchAddress("MET_RefGamma_tightpp_ety", &MET_RefGamma_tightpp_ety, &b_MET_RefGamma_tightpp_ety);
    fRealChain->SetBranchAddress("MET_RefGamma_tightpp_sumet", &MET_RefGamma_tightpp_sumet, &b_MET_RefGamma_tightpp_sumet);
    fRealChain->SetBranchAddress("MET_RefGamma_mediumpp_etx", &MET_RefGamma_mediumpp_etx, &b_MET_RefGamma_mediumpp_etx);
    fRealChain->SetBranchAddress("MET_RefGamma_mediumpp_ety", &MET_RefGamma_mediumpp_ety, &b_MET_RefGamma_mediumpp_ety);
    fRealChain->SetBranchAddress("MET_RefGamma_mediumpp_sumet", &MET_RefGamma_mediumpp_sumet, &b_MET_RefGamma_mediumpp_sumet);
    fRealChain->SetBranchAddress("MET_RefFinal_tightpp_etx", &MET_RefFinal_tightpp_etx, &b_MET_RefFinal_tightpp_etx);
    fRealChain->SetBranchAddress("MET_RefFinal_tightpp_ety", &MET_RefFinal_tightpp_ety, &b_MET_RefFinal_tightpp_ety);
    fRealChain->SetBranchAddress("MET_RefFinal_tightpp_sumet", &MET_RefFinal_tightpp_sumet, &b_MET_RefFinal_tightpp_sumet);
    fRealChain->SetBranchAddress("MET_RefFinal_mediumpp_etx", &MET_RefFinal_mediumpp_etx, &b_MET_RefFinal_mediumpp_etx);
    fRealChain->SetBranchAddress("MET_RefFinal_mediumpp_ety", &MET_RefFinal_mediumpp_ety, &b_MET_RefFinal_mediumpp_ety);
    fRealChain->SetBranchAddress("MET_RefFinal_mediumpp_sumet", &MET_RefFinal_mediumpp_sumet, &b_MET_RefFinal_mediumpp_sumet);
    fRealChain->SetBranchAddress("el_MET_tightpp_wpx", &el_MET_tightpp_wpx, &b_el_MET_tightpp_wpx);
    fRealChain->SetBranchAddress("el_MET_tightpp_wpy", &el_MET_tightpp_wpy, &b_el_MET_tightpp_wpy);
    fRealChain->SetBranchAddress("el_MET_tightpp_wet", &el_MET_tightpp_wet, &b_el_MET_tightpp_wet);
    fRealChain->SetBranchAddress("el_MET_tightpp_statusWord", &el_MET_tightpp_statusWord, &b_el_MET_tightpp_statusWord);
    fRealChain->SetBranchAddress("mu_muid_MET_tightpp_wpx", &mu_muid_MET_tightpp_wpx, &b_mu_muid_MET_tightpp_wpx);
    fRealChain->SetBranchAddress("mu_muid_MET_tightpp_wpy", &mu_muid_MET_tightpp_wpy, &b_mu_muid_MET_tightpp_wpy);
    fRealChain->SetBranchAddress("mu_muid_MET_tightpp_wet", &mu_muid_MET_tightpp_wet, &b_mu_muid_MET_tightpp_wet);
    fRealChain->SetBranchAddress("mu_muid_MET_tightpp_statusWord", &mu_muid_MET_tightpp_statusWord, &b_mu_muid_MET_tightpp_statusWord);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_MET_tightpp_wpx", &jet_AntiKt4LCTopo_MET_tightpp_wpx, &b_jet_AntiKt4LCTopo_MET_tightpp_wpx);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_MET_tightpp_wpy", &jet_AntiKt4LCTopo_MET_tightpp_wpy, &b_jet_AntiKt4LCTopo_MET_tightpp_wpy);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_MET_tightpp_wet", &jet_AntiKt4LCTopo_MET_tightpp_wet, &b_jet_AntiKt4LCTopo_MET_tightpp_wet);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_MET_tightpp_statusWord", &jet_AntiKt4LCTopo_MET_tightpp_statusWord, &b_jet_AntiKt4LCTopo_MET_tightpp_statusWord);
    fRealChain->SetBranchAddress("el_MET_mediumpp_wpx", &el_MET_mediumpp_wpx, &b_el_MET_mediumpp_wpx);
    fRealChain->SetBranchAddress("el_MET_mediumpp_wpy", &el_MET_mediumpp_wpy, &b_el_MET_mediumpp_wpy);
    fRealChain->SetBranchAddress("el_MET_mediumpp_wet", &el_MET_mediumpp_wet, &b_el_MET_mediumpp_wet);
    fRealChain->SetBranchAddress("el_MET_mediumpp_statusWord", &el_MET_mediumpp_statusWord, &b_el_MET_mediumpp_statusWord);
    fRealChain->SetBranchAddress("mu_muid_MET_mediumpp_wpx", &mu_muid_MET_mediumpp_wpx, &b_mu_muid_MET_mediumpp_wpx);
    fRealChain->SetBranchAddress("mu_muid_MET_mediumpp_wpy", &mu_muid_MET_mediumpp_wpy, &b_mu_muid_MET_mediumpp_wpy);
    fRealChain->SetBranchAddress("mu_muid_MET_mediumpp_wet", &mu_muid_MET_mediumpp_wet, &b_mu_muid_MET_mediumpp_wet);
    fRealChain->SetBranchAddress("mu_muid_MET_mediumpp_statusWord", &mu_muid_MET_mediumpp_statusWord, &b_mu_muid_MET_mediumpp_statusWord);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_MET_mediumpp_wpx", &jet_AntiKt4LCTopo_MET_mediumpp_wpx, &b_jet_AntiKt4LCTopo_MET_mediumpp_wpx);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_MET_mediumpp_wpy", &jet_AntiKt4LCTopo_MET_mediumpp_wpy, &b_jet_AntiKt4LCTopo_MET_mediumpp_wpy);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_MET_mediumpp_wet", &jet_AntiKt4LCTopo_MET_mediumpp_wet, &b_jet_AntiKt4LCTopo_MET_mediumpp_wet);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_MET_mediumpp_statusWord", &jet_AntiKt4LCTopo_MET_mediumpp_statusWord, &b_jet_AntiKt4LCTopo_MET_mediumpp_statusWord);
    fRealChain->SetBranchAddress("MET_Truth_NonInt_etx", &MET_Truth_NonInt_etx, &b_MET_Truth_NonInt_etx);
    fRealChain->SetBranchAddress("MET_Truth_NonInt_ety", &MET_Truth_NonInt_ety, &b_MET_Truth_NonInt_ety);
    fRealChain->SetBranchAddress("MET_Truth_NonInt_sumet", &MET_Truth_NonInt_sumet, &b_MET_Truth_NonInt_sumet);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_n", &jet_AntiKt4LCTopo_n, &b_jet_AntiKt4LCTopo_n);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_E", &jet_AntiKt4LCTopo_E, &b_jet_AntiKt4LCTopo_E);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_pt", &jet_AntiKt4LCTopo_pt, &b_jet_AntiKt4LCTopo_pt);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_eta", &jet_AntiKt4LCTopo_eta, &b_jet_AntiKt4LCTopo_eta);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_phi", &jet_AntiKt4LCTopo_phi, &b_jet_AntiKt4LCTopo_phi);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_EtaOrigin", &jet_AntiKt4LCTopo_EtaOrigin, &b_jet_AntiKt4LCTopo_EtaOrigin);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_PhiOrigin", &jet_AntiKt4LCTopo_PhiOrigin, &b_jet_AntiKt4LCTopo_PhiOrigin);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_MOrigin", &jet_AntiKt4LCTopo_MOrigin, &b_jet_AntiKt4LCTopo_MOrigin);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_BCH_CORR_CELL", &jet_AntiKt4LCTopo_BCH_CORR_CELL, &b_jet_AntiKt4LCTopo_BCH_CORR_CELL);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_BCH_CORR_JET", &jet_AntiKt4LCTopo_BCH_CORR_JET, &b_jet_AntiKt4LCTopo_BCH_CORR_JET);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_SamplingMax", &jet_AntiKt4LCTopo_SamplingMax, &b_jet_AntiKt4LCTopo_SamplingMax);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_fracSamplingMax", &jet_AntiKt4LCTopo_fracSamplingMax, &b_jet_AntiKt4LCTopo_fracSamplingMax);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_isUgly", &jet_AntiKt4LCTopo_isUgly, &b_jet_AntiKt4LCTopo_isUgly);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_isBadLooseMinus", &jet_AntiKt4LCTopo_isBadLooseMinus, &b_jet_AntiKt4LCTopo_isBadLooseMinus);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_emfrac", &jet_AntiKt4LCTopo_emfrac, &b_jet_AntiKt4LCTopo_emfrac);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_emscale_E", &jet_AntiKt4LCTopo_emscale_E, &b_jet_AntiKt4LCTopo_emscale_E);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_emscale_pt", &jet_AntiKt4LCTopo_emscale_pt, &b_jet_AntiKt4LCTopo_emscale_pt);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_emscale_m", &jet_AntiKt4LCTopo_emscale_m, &b_jet_AntiKt4LCTopo_emscale_m);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_emscale_eta", &jet_AntiKt4LCTopo_emscale_eta, &b_jet_AntiKt4LCTopo_emscale_eta);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_emscale_phi", &jet_AntiKt4LCTopo_emscale_phi, &b_jet_AntiKt4LCTopo_emscale_phi);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_ActiveAreaPx", &jet_AntiKt4LCTopo_ActiveAreaPx, &b_jet_AntiKt4LCTopo_ActiveAreaPx);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_ActiveAreaPy", &jet_AntiKt4LCTopo_ActiveAreaPy, &b_jet_AntiKt4LCTopo_ActiveAreaPy);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_ActiveAreaPz", &jet_AntiKt4LCTopo_ActiveAreaPz, &b_jet_AntiKt4LCTopo_ActiveAreaPz);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_ActiveAreaE", &jet_AntiKt4LCTopo_ActiveAreaE, &b_jet_AntiKt4LCTopo_ActiveAreaE);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_jvtxf", &jet_AntiKt4LCTopo_jvtxf, &b_jet_AntiKt4LCTopo_jvtxf);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_constscale_E", &jet_AntiKt4LCTopo_constscale_E, &b_jet_AntiKt4LCTopo_constscale_E);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_constscale_pt", &jet_AntiKt4LCTopo_constscale_pt, &b_jet_AntiKt4LCTopo_constscale_pt);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_constscale_m", &jet_AntiKt4LCTopo_constscale_m, &b_jet_AntiKt4LCTopo_constscale_m);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_constscale_eta", &jet_AntiKt4LCTopo_constscale_eta, &b_jet_AntiKt4LCTopo_constscale_eta);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_constscale_phi", &jet_AntiKt4LCTopo_constscale_phi, &b_jet_AntiKt4LCTopo_constscale_phi);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_flavor_weight_IP3D", &jet_AntiKt4LCTopo_flavor_weight_IP3D, &b_jet_AntiKt4LCTopo_flavor_weight_IP3D);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_flavor_weight_JetFitterCOMBNN", &jet_AntiKt4LCTopo_flavor_weight_JetFitterCOMBNN, &b_jet_AntiKt4LCTopo_flavor_weight_JetFitterCOMBNN);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_flavor_weight_MV1", &jet_AntiKt4LCTopo_flavor_weight_MV1, &b_jet_AntiKt4LCTopo_flavor_weight_MV1);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_flavor_weight_SV0", &jet_AntiKt4LCTopo_flavor_weight_SV0, &b_jet_AntiKt4LCTopo_flavor_weight_SV0);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_flavor_weight_SV1", &jet_AntiKt4LCTopo_flavor_weight_SV1, &b_jet_AntiKt4LCTopo_flavor_weight_SV1);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_flavor_truth_label", &jet_AntiKt4LCTopo_flavor_truth_label, &b_jet_AntiKt4LCTopo_flavor_truth_label);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_flavor_component_jfitcomb_pu", &jet_AntiKt4LCTopo_flavor_component_jfitcomb_pu, &b_jet_AntiKt4LCTopo_flavor_component_jfitcomb_pu);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_flavor_component_jfitcomb_pb", &jet_AntiKt4LCTopo_flavor_component_jfitcomb_pb, &b_jet_AntiKt4LCTopo_flavor_component_jfitcomb_pb);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_flavor_component_jfitcomb_pc", &jet_AntiKt4LCTopo_flavor_component_jfitcomb_pc, &b_jet_AntiKt4LCTopo_flavor_component_jfitcomb_pc);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_nTrk_pv0_1GeV", &jet_AntiKt4LCTopo_nTrk_pv0_1GeV, &b_jet_AntiKt4LCTopo_nTrk_pv0_1GeV);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_trackWIDTH_pv0_1GeV", &jet_AntiKt4LCTopo_trackWIDTH_pv0_1GeV, &b_jet_AntiKt4LCTopo_trackWIDTH_pv0_1GeV);
    fRealChain->SetBranchAddress("jet_AntiKt4LCTopo_TrackAssoc_index", &jet_AntiKt4LCTopo_TrackAssoc_index, &b_jet_AntiKt4LCTopo_TrackAssoc_index);
    fRealChain->SetBranchAddress("AntiKt4Truth_n", &AntiKt4Truth_n, &b_AntiKt4Truth_n);
    fRealChain->SetBranchAddress("AntiKt4Truth_E", &AntiKt4Truth_E, &b_AntiKt4Truth_E);
    fRealChain->SetBranchAddress("AntiKt4Truth_pt", &AntiKt4Truth_pt, &b_AntiKt4Truth_pt);
    fRealChain->SetBranchAddress("AntiKt4Truth_eta", &AntiKt4Truth_eta, &b_AntiKt4Truth_eta);
    fRealChain->SetBranchAddress("AntiKt4Truth_phi", &AntiKt4Truth_phi, &b_AntiKt4Truth_phi);
    fRealChain->SetBranchAddress("top_hfor_type", &top_hfor_type, &b_top_hfor_type);
    fRealChain->SetBranchAddress("cl_lc_pt", &cl_lc_pt, &b_cl_lc_pt);
    fRealChain->SetBranchAddress("cl_lc_eta", &cl_lc_eta, &b_cl_lc_eta);
    fRealChain->SetBranchAddress("cl_lc_phi", &cl_lc_phi, &b_cl_lc_phi);
    fRealChain->SetBranchAddress("trk_n", &trk_n, &b_trk_n);
    fRealChain->SetBranchAddress("trk_pt", &trk_pt, &b_trk_pt);
    fRealChain->SetBranchAddress("trk_eta", &trk_eta, &b_trk_eta);
    fRealChain->SetBranchAddress("trk_d0_wrtPV", &trk_d0_wrtPV, &b_trk_d0_wrtPV);
    fRealChain->SetBranchAddress("trk_z0_wrtPV", &trk_z0_wrtPV, &b_trk_z0_wrtPV);
    fRealChain->SetBranchAddress("trk_phi_wrtPV", &trk_phi_wrtPV, &b_trk_phi_wrtPV);
    fRealChain->SetBranchAddress("trk_theta_wrtPV", &trk_theta_wrtPV, &b_trk_theta_wrtPV);
    fRealChain->SetBranchAddress("trk_qoverp_wrtPV", &trk_qoverp_wrtPV, &b_trk_qoverp_wrtPV);
    fRealChain->SetBranchAddress("trk_nPixHits", &trk_nPixHits, &b_trk_nPixHits);
    fRealChain->SetBranchAddress("trk_nSCTHits", &trk_nSCTHits, &b_trk_nSCTHits);
    fRealChain->SetBranchAddress("trkpt4_pt", &trkpt4_pt, &b_trkpt4_pt);
    fRealChain->SetBranchAddress("trkpt4_eta", &trkpt4_eta, &b_trkpt4_eta);
    fRealChain->SetBranchAddress("trkpt4_phi_wrtPV", &trkpt4_phi_wrtPV, &b_trkpt4_phi_wrtPV);
    fRealChain->SetBranchAddress("trkpt4_err_qoverp_wrtPV", &trkpt4_err_qoverp_wrtPV, &b_trkpt4_err_qoverp_wrtPV);
    fRealChain->SetBranchAddress("vxp_n", &vxp_n, &b_vxp_n);
    fRealChain->SetBranchAddress("vxp_z", &vxp_z, &b_vxp_z);
    fRealChain->SetBranchAddress("vxp_type", &vxp_type, &b_vxp_type);
    fRealChain->SetBranchAddress("vxp_nTracks", &vxp_nTracks, &b_vxp_nTracks);
    fRealChain->SetBranchAddress("mc_n", &mc_n, &b_mc_n);
    fRealChain->SetBranchAddress("mc_pt", &mc_pt, &b_mc_pt);
    fRealChain->SetBranchAddress("mc_m", &mc_m, &b_mc_m);
    fRealChain->SetBranchAddress("mc_eta", &mc_eta, &b_mc_eta);
    fRealChain->SetBranchAddress("mc_phi", &mc_phi, &b_mc_phi);
    fRealChain->SetBranchAddress("mc_status", &mc_status, &b_mc_status);
    fRealChain->SetBranchAddress("mc_barcode", &mc_barcode, &b_mc_barcode);
    fRealChain->SetBranchAddress("mc_pdgId", &mc_pdgId, &b_mc_pdgId);
    fRealChain->SetBranchAddress("mc_charge", &mc_charge, &b_mc_charge);
    fRealChain->SetBranchAddress("mc_child_index", &mc_child_index, &b_mc_child_index);
    fRealChain->SetBranchAddress("mc_parent_index", &mc_parent_index, &b_mc_parent_index);
    fRealChain->SetBranchAddress("mcVx_n", &mcVx_n, &b_mcVx_n);
    fRealChain->SetBranchAddress("mcVx_z", &mcVx_z, &b_mcVx_z);
    fRealChain->SetBranchAddress("muonTruth_barcode", &muonTruth_barcode, &b_muonTruth_barcode);
    fRealChain->SetBranchAddress("muonTruth_type", &muonTruth_type, &b_muonTruth_type);
    fRealChain->SetBranchAddress("muonTruth_origin", &muonTruth_origin, &b_muonTruth_origin);
    fRealChain->SetBranchAddress("mcevt_weight", &mcevt_weight, &b_mcevt_weight);
    fRealChain->SetBranchAddress("trig_EF_el_n", &trig_EF_el_n, &b_trig_EF_el_n);
    fRealChain->SetBranchAddress("trig_EF_el_eta", &trig_EF_el_eta, &b_trig_EF_el_eta);
    fRealChain->SetBranchAddress("trig_EF_el_phi", &trig_EF_el_phi, &b_trig_EF_el_phi);
    fRealChain->SetBranchAddress("trig_EF_trigmuonef_n", &trig_EF_trigmuonef_n, &b_trig_EF_trigmuonef_n);
    fRealChain->SetBranchAddress("trig_EF_trigmuonef_track_n", &trig_EF_trigmuonef_track_n, &b_trig_EF_trigmuonef_track_n);
    fRealChain->SetBranchAddress("trig_EF_trigmuonef_track_CB_pt", &trig_EF_trigmuonef_track_CB_pt, &b_trig_EF_trigmuonef_track_CB_pt);
    fRealChain->SetBranchAddress("trig_EF_trigmuonef_track_CB_eta", &trig_EF_trigmuonef_track_CB_eta, &b_trig_EF_trigmuonef_track_CB_eta);
    fRealChain->SetBranchAddress("trig_EF_trigmuonef_track_CB_phi", &trig_EF_trigmuonef_track_CB_phi, &b_trig_EF_trigmuonef_track_CB_phi);
    fRealChain->SetBranchAddress("GSF_trk_trk_index", &GSF_trk_trk_index, &b_GSF_trk_trk_index);
  }


  void Reader::Loop(const char* out_file_name)
  {
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
  
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (Cut(ientry) < 0) continue;
    
    }
  }

  void Reader::Loop()
  {
    std::cout << "Empty loop function" << std::endl;
  }

  void Reader::Loop(const char *filename, const char* treename)
  {
    std::cout << "Reader::Loop(const char*, const char*) does nothing! Need to overwrite it!" << std::endl;
  }
    
} // namespace mAIDA
