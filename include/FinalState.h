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

  class FinalState {

  private:

    std::string                _interaction_type;
    std::vector<mAIDA::Jet>    _jets;
    std::vector<mAIDA::Lepton> _leptons;

    ClassDef(FinalState,1);
    
  public:

    FinalState();
    virtual ~FinalState();

    void Set_interaction_type(const std::string name);
    void Add_Lepton(const mAIDA::Lepton& lepton);
    void Add_Jet(const mAIDA::Jet& jet);

    const std::string&                interaction_type() const;
    const std::vector<mAIDA::Lepton>& leptons()          const;
    const std::vector<mAIDA::Jet>&    jets()             const;
    
  };

}

inline void mAIDA::FinalState::Set_interaction_type(const std::string name) { _interaction_type = name;   }
inline void mAIDA::FinalState::Add_Lepton(const mAIDA::Lepton& lepton)      { _leptons.push_back(lepton); }
inline void mAIDA::FinalState::Add_Jet(const mAIDA::Jet& jet)               { _jets.push_back(jet);       }

inline const std::string&                mAIDA::FinalState::interaction_type() const { return _interaction_type; }
inline const std::vector<mAIDA::Lepton>& mAIDA::FinalState::leptons()          const { return _leptons;          }
inline const std::vector<mAIDA::Jet>&    mAIDA::FinalState::jets()             const { return _jets;             }

#endif //* mAIDA_FinalState_h *//
