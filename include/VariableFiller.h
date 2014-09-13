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

    ClassDef(VariableFiller,1);

  public:

    VariableFiller(const char* name)
    {
      _in_file = new TFile(name);
      _in_tree = (TTree*)_in_file->Get("finalstates");
    }
    
    virtual ~VariableFiller() {}

    void Loop(const char* fname);
    
  };

}

#endif
