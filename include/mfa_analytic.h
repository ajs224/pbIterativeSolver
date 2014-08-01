#ifndef MFA_ANALYTIC_H
#define MFA_ANALYTIC_H
#include <string>


namespace mfaAnalytic
{
    enum kernelTypes { constant, additive, multiplicative, continuum, freemolecular, kinetic, shearlinear, shearnonlinear, settling, inertiasettling, berry, condensation, spmtest};

  extern kernelTypes kernelType;
    
  const int noMoments=4; // Number of moments to compute
  const std::string dataDir="data/"; // Output directory
  
} //namespace mfaAnalytic


#endif
