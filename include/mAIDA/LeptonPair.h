/** @file LeptonPair.h
 *  @brief mAIDA::LeptonPair class header
 *  @class mAIDA::LeptonPair
 *  @brief a reconstructed Lepton Pair 
 *
 *  This class describes the properties
 *  of a reconstructed Lepton Pair.
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#ifndef mAIDA_LeptonPair_h
#define mAIDA_LeptonPair_h

#include "TLorentzVector.h"
#include "mAIDA/Lepton.h"

namespace mAIDA {

  class LeptonPair {

  private:
  
    Lepton         _lepton_1;
    Lepton         _lepton_2;
    TLorentzVector _four_vector;
    int            _pdg_sum;
    float          _inv_mass;
    bool           _isOS;
    bool           _within_Z;
    bool           _is_ee;
    bool           _is_eu;
    bool           _is_uu;
    
  public:

    LeptonPair(const mAIDA::Lepton& l1, const mAIDA::Lepton& l2);
    virtual ~LeptonPair();

    void SetLeptons(const mAIDA::Lepton& l1, const mAIDA::Lepton& l2);

    void Reload();
    
    const mAIDA::Lepton&  lepton1()     const;
    const mAIDA::Lepton&  lepton2()     const;
    const TLorentzVector& four_vector() const;

    int   pdg_sum()  const;
    float M()        const;
    bool  isOS()     const;
    bool  within_Z() const;
    bool  is_ee()    const;
    bool  is_uu()    const;
    bool  is_eu()    const;    

  };

}

inline const mAIDA::Lepton&  mAIDA::LeptonPair::lepton1()     const { return _lepton_1;    }
inline const mAIDA::Lepton&  mAIDA::LeptonPair::lepton2()     const { return _lepton_2;    }
inline const TLorentzVector& mAIDA::LeptonPair::four_vector() const { return _four_vector; }
inline       int             mAIDA::LeptonPair::pdg_sum()     const { return _pdg_sum;     }
inline       float           mAIDA::LeptonPair::M()           const { return _inv_mass;    }
inline       bool            mAIDA::LeptonPair::isOS()        const { return _isOS;        }
inline       bool            mAIDA::LeptonPair::within_Z()    const { return _within_Z;    } 
inline       bool            mAIDA::LeptonPair::is_ee()       const { return _is_ee;       }
inline       bool            mAIDA::LeptonPair::is_uu()       const { return _is_uu;       }
inline       bool            mAIDA::LeptonPair::is_eu()       const { return _is_eu;       }
 
#endif //* mAIDA_LeptonPair_h *//
