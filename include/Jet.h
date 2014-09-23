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

#include "PhysicsObject.h"
#include "TObject.h"

namespace mAIDA {

  class Jet : public PhysicsObject {
    
  private:
    
    float _MV1; ///< b-tagging weight

    ClassDef(Jet,3);
    
  public:
    
    Jet();
    virtual ~Jet();

    void Set_MV1(const float i);   //!< MV1 setter
    
    float MV1() const;             //!< MV1 getter

  };
  
}

inline void mAIDA::Jet::Set_MV1(const float i) { _MV1 = i; }

inline float mAIDA::Jet::MV1() const { return _MV1; }

#endif //* mAIDA_Jet_h *//
