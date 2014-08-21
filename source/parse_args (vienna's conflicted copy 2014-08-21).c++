#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "mfa_params.h" // Needed for kernelType
#include "mfa_functions.h"

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
	      double & maxRes)
{

  using namespace std;
  using namespace mfaAnalytic;

  if ((argc == 1) || (strcmp(argv[1], "--help") == 0))
    {

      //cout << "This is the help message" << endl;
      cout << "Usage: "<< argv[0] << " <flags>" << endl << endl;
      cout << "where <flags> is one or more of:" << endl << endl;
      cout << "\t" << "-alpha" << "\t\t" << "inflow factor (default is 1/10)" << endl;
      cout << "\t" << "-beta" << "\t\t" << "outflow factor (=alpha if omitted)" << endl;
      cout << "\t" << "-p" << "\t\t" << "power p, appearing in the maximum cluster size, N=2^p (default is 16)" << endl;
      cout << "\t" << "-loops" << "\t\t" << "Can sometimes improve the convergence by doing more than log2(N) " << endl;
      cout << "\t" << "-iters" << "\t\t" << "do a fixed number of iterations (can't be used with -loops)." << endl;
      cout << "\t" << "-res" << "\t\t" << "iterate until residuals in first m0-m3 are less than res" << endl;
      cout << "\t\t\titerations (careful not to do too many though! -- default is 4)" << endl;
      cout << "\t" << "-mass" << "\t\t" << "Solves the PBE in mass flow form for more direct comparison with" << endl;
      cout << "\t\t\tstochastic algorithms (default is in terms of number density)" << endl;
      cout << "\t\t\tN.B. In this case we expect m0=1, otherwise we expect m1=1 (useful convergence check)" << endl;
      cout << "\t" << "-nin <distribution>" << "\t" << "m_in distribution, where <distribution> is one of:" << endl << endl;
      cout << "\t\t" << "mono" << "\t\t" << "inflowing particles have a mono-dispersed (delta) distribution (default)" << endl;
      cout << "\t\t" << "uniform" << "\t\t" << "inflowing particles have a uniform distribution" << endl;
      cout << "\t" << "-k <type>" << "\t" << "kernel type, where <type> is one of:" << endl << endl;
      cout << "\t\t" << "constant" << "\t\t" << "constant kernel (default)" << endl;
      cout << "\t\t" << "additive" << "\t\t" << "additive" << endl;
      cout << "\t\t" << "multiplicative" << "\t\t" << "multiplicative" << endl;
      cout << "\t\t" << "continuum" << "\t\t" << "Brownian motion (continuum regime)" << endl;
      cout << "\t\t" << "freemolecular" << "\t\t" << "Brownian motion (free molecular regime)" << endl;
      cout << "\t\t" << "kinetic" << "\t\t\t" << "Based on kinetic theory" << endl;
      cout << "\t\t" << "shearlinear" << "\t\t" << "Shear (linear velocity profile)" << endl;
      cout << "\t\t" << "shearnonlinear" << "\t\t" << "Shear (nonlinear velocity profile)" << endl;
      cout << "\t\t" << "settling" << "\t\t" << "Gravitational settling" << endl;
      cout << "\t\t" << "inertiasettling" << "\t\t" << "Inertia and gravitational settling" << endl;
      cout << "\t\t" << "berry" << "\t\t\t" << "Analytic approximation of Berry's kernel" << endl;
      cout << "\t\t" << "condensation" << "\t\t" << "Condensation and/or branched-chain polymerisation" << endl;
      cout << "\t\t" << "spmtest" << "\t\t\t" << "Kernel used to test the Single Particle Method (SPM)" << endl;
      cout << endl;
      cout << "Examples:" << endl << endl;
      cout << "* To run with inflow rate=outflow rate=1, const kernel, 16 outer loops and a max cluster size of 2^10 use:" << endl; 
      cout << "\ttime "<< argv[0] << " -alpha 1 -loops 16 -p 10" << endl;
      cout << "* To run with the additive kernel and default in/outflow rates use:" << endl;
      cout << "\ttime "<< argv[0] << " -k additive -loops 256 -p 20" << endl;
      cout << "* In order to achieve convergence with more complicated kernels lower the inflow rate:" << endl;
      cout << "\ttime "<< argv[0] << " -alpha 0.1 -k multiplicative -loops 64 -p 16" << endl;
      cout << "\ttime "<< argv[0] << " -alpha 0.05 -k freemolecular -loops 64 -p 16" << endl;
      cout << "* To run with a constant kernel, with a max cluster size of 16=2^4, with a max residual in all of m0-m3 of 1e-6:" << endl;
      cout << "\t(time "<< argv[0] << " -alpha 0.1 -k constant -res 1e-10 -p 4 -mass) |& tee run.log" << endl;
      
      cout << "* To run solve the Cauchy problem only (no coagulation), with inflow rate of 0.1, outflow rate of 0.2, a max cluster size of 16=2^4, with a max residual in all of m0-m3 of 1e-10 in mass flow form:" << endl;
      cout << "\t(time "<< argv[0] << " -alpha 0.1 -beta 0.2 -res 1e-10 -p 16 -mass -nocoag) |& tee run.log" << endl;
      
      cout << "* To run with the continuum kernel, with inflow rate of 0.1, outflow rate of 0.2, a max cluster size of 16=2^4, with a max residual in all of m0-m3 of 1e-10 in mass flow form (for comparison with MFA codes):" << endl;
      cout << "\t(time "<< argv[0] << " -alpha 0.1 -beta 0.2 -k continuum -res 1e-10 -p 16 -mass) |& tee run.log" << endl;
      cout << endl;
      cout << "\ttime N.B., you should use one of -loops, -iters, or -res." << endl;
      cout << endl;
      return 1;
    }
  
  
  // Process command line arguments
  for (int i=1; i<argc; ++i)
    {
      if (strcmp(argv[i], "-alpha") == 0) 
	{
	  // Read inflow factor
	  alpha = atof(argv[++i]); // default 1/10
	  beta=alpha;
	}
      else if (strcmp(argv[i], "-beta") == 0)
	{
	  // Read outflow factor
	  // If omitted inflow=outflow rate
	  beta = atof(argv[++i]); // default 2
	}
      else if (strcmp(argv[i], "-mass") == 0)
	{
	  // Solves the equation in mass flow form
	  numberDensityRep=false;	  
	}
      // n_in distribution
      else if (strcmp(argv[i], "-nin") == 0)
	{
	  char *ninDist=argv[++i];
	  if (strcmp(ninDist, "mono") == 0)
	    {
	      inDist = mono;
	      inDistName="delta";
	    }
	  else
	    {
	      inDist = uniform;
	      inDistName="uniform";
	    }	  
	}
      // Kernel
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
      else if (strcmp(argv[i], "-p") == 0)
	{
	  // Read p, where the maximum cluster size, N=2^p
	  p = atoi(argv[++i]); // default 16
	}
      else if (strcmp(argv[i], "-loops") == 0)
	{
	  // Read number of outer convergence loops
	  outerItLoops = atoi(argv[++i]); // default 4
	}
      else if (strcmp(argv[i], "-iters") == 0)
	{
	  // Read number of outer convergence loops
	  L = atoi(argv[++i]); //
	}
      else if (strcmp(argv[i], "-res") == 0)
	{
	  // Read number of outer convergence loops
	  maxRes = atof(argv[++i]); //
	  
	}
      else if (strcmp(argv[i], "-nocoag") == 0)
	{
	  // Read number of outer convergence loops
	  coagOn = false; //
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

   if (!coagOn)
    kernelName = "nocoag";
  

  return 0;

}

