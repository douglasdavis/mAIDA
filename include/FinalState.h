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

    std::string                _InteractionType;
    std::vector<mAIDA::Jet>    _Jets;
    std::vector<mAIDA::Lepton> _Leptons;
    float                      _MET;
    
    ClassDef(FinalState,2);
    
  public:

    FinalState();
    virtual ~FinalState();

    void SetInteractionType(const std::string name);
    void AddLepton(const mAIDA::Lepton& lepton);
    void AddJet(const mAIDA::Jet& jet);
    void ClearVecs();
    void Set_MET(const float i);
    
    const std::string&                InteractionType() const;
    const std::vector<mAIDA::Lepton>& Leptons()          const;
    const std::vector<mAIDA::Jet>&    Jets()             const;

    float MET() const;
    
  };

}

inline void mAIDA::FinalState::SetInteractionType(const std::string name) { _InteractionType = name;         }
inline void mAIDA::FinalState::AddLepton(const mAIDA::Lepton& lepton)     { _Leptons.push_back(lepton);      }
inline void mAIDA::FinalState::AddJet(const mAIDA::Jet& jet)              { _Jets.push_back(jet);            }
inline void mAIDA::FinalState::ClearVecs()                                { _Leptons.clear(); _Jets.clear(); }
inline void mAIDA::FinalState::Set_MET(const float i)                     { _MET = i;                        }

inline const std::string&                mAIDA::FinalState::InteractionType() const { return _InteractionType; }
inline const std::vector<mAIDA::Lepton>& mAIDA::FinalState::Leptons()         const { return _Leptons;         }
inline const std::vector<mAIDA::Jet>&    mAIDA::FinalState::Jets()            const { return _Jets;            }
inline       float                       mAIDA::FinalState::MET()             const { return _MET;             }

#endif //* mAIDA_FinalState_h *//
