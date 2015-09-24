/* 
 * File:   Solver.c++
 * Author: ajs224
 * 
 * Created on 18 August 2014, 15:02
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "mfa_params.h" // Needed for kernelType
#include "mfa_functions.h"
#include "Solver.h"
#include "Kernel.h"
#include <boost/filesystem.hpp>
#include <exception>      // std::exception, std::terminate

Solver::Solver() {
  precalculatedK = NULL;
}


Solver::Solver(const Solver& orig) {
  precalculatedK = NULL;
}


Solver::~Solver() {

  // Close files
  outputFile.close();
  momentsFile.close();
  
  delete kernel;

  // Check if we've allocated memory for precalculated kernel before deleting it!
  if (precalculatedK != NULL)
    {
      for(unsigned long i=1;i<=N;i++) // Loop over N particle sizes
	delete [] precalculatedK[i];
	
      delete [] precalculatedK;
    }
}


int Solver::parseArgs(int argc, char *argv[]) {
  
  using namespace std;
  using namespace mfaAnalytic;
  
  // Default values
  L = 0; // no of iterations to perform
  p = 16; // Maximum cluster size N=2^p, default is 16 (over-ridden with the -p flag)
  // Sometimes we can improve the convergence by doing more than log2(N) iterations (careful not to do too many though--div 0!)
  outerItLoops = 4; // Try increasing this to around 256 for non constant kernels (override with -loops flag) 
  //kernelType = constant; // default kernel type
  kernel = NULL;
  inDist = mono;
  inDistName = "delta";
  coagOn = true;
  numberDensityRep = true;
  maxRes = 0e0; // maximum residual tolerance
  
  alpha = 0e0;
  beta = alpha;
  
  noCells = 1;
  gridLength = 0e0;
  u = 0e0;
  
  // Process command line arguments
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-alpha") == 0) {
      // Read inflow factor
      alpha = atof(argv[++i]); // default 1/10
      beta = alpha;
    } else if (strcmp(argv[i], "-beta") == 0) {
      // Read outflow factor
      // If omitted inflow=outflow rate
      beta = atof(argv[++i]); // default 2
    } 
    else if (strcmp(argv[i], "-cells") == 0) {
      noCells = atoi(argv[++i]);
    } 
    else if (strcmp(argv[i], "-length") == 0) {
      gridLength = atof(argv[++i]);
    } 
    else if (strcmp(argv[i], "-u") == 0) {
      u = atof(argv[++i]);
    }
	else if (strcmp(argv[i], "-grid") == 0) {
      // Read the grid name
      gridFileName = argv[++i];
		}
    else if (strcmp(argv[i], "-mass") == 0) {
      // Solves the equation in mass flow form
      numberDensityRep = false;
    }// n_in distribution
    else if (strcmp(argv[i], "-nin") == 0) {
      char *ninDist = argv[++i];
      if (strcmp(ninDist, "uniform") == 0) {
	inDist = uniform;
	inDistName = "uniform";
      } else {
	inDist = mono;
	inDistName = "delta";
      }
    }// Kernel
    else if (strcmp(argv[i], "-k") == 0) {
      // read constants appearing in multiplicative kernel k(x,y)=c*x^a*y^b
      // c=argv[++i];
      // a=argv[++i];
      // b=argv[++i];
      
      // Just read one of the 3 basic kernel types with analytic solution for now
      char *kArg = argv[++i];
      if (strcmp(kArg, "additive") == 0)
	kernel = new Additive(1.0); //kernelType = additive;
      else if (strcmp(kArg, "multiplicative") == 0)
	kernel = new Multiplicative(6.25e-2); //kernelType = multiplicative;
      else if (strcmp(kArg, "continuum") == 0)
	kernel = new Continuum(0.1); //kernelType = continuum;
      else if (strcmp(kArg, "freemolecular") == 0)
	kernel = new Freemolecular(0.1); //kernelType = freemolecular;
      else if (strcmp(kArg, "transition") == 0)
	kernel = new Transition(0.1); //kernelType = transition;
      else if (strcmp(kArg, "kinetic") == 0)
	kernel = new Kinetic(1.0); //kernelType = kinetic;
      else if (strcmp(kArg, "shearlinear") == 0)
	kernel = new Shearlinear(1.0); //kernelType = shearlinear;
      else if (strcmp(kArg, "shearnonlinear") == 0)
	kernel = new Shearnonlinear(1.0); //kernelType = shearnonlinear;
      else if (strcmp(kArg, "settling") == 0)
	kernel = new Settling(1.0); //kernelType = settling;
      else if (strcmp(kArg, "inertiasettling") == 0)
	kernel = new Inertiasettling(1.0); //kernelType = inertiasettling;
      else if (strcmp(kArg, "berry") == 0)
	kernel = new Berry(1.0); //kernelType = berry;
      else if (strcmp(kArg, "condensation") == 0)
	kernel = new Condensation(1.0); //kernelType = condensation;
      else if (strcmp(kArg, "spmtest") == 0)
	kernel = new SPMtest(1.0); //kernelType = spmtest;
      else
	kernel = new Constant(1.0); //kernelType = constant; // actually this is default anyway
    } else if (strcmp(argv[i], "-p") == 0) {
      // Read p, where the maximum cluster size, N=2^p
      p = atoi(argv[++i]); // default 16
    } else if (strcmp(argv[i], "-loops") == 0) {
      // Read number of outer convergence loops
      outerItLoops = atoi(argv[++i]); // default 4
    } else if (strcmp(argv[i], "-iters") == 0) {
      // Read number of outer convergence loops
      L = atoi(argv[++i]); //
    } else if (strcmp(argv[i], "-res") == 0) {
      // Read number of outer convergence loops
      maxRes = atof(argv[++i]); //
    } else if (strcmp(argv[i], "-nocoag") == 0) {
      // Read number of outer convergence loops
      coagOn = false; //
      kernel = new Constant(0.0);
    }
  }
  
  //const int L=outerItLoops*floor(log2(N)); // Number of iterations to perform
  if (L == 0 && maxRes == 0e0) {
    L = outerItLoops*p;
  }
  
  N = pow(2, p); // Max particle size, i.e., i<N in n_i. # of particles is sum_i n_i
  // I choose a power of 2, because for pure coagulations the cluster sizes double with each iteration
  // so we can't do more than log2(N)=p iterations before gelation occurs.
  
  if (alpha == 0 && beta == 0 && noCells == 1 && gridLength == 0 && u == 0 && gridFileName == "") 
    {
      cout << "Must provide alpha and beta (0D) or noCells, length and u (1D) or grid (1D CFD grid)." << endl;
      return 1;
    }
  
  return 0;
  
}


void Solver::setup() {

  using namespace mfaAnalytic;
  using namespace std;
  
  string repType;
  if (numberDensityRep)
    repType = "_nd";
  else
    repType = "_mf";
  
  string kernelName = kernel->Name();
  
  outputFileName = dataDir + kernelName + "_data_";
  momentsFileName = dataDir + kernelName + "_moments_";
  
  //string diamsFileName=dataDir+"diameters_";
  string ext = ".txt";
  
  string desc;
  stringstream out;
  out << "p" << p;
  
  if (maxRes > 0e0)
    out << "_res" << maxRes;
  else
    out << "_iters" << L;
  
  out << "_" << inDistName;
  
  cout << "Running iterative solver (";
  if (numberDensityRep)
    cout << "in terms of number density";
  else
    cout << "in massflow form";
  cout << ") with maximum particle size of " << N;
  if (L != 0) {
    cout << " for " << L << " iterations.";
  } else {
    cout << " until steady-state (with a maximum residual tolerance of " << maxRes << ").";
  }
  cout << endl << endl;
  
  kernelName[0] = toupper(kernelName[0]); // capitalise
  
  if (coagOn)
    {
      cout << kernelName << " kernel selected. ";
      cout << "Kernel constant A = " << kernel->getA() << ". " << endl;
    }
  
    else
    cout << "Solving Cauchy problem (in/outflow only / pure transport)" << endl;
  
  
  cout << "Inflowing particles are " << inDistName << " distributed." << endl;
  
  if(alpha != 0 && beta != 0)
    {
      cout << "0D reactor simulation." << endl;
      cout << "Inflow rate (1/alpha):" << 1 / alpha << endl;
      cout << "Outflow rate (1/beta):" << 1 / beta << endl;
      cout << endl;
      out << "_alpha" << alpha << "_beta" << beta;
    }
  else if(gridLength != 0 && u != 0)
    {
      cout << "1D reactor simulation." << endl;
      cout << "Domain length:" << gridLength << " (" << noCells << " cells)" << endl;
      cout << "Uniform velocity u = " << u << " m/s" << endl;
      cout << endl;
      out << "_cells" << noCells << "_length" << gridLength << "_u" << u;
    }
  else if(gridFileName != "")
	{
	  cout << "1D reactor simulation (initialised from CFD grid)." << endl;
	  //cout << "CFD grid: " << gridFileName << endl;
	  //cout << "Domain length:" << gridLength << " (" << noCells << " cells)" << endl;
      //cout << "Uniform velocity u = " << u << " m/s" << endl;
      cout << endl;
      //out << "_cells" << noCells << "_length" << gridLength << "_u" << u;

	  size_t lastdot = gridFileName.find_last_of(".");
	  if (lastdot == std::string::npos)
		out << "_" << gridFileName;
	  else
		out << "_" << gridFileName.substr(0, lastdot); 

	}
  else //if (alpha == 0 && beta == 0 && noCells == 1 && gridLength == 0 && u == 0)
    {
      cout << "Error! Check arguments." << endl;
    }
  
  desc = out.str();
  
  outputFileName += desc + repType + ext;
  momentsFileName += desc + repType + ext;
  //diamsFileName+=desc+ext;
  
  cout << "Saving moments to: " << momentsFileName << "." << endl;
  
  outputFile.open(outputFileName.c_str(), ios::out);
  momentsFile.open(momentsFileName.c_str(), ios::out);
  //diamsFile.open(diamsFileName.c_str(), ios::out);
  
  // Set output precision
  momentsFile.precision(8);
  momentsFile.setf(ios::scientific);
  
  outputFile.precision(8);
  outputFile.setf(ios::scientific);
}


void Solver::writeMoments(int l, double * moments) {
  //std::stringstream out;
  //out << l << "\t" << moments[0] << "\t" << moments[1] << "\t" << moments[2] << "\t" << moments[3] << std::endl;	
  
  //desc=out.str();
  //momentsFile.write(out.str(), 3);
  
  std::cout << l << "\t";
  std::cout.precision(10);
  std::cout.width(20);
  //std::cout.fill('0');
  //cout.setf(ios::showpos); 
  std::cout.setf(std::ios::scientific);
  
  std::cout << moments[0] << "\t" << moments[1] << "\t" << moments[2] << "\t" << moments[3] << std::endl;
  momentsFile << l << "\t" << moments[0] << "\t" << moments[1] << "\t" << moments[2] << "\t" << moments[3] << std::endl;
}


//void Solver::writeFinalMoments(double * moments)
void Solver::writeFinalMoments(int cell, double x, double u, double * moments, int iter, double res)
{
  //std::cout << l << "\t";
  std::cout.precision(10);
  std::cout.setf(std::ios::scientific);
  std::cout << cell << "\t";
  std::cout.width(20);
  std::cout << moments[0] << "\t" << moments[1] << "\t" << moments[2] << "\t" << moments[3];
  std::cout << "\t" << iter << "\t\t" << res << std::endl;
  
  momentsFile.precision(10);
  momentsFile.width(20);
  momentsFile.setf(std::ios::scientific);
  momentsFile << cell << "\t" << x << "\t" << u << "\t";
  momentsFile << moments[0] << "\t" << moments[1] << "\t" << moments[2] << "\t" << moments[3];
  momentsFile << "\t" << iter << "\t" << res << std::endl;
  
  //momentsFile << l << "\t" << moments[0] << "\t" << moments[1] << "\t" << moments[2] << "\t" << moments[3] << std::endl;
}


void Solver::writeOutput(Cell & reactorCell) {
  outputFile.precision(8);
  // Dump steady-state PSD
  for (unsigned long i = 1; i <= N; i++) // Loop over N particle sizes
    {
      outputFile << i << "\t" << reactorCell.getNumDens(i) << std::endl;
    }
}


//double k(unsigned long int i, unsigned long int j){return kernel->k(i,j);}
void Solver::precalculateK()
{
  using namespace mfaAnalytic; // For kernelsDir
    
  // Allocate memory for precalculated kernel data
  precalculatedK = new double*[N+1];
  for(unsigned long i=1;i<=N;i++) // Loop over N particle sizes
    {
      precalculatedK[i] = new double[N+1];
    }
  
  if(!readK()) // if failed to load kernel data
    {
      // Binary kernel data file does not exists - precalculate from scratch
      std::cout << "Precalculating kernel values..." << std::endl;
      for(unsigned long i=1;i<=N;i++) // Loop over N particle sizes
	{
	  for(unsigned long j=i;j<=N;j++) // Loop over N particle sizes
	    {
	      precalculatedK[i][j] = kernel->k(i,j);
	      if(i != j)
		precalculatedK[j][i] = precalculatedK[i][j];
	    }
	}
      std::cout << "Done!" << std::endl;
      
      if(!writeK())
	std::cout << "Not writing precalculated kernel data to binary file." << std::endl;
    } 
}


bool Solver::checkDir()
{
  boost::filesystem::path p(mfaAnalytic::dataDir);
  if (!boost::filesystem::exists(p) || !boost::filesystem::is_directory(p))    // does p actually exist?
    return false;
  else
    return true;
}
  

bool Solver::writeK()
{
  std::stringstream out;
  //std::string kernelsPath = "kernels/";
  
  out << mfaAnalytic::kernelsDir << kernel->Name() << "_" << getN() << ".dat";
  std::string fileName = out.str();

  boost::filesystem::path p(mfaAnalytic::kernelsDir);

  if (!boost::filesystem::exists(p) || !boost::filesystem::is_directory(p))    // does p actually exist?
    {      
      std::cerr << "Directory " << p << " does not exist! ";
      // Abort here
      return false;
    }
  else
    std::cout << "Writing precalculated kernel to " << fileName << std::endl;
    
  double Kij;
    
  std::ofstream kernelData(fileName.c_str(), std::ios::out|std::ios::binary);

  for(unsigned long i=1;i<=N;i++) // Loop over N particle sizes
    {
      for(unsigned long j=i;j<=N;j++) // Loop over N particle sizes
        {
	  Kij = precalculatedK[i][j];
	  kernelData.write( reinterpret_cast <const char*> (&Kij), sizeof( Kij ) );
	}
    }

  kernelData.close();
  
  return true;
  
}


bool Solver::readK()
{
  std::stringstream out;
  //std::string kernelsPath = "kernels/";
  
  out << mfaAnalytic::kernelsDir << kernel->Name() << "_" << getN() << ".dat";
  std::string fileName = out.str();
  
  boost::filesystem::path p(fileName);
  
  if (boost::filesystem::is_regular_file(p))
    {
      std::cout << "Reading precalculated kernel data from " << fileName << "." << std::endl;
      // Read in precalculated kernel data here
      // don't forget K_ij=K_ji for i!=j
      std::ifstream kernelData(fileName.c_str(), std::ios::in|std::ios::binary);
      
      double Kij;

      //std::cout << "Attempting to read kernel data from binary file"  << std::endl;
      for(unsigned long i=1;i<=N;i++) // Loop over N particle sizes
	{
	  for(unsigned long j=i;j<=N;j++) // Loop over N particle sizes
	    {
	      kernelData.read(reinterpret_cast<char*>( &Kij ), sizeof(Kij) );
	      //std::cout <<  Kij << " ";
	      precalculatedK[i][j] = Kij;
	      if(i != j)
		precalculatedK[j][i] = Kij;
	    }
	  //  std::cout << precalculatedK[i][j]  << " ";
	  //std::cout << std::endl;
	}
      
      //std::cout << "Done"  << std::endl;
      kernelData.close();
      return true;
    }
  else // Binary kernel data does not exists
    return false;
}
