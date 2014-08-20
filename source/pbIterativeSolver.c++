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
#include <cstdlib>
#include <cmath>
#include <vector>

#include "random.h"
#include "mfa_functions.h"
#include "mfa_params.h"
#include "Solver.h"
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
  
  double * moments = new double[noMoments];
  double * momentsPrev = new double[noMoments];
   
  int maxIter = 1000;
  double resCutOff = 1e10;
  
  // Output blurb
  cout << endl;
  cout << "Iterative PBE Solver - A. J. Smith (ajs224@cam.ac.uk)" << endl;
  cout << endl;
  cout << "This code solves the discrete Smoluchowski equation with in/outflow" << endl;
  cout << "and coagulation described by constant, additive and multiplicative kernels " << endl;
  cout << "(admitting analytic solutions) in addition to a range of more physically " << endl;
  cout << "realistic kernels (run with --help for additional information)." << endl;
  cout << endl;

  // Create new single cell simulation
  Solver reactorSolver;
  
  // Parse command line arguments
  if(reactorSolver.parseArgs(argc, argv))
    {
      // Didn't enter any arguments
      return 0;
    }

  reactorSolver.setup();
  
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
   
  Cell reactorCell = Cell(reactorSolver.getIn(),reactorSolver.getOut(),reactorSolver.getN());
  reactorCell.initDist(mono); // Set initial number density distribution 
  reactorCell.initInDist(mono); // Set distribution of inflowing particles

  double birthSum, deathSum;
    
  // Iterate L times
  while (isRunning)
    {      
      currMaxRes = 0e0;
      // Let's compute the moments of the distribution
      for(int moment=0;moment<noMoments;moment++)
	{
	  moments[moment]=0e0;
      	  for(unsigned long i=1;i<=reactorSolver.getN();i++)
	    {
	      moments[moment]+=pow(i,moment)*reactorCell.getNumDens(i);
	    }
	  
	  double currRes = abs(moments[moment] - momentsPrev[moment]);
	  if(currRes > currMaxRes)
	    currMaxRes = currRes;
	  //cout << "m"<< moment << "residual = " << currRes << endl;
	  
	  momentsPrev[moment] = moments[moment];
	  
	}
  
      

      
  
      reactorSolver.writeMoments(l, moments);
                              
      //reactorSolver.getMomentsFile() << l << "\t" << moments[0] << "\t" <<moments[1] << "\t" << moments[2] << "\t" << moments[3] << endl;
      
      // Update old distribution to new distribution
      reactorCell.updateDist(); 
          
      for(unsigned long i=1;i<=reactorSolver.getN();i++) // Loop over N particle sizes
	{
	  
	  // Compute sums in numerator and denominator
	  deathSum=0e0;
	  for(unsigned long j=1;j<=reactorSolver.getN();j++)
	    {
	      if(reactorSolver.isNumberDensityRep())
		deathSum+=k(i,j)*reactorCell.getOldNumDens(j);
	      else
		deathSum+=k(i,j)*reactorCell.getOldNumDens(j)/j;
	    }
	  
	  birthSum=0e0;
	  for(unsigned long j=1;j<=i-1;j++)
	    {
	      //summa+=K[i-j][j]*nold[i-j]*nold[j];
	      if(reactorSolver.isNumberDensityRep())
		birthSum+=k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j);
	      else
		birthSum+=k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j)/j;
	    }

	  if(reactorSolver.isNumberDensityRep())
	    birthSum*=0.5;

	  if (!reactorSolver.isCoagOn())
	    {
	      deathSum = 0e0;
	      birthSum =0e0;
	    }
	  
	  /*
	  cout << "n_in = " << n_in << endl;
	  cin.get();
	  cin.sync();
	  */
	    
	  
	  // Iterate baby!
	  //n[i]=(n_in/alpha+0.5*summa)/(1e0/beta+d);
	  reactorCell.setNumDens(i,(reactorCell.getInDist(i)/reactorSolver.getIn()+birthSum)/(1e0/reactorSolver.getOut()+deathSum));
	      
	  //n[i]=0.5*summa/d; // Pure coagulation 
	  
	}


      if (reactorSolver.getL() != 0)
	{
	  isRunning = (l<=reactorSolver.getL());
	}
      else if( currMaxRes < reactorSolver.getMaxRes())
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
  for(unsigned long i=1;i<=reactorSolver.getN();i++) // Loop over N particle sizes
    {
      
      //reactorSolver.getOutputFile() << i << "\t" << reactorCell.getNumDens(i) << endl;
  /*
       line = cstr(0) + " " + cstr(0) +
               " " + cstr(0)+"\n ";
        file.write(line.c_str(), line.length());
        line = cstr(Rg)+"\n";							//write radius of gyration
*/
  }
  
  
  

  
  delete [] moments;
  moments = NULL; 
  
  //delete [][] K;
  //K=NULL; 
  
  
  return 0;
  
}

