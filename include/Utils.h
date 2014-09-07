/** @file Utils.h
 *  @brief mAIDA utility functions
 *
 *  This file contains utility functions for
 *  the rest of the mAIDA classes
 *
 *  @author Douglas Davis < drd25@phy.duke.edu >
 */

#ifndef mAIDA_Utils_h
#define mAIDA_Utils_h

#include <cmath>

namespace mAIDA {

  inline bool good_el(const float pt, const float eta)
  {
    if ( ( pt > 25000.0 ) &&
	 ( std::fabs(eta) < 2.47 ) &&
	 !( (std::fabs(eta) > 1.37) && (std::fabs(eta) < 1.52) ) ) {
      return true;
    }
    return false;
  }

  inline bool good_mu(const float pt, const float eta)
  {
    if ( ( pt > 20000.0 ) &&
	 ( std::fabs(eta) < 2.5 ) ) {
      return true;
    }
    return false;
  }

  inline bool good_jet(const float pt, const float eta)
  {
    if ( ( pt > 30000.0 ) &&
	 ( std::fabs(eta) < 2.5 ) ) {
      return true;
    }
    return false;
  }

  enum pdg_codes {

    k_d    = 1,
    k_u    = 2,
    k_s    = 3,
    k_c    = 4,
    k_b    = 5,
    k_t    = 6,
    k_el   = 11,
    k_mu   = 13,
    k_ta   = 15,
    k_nue  = 12,
    k_numu = 14,
    k_nuta = 16,
    k_glu  = 21,
    k_gam  = 22,
    k_Z    = 23,
    k_W    = 24

  };

}

#endif
