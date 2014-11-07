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
    mAIDA::Lepton              _SecondLepton;     ///< second highest p_T lepton
    float                      _MET;              ///< Missing E_T
    float                      _HT;               ///< sum lepton pt + sum jet pt
    float                      _HT_jets;          ///< sum jet pt
    float                      _HT_leptons;       ///< sum lepton pt
    int                        _pdgIdSum;         ///< sum of Lepton PDG codes
    float                      _chargeSum;        ///< sum of Lepton charges
    
    ClassDef(FinalState,2);
    
  public:

    FinalState();
    virtual ~FinalState();

    void AddLepton(const mAIDA::Lepton& lepton);               //!< add a lepton
    void AddJet(const mAIDA::Jet& jet);                        //!< add a jet
    void EvaluateSelf();                                       //!< calculates some member variables
    void ClearVecs();                                          //!< clear the jet and lepton vectors
    void Set_MET(const float i);                               //!< set the missing E_T
    void Set_HT(const float i);                                //!< set event HT
    void Set_HT_leptons(const float i);                        //!< set event leptons HT
    void Set_HT_jets(const float i);                           //!< set event jets HT
    
    const std::vector<mAIDA::Lepton>& Leptons()         const; //!< getter for lepton vector
    const std::vector<mAIDA::Jet>&    Jets()            const; //!< getter for jet vector
    const mAIDA::Lepton&              LeadingLepton()   const; //!< getter for leading lepton
    const mAIDA::Lepton&              SecondLepton()    const; //!< getter for second lepton
    const mAIDA::Jet&                 LeadingJet()      const; //!< getter for leading jet

    float MET()        const;                                  //!< getter for missing E_T
    float HT()         const;                                  //!< getter for HT
    float HT_leptons() const;                                  //!< getter for HT_leptons
    float HT_jets()    const;                                  //!< getter for HT_jets
    int   pdgIdSum()   const;                                  //!< getter for abs(pdg) sum
    float chargeSum()  const;                                  //!< getter for charge sum
    
  };

}

inline void mAIDA::FinalState::AddLepton(const mAIDA::Lepton& lepton)     { _Leptons.push_back(lepton);        }
inline void mAIDA::FinalState::AddJet(const mAIDA::Jet& jet)              { _Jets.push_back(jet);              }
inline void mAIDA::FinalState::ClearVecs()                                { _Leptons.clear(); _Jets.clear();   }
inline void mAIDA::FinalState::Set_MET(const float i)                     { _MET = i;                          }
inline void mAIDA::FinalState::Set_HT(const float i)                      { _HT  = i;                          }
inline void mAIDA::FinalState::Set_HT_leptons(const float i)              { _HT_leptons = i;                   }
inline void mAIDA::FinalState::Set_HT_jets(const float i)                 { _HT_jets    = i;                   }

inline const std::vector<mAIDA::Lepton>& mAIDA::FinalState::Leptons()         const { return _Leptons;         }
inline const std::vector<mAIDA::Jet>&    mAIDA::FinalState::Jets()            const { return _Jets;            }
inline const mAIDA::Lepton&              mAIDA::FinalState::LeadingLepton()   const { return _LeadingLepton;   }
inline const mAIDA::Lepton&              mAIDA::FinalState::SecondLepton()    const { return _SecondLepton;    }
inline const mAIDA::Jet&                 mAIDA::FinalState::LeadingJet()      const { return _LeadingJet;      }
inline       float                       mAIDA::FinalState::MET()             const { return _MET;             }
inline       float                       mAIDA::FinalState::HT()              const { return _HT;              }
inline       float                       mAIDA::FinalState::HT_leptons()      const { return _HT_leptons;      }
inline       float                       mAIDA::FinalState::HT_jets()         const { return _HT_jets;         }
inline       int                         mAIDA::FinalState::pdgIdSum()        const { return _pdgIdSum;        }
inline       float                       mAIDA::FinalState::chargeSum()       const { return _chargeSum;       }

#endif //* mAIDA_FinalState_h *//
