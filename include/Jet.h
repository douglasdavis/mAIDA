/** @file Jet.h
 *  @brief mAIDA::Jet class header
 *  @class mAIDA::Jet
 *  @brief a reconstructed Jet
 *
 *  This class describes the properties
 *  of a reconstructed Jet.
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#ifndef mAIDA_Jet_h
#define mAIDA_Jet_h

#include "TObject.h"

namespace mAIDA {

  class Jet {
    
  private:
    
    float _E;
    float _pt;
    float _eta;
    float _phi;
    float _MV1;

    ClassDef(Jet,1);
    
  public:
    
    Jet();
    virtual ~Jet();

    void Set_E(const float i);     //!< E setter
    void Set_pt(const float i);    //!< pt setter
    void Set_eta(const float i);   //!< eta setter
    void Set_phi(const float i);   //!< phi setter
    void Set_MV1(const float i);   //!< MV1 setter
    
    float E()   const;             //!< E getter
    float pt()  const;             //!< pt getter
    float eta() const;             //!< eta getter
    float phi() const;             //!< phi getter
    float MV1() const;             //!< MV1 getter

  };
  
}

inline void mAIDA::Jet::Set_E(const float i)   { _E   = i; }
inline void mAIDA::Jet::Set_pt(const float i)  { _pt  = i; }
inline void mAIDA::Jet::Set_eta(const float i) { _eta = i; }
inline void mAIDA::Jet::Set_phi(const float i) { _phi = i; }
inline void mAIDA::Jet::Set_MV1(const float i) { _MV1 = i; }

inline float mAIDA::Jet::E()   const { return _E;   }
inline float mAIDA::Jet::pt()  const { return _pt;  }
inline float mAIDA::Jet::eta() const { return _eta; }
inline float mAIDA::Jet::phi() const { return _phi; }
inline float mAIDA::Jet::MV1() const { return _MV1; }

#endif //* mAIDA_Jet_h *//
