#ifndef MFA_PARAMS_H
#define MFA_PARAMS_H

#include <vector>
#include <string>

namespace mfaAnalytic
{
  //enum kernelTypes { constant, additive, multiplicative, continuum, freemolecular, kinetic, shearlinear, shearnonlinear, settling, inertiasettling, berry, condensation, spmtest};
  
  enum distributions { mono, uniform };
  
  //extern kernelTypes kernelType; // Read from command line with -k flag.  Default is constant
  
  extern distributions inDist;
   
  extern const int noMoments; // Number of moments to compute
  extern const std::string dataDir; // Output directory
  extern const std::string kernelsDir; // Precalculated kernels directory
} //namespace mfaAnalytic


namespace MFA
{
  
  // MATHEMATICAL CONSTANTS.
  
    extern const double PI;
    extern const double ONE_THIRD;
    extern const double TWO_THIRDS;
    
} //namespace MFA



#endif
