#include "Lepton.h"

namespace mAIDA {

  Lepton::Lepton() :
    _pdgId(-999),
    _E(-9e9),
    _pt(-9e9),
    _eta(-9e9),
    _phi(-9e9),
    _charge(-9e9),
    _px(-9e9),
    _py(-9e9),
    _pz(-9e9)
  {}

  Lepton::~Lepton() {}

}
