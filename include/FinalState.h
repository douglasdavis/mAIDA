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

    std::vector<mAIDA::Jet>    _Jets;             ///< all passing jets
    std::vector<mAIDA::Lepton> _Leptons;          ///< all passing leptons
    mAIDA::Jet                 _LeadingJet;       ///< highest p_T jet
    mAIDA::Lepton              _LeadingLepton;    ///< highest p_T lepton
    float                      _MET;              ///< Missing E_T

    ClassDef(FinalState,2);
    
  public:

    FinalState();
    virtual ~FinalState();

    void AddLepton(const mAIDA::Lepton& lepton);     //!< add a lepton
    void AddJet(const mAIDA::Jet& jet);              //!< add a jet
    void EvaluateSelf();                             //!< figures out other private variables from other vars
    void ClearVecs();                                //!< clear the jet and lepton vectors
    void Set_MET(const float i);                     //!< set the missing E_T

    const std::vector<mAIDA::Lepton>& Leptons()         const; //!< getter for lepton vector
    const std::vector<mAIDA::Jet>&    Jets()            const; //!< getter for jet vector
    const mAIDA::Lepton&              LeadingLepton()   const; //!< getter for leading lepton
    const mAIDA::Jet&                 LeadingJet()      const; //!< getter for leading jet

    float MET() const;  //!< getter for missing E_T
    
  };

}

inline void mAIDA::FinalState::AddLepton(const mAIDA::Lepton& lepton)     { _Leptons.push_back(lepton);            }
inline void mAIDA::FinalState::AddJet(const mAIDA::Jet& jet)              { _Jets.push_back(jet);                  }
inline void mAIDA::FinalState::ClearVecs()                                { _Leptons.clear(); _Jets.clear();       }
inline void mAIDA::FinalState::Set_MET(const float i)                     { _MET = i;                              }

inline const std::vector<mAIDA::Lepton>& mAIDA::FinalState::Leptons()         const { return _Leptons;         }
inline const std::vector<mAIDA::Jet>&    mAIDA::FinalState::Jets()            const { return _Jets;            }
inline const mAIDA::Lepton&              mAIDA::FinalState::LeadingLepton()   const { return _LeadingLepton;   }
inline const mAIDA::Jet&                 mAIDA::FinalState::LeadingJet()      const { return _LeadingJet;      }
inline       float                       mAIDA::FinalState::MET()             const { return _MET;             }

#endif //* mAIDA_FinalState_h *//
