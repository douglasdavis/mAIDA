/** @file FinalState.h
 *  @brief mAIDA::FinalState class header
 *  @class mAIDA::FinalState
 *  @brief a reconstructed Final State
 *
 *  This class describes the properties
 *  of a reconstructed final state.
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#ifndef mAIDA_FinalState_h
#define mAIDA_FinalState_h

#include <vector>
#include "TObject.h"
#include "Jet.h"
#include "Lepton.h"

namespace mAIDA {

  class FinalState : public TObject {

  private:

    std::string                _InteractionType;  ///< ssdi, osdi, tri, four lepton
    std::vector<mAIDA::Jet>    _Jets;             ///< all passing jets
    std::vector<mAIDA::Lepton> _Leptons;          ///< all passing leptons
    float                      _MET;              ///< Missing E_T
    bool                       _ee;               ///< true if dilepton both electrons
    bool                       _eu;               ///< true if dilepton electron, muon
    bool                       _uu;               ///< true if dilepton both muons
    
    ClassDef(FinalState,2);
    
  public:

    FinalState();
    virtual ~FinalState();

    void SetInteractionType(const std::string name); //!< set the type, ssdi,osdi,tri,four lepton
    void AddLepton(const mAIDA::Lepton& lepton);     //!< add a lepton
    void AddJet(const mAIDA::Jet& jet);              //!< add a jet
    void ClearVecs();                                //!< clear the jet and lepton vectors
    void Set_MET(const float i);                     //!< set the missing E_T
    void Set_ee(const bool i);                       //!< set boolean for 2 electrons
    void Set_eu(const bool i);                       //!< set boolean for electron, muon
    void Set_uu(const bool i);                       //!< set boolean for 2 muons

    const std::string&                InteractionType() const; //!< getter for type
    const std::vector<mAIDA::Lepton>& Leptons()         const; //!< getter for lepton vector
    const std::vector<mAIDA::Jet>&    Jets()            const; //!< getter for jet vector

    float MET() const;  //!< getter for missing E_T
    bool  ee()  const;  //!< getter for 2 electron bool
    bool  eu()  const;  //!< getter for electron, muon bool
    bool  uu()  const;  //!< getter for 2 muon bool
    
  };

}

inline void mAIDA::FinalState::SetInteractionType(const std::string name) { _InteractionType = name;         }
inline void mAIDA::FinalState::AddLepton(const mAIDA::Lepton& lepton)     { _Leptons.push_back(lepton);      }
inline void mAIDA::FinalState::AddJet(const mAIDA::Jet& jet)              { _Jets.push_back(jet);            }
inline void mAIDA::FinalState::ClearVecs()                                { _Leptons.clear(); _Jets.clear(); }
inline void mAIDA::FinalState::Set_MET(const float i)                     { _MET = i;                        }
inline void mAIDA::FinalState::Set_ee(const bool i)                       { _ee  = i;                        }
inline void mAIDA::FinalState::Set_eu(const bool i)                       { _eu  = i;                        }
inline void mAIDA::FinalState::Set_uu(const bool i)                       { _uu  = i;                        }

inline const std::string&                mAIDA::FinalState::InteractionType() const { return _InteractionType; }
inline const std::vector<mAIDA::Lepton>& mAIDA::FinalState::Leptons()         const { return _Leptons;         }
inline const std::vector<mAIDA::Jet>&    mAIDA::FinalState::Jets()            const { return _Jets;            }
inline       float                       mAIDA::FinalState::MET()             const { return _MET;             }
inline       bool                        mAIDA::FinalState::ee()              const { return _ee;              }
inline       bool                        mAIDA::FinalState::eu()              const { return _eu;              }
inline       bool                        mAIDA::FinalState::uu()              const { return _uu;              }


#endif //* mAIDA_FinalState_h *//
