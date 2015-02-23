/** @file Lepton.cxx
 *  @brief mAIDA::Lepton class implementation
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "mAIDA/Lepton.h"

namespace mAIDA {

  Lepton::Lepton() :
    _pdgId(-999),
    _charge(-9e9)
  {}

  Lepton::~Lepton() {}

}
