/** @file Swizzler.h
 *  @brief mAIDA::Swizzler class header
 *  @class mAIDA::Swizzler
 *  @brief a class to accumulate and store final states
 *
 *  This class uses the mAIDA::Reader class to loop
 *  over the D3PD physics tree and store the relavent
 *  information as particles making up a final state
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#ifndef mAIDA_Swizzler_h
#define mAIDA_Swizzler_h

#include "FinalState.h"
#include "Reader.h"

namespace mAIDA {

  class Swizzler : public mAIDA::Reader {

  private:

    TFile* _out_file;
    TTree* _out_tree;
    
    ClassDef(Swizzler,2);
    
  public:

    Swizzler(const char *fname, const char *tname);
    virtual ~Swizzler();

    void Loop();
    
  };

}

#endif
