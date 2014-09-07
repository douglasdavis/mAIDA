/** @file Lepton.h
 *  @brief mAIDA::Lepton class header
 *  @class mAIDA::Lepton
 *  @brief a reconstructed Lepton (mu or e)
 *
 *  This class describes the properties
 *  of a reconstructed Lepton.
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "TObject.h"

#ifndef mAIDA_Lepton_h
#define mAIDA_Lepton_h

namespace mAIDA {

  class Lepton {

  private:

    int   _pdgId;
    float _E;
    float _pt;
    float _eta;
    float _phi;
    float _charge;
    float _px;
    float _py;
    float _pz;
    
    ClassDef(Lepton,1);

  public:

    Lepton();
    virtual ~Lepton();

    void Set_pdgId(const int i);     //!< pdgId setter
    void Set_E(const float i);       //!< E setter
    void Set_pt(const float i);      //!< pt setter
    void Set_eta(const float i);     //!< eta setter
    void Set_phi(const float i);     //!< phi setter
    void Set_px(const float i);      //!< px setter
    void Set_py(const float i);      //!< py setter
    void Set_pz(const float i);      //!< pz setter
    void Set_charge(const float i);  //!< charge setter
    
    int   pdgId()  const;            //!< pdgId getter
    float E()      const;            //!< E getter
    float pt()     const;            //!< pt getter
    float eta()    const;            //!< eta getter
    float phi()    const;            //!< phi getter
    float px()     const;            //!< px getter
    float py()     const;            //!< py getter
    float pz()     const;            //!< pz getter
    float charge() const;            //!< charge getter

  };

}

inline void mAIDA::Lepton::Set_pdgId(const int i)     { _pdgId  = i; }
inline void mAIDA::Lepton::Set_E(const float i)       { _E      = i; }
inline void mAIDA::Lepton::Set_pt(const float i)      { _pt     = i; }
inline void mAIDA::Lepton::Set_eta(const float i)     { _eta    = i; }
inline void mAIDA::Lepton::Set_phi(const float i)     { _phi    = i; }
inline void mAIDA::Lepton::Set_px(const float i)      { _px     = i; }
inline void mAIDA::Lepton::Set_py(const float i)      { _py     = i; }
inline void mAIDA::Lepton::Set_pz(const float i)      { _pz     = i; }
inline void mAIDA::Lepton::Set_charge(const float i)  { _charge = i; }

inline int   mAIDA::Lepton::pdgId()  const { return _pdgId;  }
inline float mAIDA::Lepton::E()      const { return _E;      }
inline float mAIDA::Lepton::pt()     const { return _pt;     }
inline float mAIDA::Lepton::eta()    const { return _eta;    }
inline float mAIDA::Lepton::phi()    const { return _phi;    }
inline float mAIDA::Lepton::px()     const { return _px;     }
inline float mAIDA::Lepton::py()     const { return _py;     }
inline float mAIDA::Lepton::pz()     const { return _pz;     }
inline float mAIDA::Lepton::charge() const { return _charge; }

#endif //* mAIDA_Lepton_h *//
