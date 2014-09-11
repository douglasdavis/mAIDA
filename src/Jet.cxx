/** @file Jet.cxx
 *  @brief mAIDA::Jet class implementation
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "Jet.h"

namespace mAIDA {

  Jet::Jet() :
    _E(-9e9),
    _pt(-9e9),
    _eta(-9e9),
    _phi(-9e9),
    _MV1(-9e9)
  {}
  
  Jet::~Jet() {}
  
}