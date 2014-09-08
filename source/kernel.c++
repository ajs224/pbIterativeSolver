#include<cmath>
#include <cstdlib>
#include "mfa_params.h"

// Coagulation kernel definition
double k(unsigned long int i, unsigned long int j)
{
  
  using namespace mfaAnalytic;
  
  switch (kernelType)
    {
    case continuum: // Brownian motion (continuum regime)
      return 0.1*(pow(i,1e0/3e0)+pow(j,1e0/3e0))*(pow(i,-1e0/3e0)+pow(j,-1e0/3e0));
      //return (pow(i,1e0/3e0)+pow(j,1e0/3e0))*(pow(i,-1e0/3e0)+pow(j,-1e0/3e0));
      break;
    case freemolecular: // Brownian motion (free molecular regime)
      return pow(pow(i,1e0/3e0)+pow(j,1e0/3e0),2e0)*pow(pow(i,-1e0/3e0)+pow(j,-1e0/3e0),1e0/2e0);
      break;
    case kinetic: // Based on kinetic theory
      return (pow(i,1e0/3e0)+pow(j,1e0/3e0))*pow(i*j,1e0/2e0)*pow(i+j,-3e0/2e0);
      break;
    case shearlinear: // Shear (linear velocity profile)
      return pow(pow(i,1e0/3e0)+pow(j,1e0/3e0),3e0);
      break;
    case shearnonlinear: // Shear (nonlinear velocity profile):
      return pow(pow(i,1e0/3e0)+pow(j,1e0/3e0),7e0/3e0);
      break;
    case settling: // Gravitational settling
      return pow(pow(i,1e0/3e0)+pow(j,1e0/3e0),2e0)*abs(pow(i,1e0/3e0)-pow(j,1e0/3e0));
      break;
    case inertiasettling: // Inertia and gravitational settling
      return pow(pow(i,1e0/3e0)+pow(j,1e0/3e0),2e0)*abs(pow(i,2e0/3e0)-pow(j,2e0/3e0));
      break;
    case berry: // Analytic approximation of Berry's kernel
      return pow(i-j,2e0)*pow(i+j,-1e0);
      break;
    case condensation: // Condensation and/or branched-chain polymerisation
      return (i+2)*(j+2);  // with constant c=2 
      break;
    case additive:
      return i+j;
      break;
    case multiplicative:
      return i*j;
      break;
    case spmtest:
      return pow(i*j,1e0/3e0);
      break;    
    default: // constant kernel
      return 1e0;
    }
}
