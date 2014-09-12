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
  
  inline bool good_el(const int tight, const float pt, const float eta,
		      const float Etcone20, const float ptcone30)
  {
    if ( ( tight > 0 ) &&
	 ( pt > 25.0e3 ) &&
	 ( std::fabs(eta) < 2.47 ) &&
	 !( (std::fabs(eta) > 1.37) && (std::fabs(eta) < 1.52) ) &&
	 ( Etcone20 < 4.0e3 ) && ( ptcone30 < 2.5e3 ) ) {
      return true;
    }
    return false;
  }
  
  inline bool good_mu(const float pt, const float eta,
		      const float Etcone20, const float ptcone30)
  {
    if ( ( pt > 20.0e3 ) &&
	 ( std::fabs(eta) < 2.5 ) &&
	 ( Etcone20 < 4.0e3 ) && ( ptcone30 < 2.5e3 ) ) {
      return true;
    }
    return false;
  }

  inline bool good_jet(const float pt, const float eta)
  {
    if ( ( pt > 30.0e3 ) &&
	 ( std::fabs(eta) < 2.5 ) ) {
      return true;
    }
    return false;
  }

  inline float get_dR(const float phi1, const float phi2,const float eta1, const float eta2)
  {
    return std::sqrt(std::pow(fabs(fabs(fabs(phi1-phi2)-3.14159)-3.14159),2)+std::pow(eta1-eta2,2));
  }
  
  inline float get_dPhi(const float phi1, const float phi2)
  {
    return fabs(fabs(fabs(phi1-phi2)-3.14159)-3.14159);
  }
  
  inline float get_dEta(const float eta1, const float eta2)
  {
    return (eta1 - eta2);
  }
  
  enum pdg_codes {

    k_d    = 1,  k_u    = 2,  k_s    = 3,  k_c    = 4,
    k_b    = 5,  k_t    = 6,  k_el   = 11, k_mu   = 13,
    k_ta   = 15, k_nue  = 12, k_numu = 14, k_nuta = 16,
    k_glu  = 21, k_gam  = 22, k_Z    = 23, k_W    = 24

  };

}

#endif
