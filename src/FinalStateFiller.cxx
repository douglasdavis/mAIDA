/** @file FinalStateFiller.cxx
 *  @brief mAIDA::FinalStateFiller class implementation
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#include "FinalStateFiller.h"

mAIDA::FinalStateFiller::FinalStateFiller() {}

mAIDA::FinalStateFiller::~FinalStateFiller() {}

void mAIDA::FinalStateFiller::Loop()
{
  //
}

void mAIDA::FinalStateFiller::Use_trilepton()
{
  _trilepton  = true;
  _fourlepton = false;
  _osdilepton = false;
  _ssdilepton = false;
}

void mAIDA::FinalStateFiller::Use_fourlepton()
{
  _trilepton  = false;
  _fourlepton = true;
  _osdilepton = false;
  _ssdilepton = false;
}

void mAIDA::FinalStateFiller::Use_osdilepton()
{
  _trilepton  = false;
  _fourlepton = false;
  _osdilepton = true;
  _ssdilepton = false;
}

void mAIDA::FinalStateFiller::Use_ssdilepton()
{
  _trilepton  = false;
  _fourlepton = false;
  _osdilepton = false;
  _ssdilepton = true;
}
