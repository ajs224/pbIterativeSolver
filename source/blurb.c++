#include<blurb.h>
#include<iostream>
#include<string.h>

int blurb(int argc, char *argv[])
{
  using namespace std;
  
  // Output blurb
  cout << endl;
  cout << "Iterative PBE Solver - A. J. Smith (ajs224@cam.ac.uk)" << endl;
  cout << endl;
  cout << "This code solves the discrete Smoluchowski equation with in/outflow" << endl;
  cout << "and coagulation described by constant, additive and multiplicative kernels " << endl;
  cout << "(admitting analytic solutions) in addition to a range of more physically " << endl;
  cout << "realistic kernels (run with --help for additional information)." << endl;
  cout << endl;
  
  if ((argc == 1) || (strcmp(argv[1], "--help") == 0)) {
    
    //cout << "This is the help message" << endl;
    cout << "Usage: " << argv[0] << " <flags>" << endl << endl;
    cout << "where <flags> is one or more of:" << endl << endl;
    
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
    cout << endl<< endl;
    
    cout << "For a zero-dimensional reactor, provide:" << endl << endl;
    cout << "\t" << "-alpha" << "\t\t" << "inflow factor" << endl;
    cout << "\t" << "-beta" << "\t\t" << "outflow factor (=alpha if omitted)" << endl;
    cout << endl;
    
    cout << "For a quasi 1D reactor, provide:" << endl << endl;
    cout << "\t" << "-cells" << "\t\t" << "number of cells" << endl;
    cout << "\t" << "-length" << "\t\t" << "length of domain in x direction" << endl;
    cout << "\t" << "-u" << "\t\t" << "uniform velocity in x direction" << endl;
    cout << endl<< endl;
    
    cout << "0D Examples:" << endl << endl;
    cout << "* To run with inflow rate=outflow rate=1, const kernel, 16 outer loops and a max cluster size of 2^10 use:" << endl;
    cout << "\ttime " << argv[0] << " -alpha 1 -loops 16 -p 10" << endl;
    cout << "* To run with the additive kernel and default in/outflow rates use:" << endl;
    cout << "\ttime " << argv[0] << " -k additive -loops 256 -p 20" << endl;
    cout << "* In order to achieve convergence with more complicated kernels lower the inflow rate:" << endl;
    cout << "\ttime " << argv[0] << " -alpha 0.1 -k multiplicative -loops 64 -p 16" << endl;
    cout << "\ttime " << argv[0] << " -alpha 0.05 -k freemolecular -loops 64 -p 16" << endl;
    cout << "* To run with a constant kernel, with a max cluster size of 16=2^4, with a max residual in all of m0-m3 of 1e-6:" << endl;
    cout << "\t(time " << argv[0] << " -alpha 0.1 -k constant -res 1e-10 -p 4 -mass) |& tee run.log" << endl;
    
    cout << "* To run solve the Cauchy problem only (no coagulation), with inflow rate of 0.1, outflow rate of 0.2, a max cluster size of 16=2^4, with a max residual in all of m0-m3 of 1e-10 in mass flow form:" << endl;
    cout << "\t(time " << argv[0] << " -alpha 0.1 -beta 0.2 -res 1e-10 -p 16 -mass -nocoag) |& tee run.log" << endl;
    
    cout << "* To run with the continuum kernel, with inflow rate of 0.1, outflow rate of 0.2, a max cluster size of 16=2^4, with a max residual in all of m0-m3 of 1e-10 in mass flow form (for comparison with MFA codes):" << endl;
    cout << "\t(time " << argv[0] << " -alpha 0.1 -beta 0.2 -k continuum -res 1e-10 -p 16 -mass) |& tee run.log" << endl;
    
    cout << endl<< endl;
    cout << "1D Examples:" << endl << endl;
    cout << "* To run a reactor of length 1m, with 100 cells and uniform velocity of u=1m/s, constant kernel, a max cluster size of 2^10 with max residual 1e-10 use (in mass flow form):" << endl;
    cout << "\ttime " << argv[0] << " -cells 100 -length 1 -u 1 -k constant -p 10 -res 1e-10 -mass"  << endl;
   
    cout << endl<< endl;
    cout << "\ttime N.B., you should use one of -loops, -iters, or -res." << endl;
    cout << endl;
    return 1;
  }
  else
    return 0; // entered valid command line args
}
