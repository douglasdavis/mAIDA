/** @file MVASigBkg.h
 *  @brief mAIDA::MVASigBkg class header
 *  @class mAIDA::MVASigBkg
 *  @brief signal background manager
 *
 *  This class provides and easy way to deal
 *  with signal and background trees for use
 *  with TMVA.
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#ifndef mAIDA_MVASigBkg_h
#define mAIDA_MVASigBkg_h

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TMVA/Factory.h"
#include <map>

namespace mAIDA {

  class MVASigBkg : public TObject {

  private:

    TFile                        *_sig_file;
    TTree                        *_sig_tree;
    std::string                   _sig_name;
    float                         _sig_weight;
    std::map<std::string,TFile*>  _bkg_files;
    std::map<std::string,TTree*>  _bkg_trees;
    std::map<std::string,float>   _bkg_weights;

    ClassDef(MVASigBkg,1);
      
  public:

    MVASigBkg();
    virtual ~MVASigBkg();

    void set_sig(const std::string& name, const char* file, const char* tree, const float weight);
    void add_bkg(const std::string& name, const char* file, const char* tree, const float weight);

    void weight_by_entries();                  //!< weight each sample by the minimum entries (each sample contributes evenly)
    
    void add_bkg_to_factory(TMVA::Factory *f); //!< adds all of the background samples to the TMVA factory
  
    std::vector<TH1F*> hist_set(const std::string& var_name, const char* title, const int n_bins,
				const float x_min, const float x_max, const float divider);

    const std::string&  sig_name()   const;
    TFile*              sig_file()   const;
    TTree*              sig_tree()   const;
    float               sig_weight() const;

    const std::map<std::string,TFile*>& bkg_files()   const;
    const std::map<std::string,TTree*>& bkg_trees()   const;
    const std::map<std::string,float>&  bkg_weights() const;
  
  };

}

inline       TFile*                        mAIDA::MVASigBkg::sig_file()    const { return _sig_file;    }
inline       TTree*                        mAIDA::MVASigBkg::sig_tree()    const { return _sig_tree;    }
inline const std::string&                  mAIDA::MVASigBkg::sig_name()    const { return _sig_name;    }
inline       float                         mAIDA::MVASigBkg::sig_weight()  const { return _sig_weight;  }
inline const std::map<std::string,TFile*>& mAIDA::MVASigBkg::bkg_files()   const { return _bkg_files;   }
inline const std::map<std::string,TTree*>& mAIDA::MVASigBkg::bkg_trees()   const { return _bkg_trees;   }
inline const std::map<std::string,float>&  mAIDA::MVASigBkg::bkg_weights() const { return _bkg_weights; }

#endif /* mAIDA_MVASigBkg_h */
