#ifndef MFA_FUNCS_H
#define MFA_FUNCS_H

#include <string>
#include "mfa_params.h"

// Function headers
//double k(double x, double y); // Collision kernel
double k(unsigned long int i, unsigned long int j); // Collision kernel
double nIn(unsigned long i, unsigned long j); // Distribution of inflowing particles

//double kt(double x, double y); // Majorant kernel
//double* computeMoments(double* diamArray, int noMoments);
double theta(double x, double rate); // Outflow rate
//unsigned long int mIn(unsigned long int i); // Inflowing particle distribution


int parseArgs(int argc, char *argv[],
	      double & alpha,
	      double & beta,
	      bool & numberDensityRep,
	      mfaAnalytic::distributions & inDist,
	      std::string & inDistName,
	      std::string & kernelName,
	      bool & coagOn,
	      unsigned int & p,
	      unsigned int & outerItLoops  ,   
	      unsigned long int & L,
	      double & maxRes);

/*
double interpMon(double evalTime, double t1, double t2, double p1, double p2)
{
  double m = (p2-p1)/(t2-t1);
  return m*(evalTime-t1)+p1;
};
*/

  

#endif
