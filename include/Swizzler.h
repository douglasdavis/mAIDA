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
    
    bool _trilepton;
    bool _ssdilepton;
    bool _osdilepton;
    bool _fourlepton;
    
    ClassDef(Swizzler,1);
    
  public:

    Swizzler(const char *fname, const char *tname);
    virtual ~Swizzler();

    void Loop();
    
    void Make_trilepton();
    void Make_ssdilepton();
    void Make_osdilepton();
    void Make_fourlepton();

  };

}

inline void mAIDA::Swizzler::Make_trilepton()
{
  _trilepton  = true;
  _fourlepton = false;
  _osdilepton = false;
  _ssdilepton = false;
}

inline void mAIDA::Swizzler::Make_fourlepton()
{
  _trilepton  = false;
  _fourlepton = true;
  _osdilepton = false;
  _ssdilepton = false;
}

inline void mAIDA::Swizzler::Make_osdilepton()
{
  _trilepton  = false;
  _fourlepton = false;
  _osdilepton = true;
  _ssdilepton = false;
}

inline void mAIDA::Swizzler::Make_ssdilepton()
{
  _trilepton  = false;
  _fourlepton = false;
  _osdilepton = false;
  _ssdilepton = true;
}


#endif
