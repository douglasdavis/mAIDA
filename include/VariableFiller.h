/** @file VariableFiller.h
 *  @brief mAIDA::VariableFiller class header
 *  @class mAIDA::VariableFiller
 *  @brief a class to accumulate and store variables for MVA
 *
 *  This class reads from the FinalStateFiller output
 *  to formulate a tree of variables to be read by 
 *  an MVA method.
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#ifndef mAIDA_VariableFiller_h
#define mAIDA_VariableFiller_h

#include "TFile.h"
#include "TTree.h"

namespace mAIDA {

  class VariableFiller : public TObject {

  private:

    TFile* _in_file;
    TTree* _in_tree;

    TFile* _out_file;
    TTree* _out_tree;

    // Variables for tree, all caps
    int   IS_EE;
    int   IS_EU;
    int   IS_UU; 
    int   IS_SS;
    int   IS_OS;
    int   IS_TRI;
    int   IS_FOUR;

    float MET;
    int   N_JETS;
    int   N_JETS_B;

    float HT;
    float HT_LEPTONS;
    float HT_JETS;
    float M_LEPTONS;
    float M_JETS;  

    float DR_LL_LJ;
    float DR_LL_SL;
    float DPHI_LL_LJ;
    float DPHI_LL_SL;
    
    ClassDef(VariableFiller,1);

  public:

    VariableFiller(const char* inname, const char* outname)
    {
      _in_file = new TFile(inname);
      _in_tree = (TTree*)_in_file->Get("finalstates");

      _out_file = new TFile(outname,"RECREATE");
      _out_tree = new TTree("mvavartree","mvavartree");

      _out_tree->Branch("IS_EE",  &IS_EE,  "IS_EE/I");
      _out_tree->Branch("IS_EU",  &IS_EU,  "IS_EU/I");
      _out_tree->Branch("IS_UU",  &IS_UU,  "IS_UU/I");
      _out_tree->Branch("IS_SS",  &IS_SS,  "IS_SS/I");
      _out_tree->Branch("IS_OS",  &IS_OS,  "IS_OS/I");
      _out_tree->Branch("IS_TRI", &IS_TRI, "IS_TRI/I");
      _out_tree->Branch("IS_FOUR",&IS_FOUR,"IS_FOUR/I");

      _out_tree->Branch("MET",       &MET,       "MET/F");
      _out_tree->Branch("N_JETS",    &N_JETS,    "N_JETS/I");
      _out_tree->Branch("N_JETS_B",  &N_JETS_B,  "N_JETS_B/I");
      _out_tree->Branch("HT",        &HT,        "HT/F");
      _out_tree->Branch("HT_LEPTONS",&HT_LEPTONS,"HT_LEPTONS/F");
      _out_tree->Branch("HT_JETS",   &HT_JETS,   "HT_JETS/F");
      _out_tree->Branch("M_LEPTONS", &M_LEPTONS, "M_LEPTONS/F");
      _out_tree->Branch("M_JETS",    &M_JETS,    "M_JETS/F");

      _out_tree->Branch("DR_LL_LJ",  &DR_LL_LJ,  "DR_LL_LJ/F");
      _out_tree->Branch("DR_LL_SL",  &DR_LL_SL,  "DR_LL_SL/F");
      _out_tree->Branch("DPHI_LL_LJ",&DPHI_LL_LJ,"DPHI_LL_LJ/F");
      _out_tree->Branch("DPHI_LL_SL",&DPHI_LL_SL,"DPHI_LL_SL/F");
    }
    
    virtual ~VariableFiller() {}

    void Loop();
    
  };

}

#endif
