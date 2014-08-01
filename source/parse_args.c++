#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "mfa_params.h" // Needed for kernelType
#include "kernel.h"

using namespace std;
using namespace mfaAnalytic;

int parseArgs(int argc, char *argv[], double & inFactor, double & outFactor, double & tStop, int & N, int & L, std::string & kernelName, bool & coagOn)
{
 
  if ((argc == 1) || (strcmp(argv[1], "--help") == 0))
    {









      
      
      cout << endl;
      
      return 1;
    }
  
  
  // Process command line arguments
  for (int i=1; i<argc; ++i)
    {
      if (strcmp(argv[i], "-alpha") == 0) 
	{
	  // Read inflow factor
	  inFactor = atof(argv[++i]); // default 1/10
	  outFactor=inFactor;
	}
      else if (strcmp(argv[i], "-beta") == 0)
	{
	  // Read outflow factor
	  // If omitted inflow=outflow rate
	  outFactor = atof(argv[++i]); // default 2
	}
      else if (strcmp(argv[i], "-t") == 0)
	{
	  // Read stopping time
	  //tStop = strtod(argv[++i], &pEnd); // default 12.0s
	  tStop = atof(argv[++i]); // default 12.0s
	}
      else if (strcmp(argv[i], "-N") == 0)
	{
	  // Read numer of stochastic particles
	  N = atoi(argv[++i]); // default 1024
	}
      else if (strcmp(argv[i], "-L") == 0)
	{
	  // Read numer of runs
	  L = atoi(argv[++i]); // default 10
	}
      else if (strcmp(argv[i], "-m") == 0)
	{
	  // print moments
	  // does this anyway
	}
      else if (strcmp(argv[i], "-k") == 0)
	{
	  // read constants appearing in multiplicative kernel k(x,y)=c*x^a*y^b
	  // c=argv[++i];
	  // a=argv[++i];
	  // b=argv[++i];

	  // Just read one of the 3 basic kernel types with analytic solution for now
	  char *kArg=argv[++i];
	  if (strcmp(kArg, "additive") == 0)
	    kernelType=additive;
	  else if (strcmp(kArg, "multiplicative") == 0)
	    kernelType=multiplicative;
	  else if (strcmp(kArg, "continuum") == 0)
	    kernelType=continuum;
	  else if (strcmp(kArg, "freemolecular") == 0)
	    kernelType=freemolecular;
	  else if (strcmp(kArg, "kinetic") == 0)
	    kernelType=kinetic;
	  else if (strcmp(kArg, "shearlinear") == 0)
	    kernelType=shearlinear;
	  else if (strcmp(kArg, "shearnonlinear") == 0)
	    kernelType=shearnonlinear;
	  else if (strcmp(kArg, "settling") == 0)
	    kernelType=settling;
	  else if (strcmp(kArg, "inertiasettling") == 0)
	    kernelType=inertiasettling;
	  else if (strcmp(kArg, "berry") == 0)
	    kernelType=berry;
	  else if (strcmp(kArg, "condensation") == 0)
	    kernelType=condensation;
	  else if (strcmp(kArg, "spmtest") == 0)
	    kernelType=spmtest;
	  else
	    kernelType=constant; // actually this is default anyway
	}
      else if (strcmp(argv[i], "-nocoag") == 0)
      	{
	  // In/outflow only
      	  coagOn=false;
      	}
    }
  
  // Find out which kernel type is selected
  switch (kernelType)
    {
    case continuum:
      kernelName="continuum";
      break;
    case freemolecular:
      kernelName="freemolecular";
      break;
    case kinetic:
      kernelName="kinetic";
      break;
    case shearlinear:
      kernelName="shearlinear";
      break;
    case shearnonlinear:
      kernelName="shearnonlinear";
      break;
    case settling:
      kernelName="settling";
      break;
    case inertiasettling:
      kernelName="inertiasettling";
      break;
    case berry:
      kernelName="berry";
      break;
    case condensation:
      kernelName="condensation";
      break;
      // Analytic kernels
    case additive:
      kernelName="additive";
      break;
    case multiplicative:
      kernelName="multiplicative";
      break;
    case spmtest:
      kernelName="spmtest";
      break;
    default: // constant kernel
      kernelName="constant";
    }

  return 0;

}
