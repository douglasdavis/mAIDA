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

}
