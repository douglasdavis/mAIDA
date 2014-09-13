/** @file PhysicsObject.h
 *  @brief mAIDA::PhysicsObject class header
 *  @class mAIDA::PhysicsObject
 *  @brief a reconstructed PhysicsObject (lepton or jet)
 *
 *  This class describes the properties
 *  of a reconstructed PhysicsObject.
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#ifndef mAIDA_PhysicsObject_h
#define mAIDA_PhysicsObject_h

#include "TObject.h"
#include "TLorentzVector.h"

namespace mAIDA {

  class PhysicsObject : public TObject {

  protected:
    
    TLorentzVector _four_vector;

    ClassDef(PhysicsObject,1);
    
  public:

    PhysicsObject();
    virtual ~PhysicsObject();

    void Set_PtEtaPhiE(const float pt,
		       const float eta,
		       const float phi,
		       const float E);         //!< four_vector setter
    
    float E()   const;                         //!< energy getter
    float pt()  const;                         //!< pt getter
    float eta() const;                         //!< eta getter
    float phi() const;                         //!< phi getter

    const TLorentzVector& four_vector() const; //!< four_vector getter
    
  };
  
}

inline void mAIDA::PhysicsObject::Set_PtEtaPhiE(const float pt,
						const float eta,
						const float phi,
						const float E)
{
  _four_vector.SetPtEtaPhiE(pt,eta,phi,E);
}

inline       float           mAIDA::PhysicsObject::E()           const { return _four_vector.E();   }
inline       float           mAIDA::PhysicsObject::pt()          const { return _four_vector.Pt();  }
inline       float           mAIDA::PhysicsObject::eta()         const { return _four_vector.Eta(); }
inline       float           mAIDA::PhysicsObject::phi()         const { return _four_vector.Phi(); }
inline const TLorentzVector& mAIDA::PhysicsObject::four_vector() const { return _four_vector;       }

#endif
