/** @file FinalStateFiller.h
 *  @brief mAIDA::FinalStateFiller class header
 *  @class mAIDA::FinalStateFiller
 *  @brief a class to accumulate and store final states
 *
 *  This class uses the mAIDA::Reader class to loop
 *  over the D3PD physics tree and store the relavent
 *  information as particles making up a final state
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#ifndef mAIDA_FinalStateFiller_h
#define mAIDA_FinalStateFiller_h

#include "FinalState.h"
#include "Reader.h"

namespace mAIDA {

  class FinalStateFiller : public mAIDA::Reader {

  private:

    TFile* _out_file;
    TTree* _out_tree;
    
    bool _trilepton;
    bool _ssdilepton;
    bool _osdilepton;
    bool _fourlepton;
    
    ClassDef(FinalStateFiller,1);
    
  public:

    FinalStateFiller();
    virtual ~FinalStateFiller();

    void Loop();
    
    void Use_trilepton();
    void Use_ssdilepton();
    void Use_osdilepton();
    void Use_fourlepton();

  };

}

#endif
