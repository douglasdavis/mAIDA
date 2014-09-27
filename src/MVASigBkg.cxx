/** @file MVASigBkg.cxx
 *  @brief mAIDA::MVASigBkg class implementation
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "MVASigBkg.h"

namespace mAIDA {

  MVASigBkg::MVASigBkg() {}

  // ___________________________________________________________________________________________________

  void MVASigBkg::set_sig(const std::string& name, const char* file, const char* tree, const float weight)
  {
    _sig_file   = new TFile(file);
    _sig_tree   = dynamic_cast<TTree*>(_sig_file->Get(tree));
    _sig_name   = name;
    _sig_weight = weight;
  }

  // ___________________________________________________________________________________________________

  void MVASigBkg::add_bkg(const std::string& name, const char* file, const char* tree, const float weight)
  {
    _bkg_files[name]   = new TFile(file);
    _bkg_trees[name]   = dynamic_cast<TTree*>(_bkg_files.at(name)->Get(tree));
    _bkg_weights[name] = weight;
  }

  // ___________________________________________________________________________________________________

  void MVASigBkg::add_bkg_to_factory(TMVA::Factory *f)
  {
    for ( auto const& tree : _bkg_trees )
      f->AddBackgroundTree(tree.second,_bkg_weights.at(tree.first));    
  }
  
  // ___________________________________________________________________________________________________

  
  void MVASigBkg::weight_by_entries()
  {
    Long64_t min_entries = 1000000;
    if ( _sig_tree->GetEntries() < min_entries ) min_entries = _sig_tree->GetEntries();
    
    for ( auto const& w : _bkg_trees ) {
      if ( w.second->GetEntries() < min_entries ) {
	min_entries = w.second->GetEntries();
      } else {
	continue;
      }
    }
    
    _sig_weight = (float)min_entries/_sig_tree->GetEntries();
    
    for ( auto const& w : _bkg_weights )
      _bkg_weights[w.first] = (float)min_entries/_bkg_trees[w.first]->GetEntries();
  }
  
  // ___________________________________________________________________________________________________

  std::vector<TH1F*> MVASigBkg::hist_set(const std::string& var_name, const char* title,
					 const int n_bins, const float x_min, const float x_max,
					 const float divider)
  {
    std::vector<TH1F*> hist_vec;

    std::string sig_hist_name = "h_sig_"+var_name;
    TH1F *h_sig = new TH1F(sig_hist_name.c_str(),title,n_bins,x_min,x_max);
    float sigfill;
    _sig_tree->SetBranchAddress(var_name.c_str(),&sigfill);
    for ( auto i = 0; i < _sig_tree->GetEntries(); ++ i ) {
      _sig_tree->GetEntry(i);
      h_sig->Fill(sigfill/divider);
    }
    h_sig->Scale(1./h_sig->Integral());

    hist_vec.push_back(h_sig);

    std::map<std::string,TH1F*> h_bkg;
    for ( auto const &tree : _bkg_trees ) {
      h_bkg[tree.first] = new TH1F(("h_bkg_"+tree.first+"_"+var_name).c_str(),
				   title,n_bins,x_min,x_max);
      float fill_val;
      tree.second->SetBranchAddress(var_name.c_str(),&fill_val);
      for ( auto i = 0; i < tree.second->GetEntries(); ++i ) {
	tree.second->GetEntry(i);
	h_bkg[tree.first]->Fill(fill_val/divider);
      }
      h_bkg[tree.first]->Scale(1/h_bkg[tree.first]->Integral());
      hist_vec.push_back(h_bkg[tree.first]);
    }

    return hist_vec;
  }
    
  // ___________________________________________________________________________________________________
    
  MVASigBkg::~MVASigBkg() {}

  // ___________________________________________________________________________________________________
    
}
