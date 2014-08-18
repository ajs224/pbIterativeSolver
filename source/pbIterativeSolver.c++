// ---------------------------------------------------------------\
//
// Iterative PBE Solver
// --------------------
// Solve discrete Smoluchowski Eqn with in/outflow and coagulation
// described by constant, additive and multiplicative kernels (analytic)
// in addition to a range of more physically realistic kernels.
//
// A. J. Smith (ajs224@cam.ac.uk)
//
// V4.5
//
//---------------------------------------------------------------/

// To run with inflow rate=outflow rate=1, const kernel, 16 outer loops and a max cluster size of 2^10 use: 
// time ./pbSolverIterative -alpha 1 -k constant -loops 16 -p 10
// To run with the additive kernel and defaul in/outflow rates use:
// time ./pbSolverIterative -k additive -loops 256 -p 20
// In order to achieve convergence with the additive (and multiplicative?) kernels lower the inflow rate:
// time ./pbSolverIterative -alpha 0.1 -k additive -loops 256 -p 10
//time ./pbSolverIterative -alpha 0.1 -k multiplicative -loops 64 -p 16

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "random.h"
#include "mfa_functions.h"
#include "mfa_params.h"
#include "Cell.h"

int main(int argc, char *argv[])
{
  using namespace std;
  using namespace mfaAnalytic;
  using namespace ajsRandom;
  
  bool loadRandState=false; // Generate a new set of seeds
  bool saveRandState=true; // Write the state so we can rewread later
  
  // Declare a Mersenne Twister random number generator
  MTRand mtrand;// = intRand(loadRandState);
  
  unsigned int p=16; // Maximum cluster size N=2^p, default is 16 (over-ridden with the -p flag)
  
  // Sometimes we can improve the convergence by doing more than log2(N) iterations (careful not to do too many though--div 0!)
  unsigned int outerItLoops=4; // Try increasing this to around 256 for non constant kernels (override with -loops flag) 
 
  kernelType=constant; // default kernel type
  
  string kernelName;
  string inDistName="delta";
  double * moments = new double[noMoments];
  double * momentsPrev = new double[noMoments];
  
  unsigned long int L = 0; // no of iterations to perform

  double alpha, beta; // In and outflow factors

  double maxRes = 0e0; // maximum residual tolerance
  int maxIter = 1000;
  double resCutOff = 1e10;

  bool coagOn=true;
  
  // Default values
  alpha=1e-1;
  beta=alpha;

  bool numberDensityRep=true;

  // Output blurb
  cout << endl;
  cout << "Iterative PBE Solver - A. J. Smith (ajs224@cam.ac.uk)" << endl;
  cout << endl;
  cout << "This code solves the discrete Smoluchowski equation with in/outflow" << endl;
  cout << "and coagulation described by constant, additive and multiplicative kernels " << endl;
  cout << "(admitting analytic solutions) in addition to a range of more physically " << endl;
  cout << "realistic kernels (run with --help for additional information)." << endl;
  cout << endl;

  // Parse command line arguments
  if(parseArgs(argc, argv, alpha, beta, numberDensityRep, inDist, inDistName, kernelName, coagOn, p, outerItLoops, L, maxRes))
    {
      // Didn't enter any arguments
      return 0;
    }
  
  const unsigned long N=pow(2,p); // Max particle size, i.e., i<N in n_i. # of particles is sum_i n_i
  // I choose a power of 2, because for pure coagulations the cluster sizes double with each iteration
  // so we can't do more than log2(N)=p iterations before gelation occurs.

  //const int L=outerItLoops*floor(log2(N)); // Number of iterations to perform
  if(L == 0 && maxRes == 0e0)
    {
      L=outerItLoops*floor(log2(N));
    }
  
    // Set up output file streams
  ofstream outputFile;
  ofstream momentsFile;
  //ofstream diamsFile;
 
  string repType;
  if (numberDensityRep)
    repType="_nd";
  else
    repType="_mf";

  string outputFileName=dataDir+kernelName+"_data_";
  string momentsFileName=dataDir+kernelName+"_moments_";
  //string diamsFileName=dataDir+"diameters_";
  string ext=".txt";

  string desc;
  stringstream out;
  
  out << "p" << p << "_alpha" << alpha << "_beta" << beta;
  if (maxRes > 0e0)
    out << "_res" << maxRes;
  else
    out << "_iters" << L;
  out << "_" << inDistName;
    
  desc=out.str();
  
  outputFileName+=desc+repType+ext;
  momentsFileName+=desc+repType+ext;
  //diamsFileName+=desc+ext;

  outputFile.open(outputFileName.c_str(), ios::out);
  momentsFile.open(momentsFileName.c_str(), ios::out);
  //diamsFile.open(diamsFileName.c_str(), ios::out);

  cout << "Running iterative solver (";
  if(numberDensityRep)
    cout << "in terms of number density";
  else
    cout << "in massflow form";
  cout << ") with maximum particle size of " << N;
  if ( L != 0 )
    {
      cout << " for " << L << " iterations.";
    }
  else
    {
      cout << " until steady-state (with a maximum residual tolerance of "<< maxRes << ").";
    }
  cout << endl << endl;

  kernelName[0]=toupper(kernelName[0]); // capitalise
  if(coagOn)
    cout << kernelName << " kernel selected." << endl;
  else
    cout << "Solving Cauchy problem (in/outflow only)" << endl;

  cout << "Inflowing particles are " << inDistName << " distributed." << endl;
  cout << "Inflow rate (1/alpha):" << 1/alpha << endl;
  cout << "Outflow rate (1/beta):" << 1/beta << endl;
  cout << endl;
  
  cout.precision(10);
  cout.width(20);
  //cout.fill('0');
  //cout.setf(ios::showpos); 
  cout.setf(ios::scientific); 
  outputFile.precision(8);
  momentsFile.precision(8);

  // Output header
  cout << "Iter\tm0\t\t\tm1\t\t\tm2\t\t\tm3" << endl;
    
  int l=1;
  bool isRunning  = true;

  double currMaxRes = 0e0;
    
  // Inialise previous moments array which is used for calculating residuals
  for(int moment=0;moment<noMoments;moment++)
    {
      momentsPrev[moment]=0e0;
    }
  

  
  Cell reactorCell = Cell(alpha,beta,N);
  reactorCell.initDist(mono); // Set initial number density distribution 
  reactorCell.initInDist(mono); // Set distribution of inflowing particles

  double d, summa;
    
  // Iterate L times
  while (isRunning)
    {      
      
      currMaxRes = 0e0;
      // Let's compute the moments of the distribution
      for(int moment=0;moment<noMoments;moment++)
	{
	  moments[moment]=0e0;
      	  for(unsigned long i=1;i<=N;i++)
	    {
	      moments[moment]+=pow(i,moment)*reactorCell.getNumDens(i);
	    }
	  
	  double currRes = abs(moments[moment] - momentsPrev[moment]);
	  if(currRes > currMaxRes)
	    currMaxRes = currRes;
	  //cout << "m"<< moment << "residual = " << currRes << endl;
	  
	  momentsPrev[moment] = moments[moment];
	  
	}
  
       
      cout << l << "\t" << moments[0] << "\t" <<moments[1] << "\t" << moments[2] << "\t" << moments[3] << endl;
      momentsFile << l << "\t" << moments[0] << "\t" <<moments[1] << "\t" << moments[2] << "\t" << moments[3] << endl;
      
      // Update old distribution to new distribution
      reactorCell.updateDist(); 
          
      for(unsigned long i=1;i<=N;i++) // Loop over N particle sizes
	{
	  
	  // Compute sums in numerator and denominator
	  d=0e0;
	  for(unsigned long j=1;j<=N;j++)
	    {
	      if(numberDensityRep)
		d+=k(i,j)*reactorCell.getOldNumDens(j);
	      else
		d+=k(i,j)*reactorCell.getOldNumDens(j)/j;
	    }
	  
	  summa=0e0;
	  for(unsigned long j=1;j<=i-1;j++)
	    {
	      //summa+=K[i-j][j]*nold[i-j]*nold[j];
	      if(numberDensityRep)
		summa+=k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j);
	      else
		summa+=k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j)/j;
	    }
	  
	  //cout <<"i="<<i<<", d="<<d<<", summa="<<summa<<endl;


	  if(numberDensityRep)
	    summa*=0.5;

	  if (!coagOn)
	    {
	      d = 0e0;
	      summa =0e0;
	    }
	  
	  /*
	  cout << "n_in = " << n_in << endl;
	  cin.get();
	  cin.sync();
	  */
	    
	  
	  // Iterate baby!
	  //n[i]=(n_in/alpha+0.5*summa)/(1e0/beta+d);
	  reactorCell.setNumDens(i,(reactorCell.getInDist(i)/alpha+summa)/(1e0/beta+d));
	      
	  //n[i]=0.5*summa/d; // Pure coagulation 
	  
	}


      if (L != 0)
	{
	  isRunning = (l<=L);
	}
      else if( currMaxRes < maxRes)
	{
	  // Have reached steady-state with a tolerance of maxRes
	  cout << "Steady-state reached in "<< l << " iterations, with a maximum residual of " << currMaxRes << "!" << endl;
	  isRunning = false;
	}
      
      l++; // Update iteration counter
      
      if (l > maxIter || currMaxRes > resCutOff)
	{
	  cout << "Carried out " << l << " iterations, with a current residual of " << currMaxRes<< ". Check that there is a steady-state solution." << endl;
	  isRunning = false;
	}
	  
	  

      
      
      
    }
  
  
  // Dump steady-state PSD
  for(unsigned long i=1;i<=N;i++) // Loop over N particle sizes
    {
      
      //outputFile << i << "\t" << n[i] << endl;
    }
  
  // Close files
  outputFile.close();
  momentsFile.close();
  
  

  
  delete [] moments;
  moments = NULL; 
  
  //delete [][] K;
  //K=NULL; 
  
  
  return 0;
  
}

