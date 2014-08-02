#include "mfa_params.h"

// Distribution of inflowing particles
double nIn(unsigned long i, unsigned long j)
{
  using namespace mfaAnalytic;
  // Evaluate n_in (here delta_{i1}), i.e., clusters of size 1 flow into the domain
  // if j is always 1, this is a delta distribution (mono-dispersed)
  // if j~U[1,N], this is a uniform distrubtion
  
  //std::cout << "i,j = " << i<<", " <<j<< std::endl;
  
  if(i==j)
    return 1e0;
  else
    return 0e0;    
}
