/** @file LeptonPair.cxx
 *  @brief mAIDA::LeptonPair class implementation
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "mAIDA/LeptonPair.h"
#include <cmath>

mAIDA::LeptonPair::LeptonPair(const mAIDA::Lepton& l1, const mAIDA::Lepton& l2)
{
  _lepton_1    = l1;
  _lepton_2    = l2;
  Reload();
}

mAIDA::LeptonPair::~LeptonPair() {}

void mAIDA::LeptonPair::SetLeptons(const mAIDA::Lepton& l1, const mAIDA::Lepton& l2)
{
  _lepton_1    = l1;
  _lepton_2    = l2;
  Reload();
}

void mAIDA::LeptonPair::Reload()
{
  _pdg_sum     = std::abs(_lepton_1.pdgId()) + std::abs(_lepton_2.pdgId());
  _inv_mass    = (_lepton_1.four_vector()+_lepton_2.four_vector()).M();
  _four_vector = _lepton_1.four_vector() + _lepton_2.four_vector();
  _within_Z    = false;
  _is_ee       = false;
  _is_eu       = false;
  _is_uu       = false;
  
  if ( _lepton_1.charge()*_lepton_2.charge() > 0 ) _isOS = false;
  if ( _lepton_1.charge()*_lepton_2.charge() < 0 ) _isOS = true;
  if ( fabs(_inv_mass - 91.1876e3) < 10e3 ) _within_Z = true;
  if ( _pdg_sum == 22 ) _is_ee = true;
  if ( _pdg_sum == 24 ) _is_eu = true;
  if ( _pdg_sum == 26 ) _is_uu = true;
}
