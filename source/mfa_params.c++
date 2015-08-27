#include "mfa_params.h"


namespace mfaAnalytic
{
  //kernelTypes kernelType; // Read from command line with -k flag.  Default is constant
  distributions inDist = mono;
  
  const int noMoments=4; // Number of moments to compute
  const std::string dataDir="data/"; // Output directory
  const std::string kernelsDir = "/scratch/ajs224/pbIterativeSolver/kernels/"; // Precalculated kernels directory
} //namespace mfaAnalytic


namespace MFA
{

   // MATHEMATICAL CONSTANTS.

    const double PI = 3.1415926535897932384626433832795;
    const double ONE_THIRD  = 3.3333334e-01;
    const double TWO_THIRDS = 6.6666667e-01;

} //namespace MFA

