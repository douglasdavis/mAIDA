/** @file FinalState.cxx
 *  @brief mAIDA::FinalState class implementation
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "FinalState.h"

namespace mAIDA {
  
  FinalState::FinalState() :
    _MET(-999),
    _ee(false),
    _eu(false),
    _uu(false)
  {}
  
  FinalState::~FinalState() {}
  
  void FinalState::EvaluateSelf()
  {
    float compare_pt = 0;
    for ( auto const& lepton : _Leptons ) {
      if ( lepton.pt() > compare_pt ) {
	_LeadingLepton = lepton;
	compare_pt = lepton.pt();
      }
    }
    
    compare_pt = 0;
    for ( auto const& jet : _Jets) {
      if ( jet.pt() > compare_pt ) {
	_LeadingJet = jet;
	compare_pt = jet.pt();
      }
    }
  }
  
}
