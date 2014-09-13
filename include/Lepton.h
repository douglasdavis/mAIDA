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

#ifndef mAIDA_Lepton_h
#define mAIDA_Lepton_h

#include "PhysicsObject.h"

namespace mAIDA {

  class Lepton : public mAIDA::PhysicsObject {

  private:

    int   _pdgId;
    float _charge;
    float _px;
    float _py;
    float _pz;

    ClassDef(Lepton,3);

  public:

    Lepton();
    virtual ~Lepton();

    void Set_pdgId(const int i);     //!< pdgId setter
    void Set_px(const float i);      //!< px setter
    void Set_py(const float i);      //!< py setter
    void Set_pz(const float i);      //!< pz setter
    void Set_charge(const float i);  //!< charge setter
    
    int   pdgId()  const;            //!< pdgId getter
    float px()     const;            //!< px getter
    float py()     const;            //!< py getter
    float pz()     const;            //!< pz getter
    float charge() const;            //!< charge getter

  };

}

inline void mAIDA::Lepton::Set_pdgId(const int i)     { _pdgId  = i; }
inline void mAIDA::Lepton::Set_px(const float i)      { _px     = i; }
inline void mAIDA::Lepton::Set_py(const float i)      { _py     = i; }
inline void mAIDA::Lepton::Set_pz(const float i)      { _pz     = i; }
inline void mAIDA::Lepton::Set_charge(const float i)  { _charge = i; }

inline int   mAIDA::Lepton::pdgId()  const { return _pdgId;  }
inline float mAIDA::Lepton::px()     const { return _px;     }
inline float mAIDA::Lepton::py()     const { return _py;     }
inline float mAIDA::Lepton::pz()     const { return _pz;     }
inline float mAIDA::Lepton::charge() const { return _charge; }

#endif //* mAIDA_Lepton_h *//
