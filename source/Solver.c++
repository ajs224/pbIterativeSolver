/* 
 * File:   solver.cpp
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

Solver::Solver() {
}

Solver::Solver(const Solver& orig) {  
}

Solver::~Solver() {
  
    // Close files
    outputFile.close();
    momentsFile.close();
    delete kernel;
    
   for(unsigned long int i = 0; i < N; ++i)
   {
        delete [] precalculatedK[i];
    }
    delete [] precalculatedK; 
    
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
    inDistName = "delta";
    coagOn = true;
    numberDensityRep = true;
    maxRes = 0e0; // maximum residual tolerance

    alpha = 0e0;
    beta = alpha;
    
    noCells = 1;
    gridLength = 0e0;
    u = 0e0;


    // if ((argc == 1) || (strcmp(argv[1], "--help") == 0)) {

    //     //cout << "This is the help message" << endl;
    //     cout << "Usage: " << argv[0] << " <flags>" << endl << endl;
    //     cout << "where <flags> is one or more of:" << endl << endl;
        
    //     cout << "\t" << "-p" << "\t\t" << "power p, appearing in the maximum cluster size, N=2^p (default is 16)" << endl;
    //     cout << "\t" << "-loops" << "\t\t" << "Can sometimes improve the convergence by doing more than log2(N) " << endl;
    //     cout << "\t" << "-iters" << "\t\t" << "do a fixed number of iterations (can't be used with -loops)." << endl;
    //     cout << "\t" << "-res" << "\t\t" << "iterate until residuals in first m0-m3 are less than res" << endl;
    //     cout << "\t\t\titerations (careful not to do too many though! -- default is 4)" << endl;
    //     cout << "\t" << "-mass" << "\t\t" << "Solves the PBE in mass flow form for more direct comparison with" << endl;
    //     cout << "\t\t\tstochastic algorithms (default is in terms of number density)" << endl;
    //     cout << "\t\t\tN.B. In this case we expect m0=1, otherwise we expect m1=1 (useful convergence check)" << endl;
    //     cout << "\t" << "-nin <distribution>" << "\t" << "m_in distribution, where <distribution> is one of:" << endl << endl;
    //     cout << "\t\t" << "mono" << "\t\t" << "inflowing particles have a mono-dispersed (delta) distribution (default)" << endl;
    //     cout << "\t\t" << "uniform" << "\t\t" << "inflowing particles have a uniform distribution" << endl;
    //     cout << "\t" << "-k <type>" << "\t" << "kernel type, where <type> is one of:" << endl << endl;
    //     cout << "\t\t" << "constant" << "\t\t" << "constant kernel (default)" << endl;
    //     cout << "\t\t" << "additive" << "\t\t" << "additive" << endl;
    //     cout << "\t\t" << "multiplicative" << "\t\t" << "multiplicative" << endl;
    //     cout << "\t\t" << "continuum" << "\t\t" << "Brownian motion (continuum regime)" << endl;
    //     cout << "\t\t" << "freemolecular" << "\t\t" << "Brownian motion (free molecular regime)" << endl;
    //     cout << "\t\t" << "kinetic" << "\t\t\t" << "Based on kinetic theory" << endl;
    //     cout << "\t\t" << "shearlinear" << "\t\t" << "Shear (linear velocity profile)" << endl;
    //     cout << "\t\t" << "shearnonlinear" << "\t\t" << "Shear (nonlinear velocity profile)" << endl;
    //     cout << "\t\t" << "settling" << "\t\t" << "Gravitational settling" << endl;
    //     cout << "\t\t" << "inertiasettling" << "\t\t" << "Inertia and gravitational settling" << endl;
    //     cout << "\t\t" << "berry" << "\t\t\t" << "Analytic approximation of Berry's kernel" << endl;
    //     cout << "\t\t" << "condensation" << "\t\t" << "Condensation and/or branched-chain polymerisation" << endl;
    //     cout << "\t\t" << "spmtest" << "\t\t\t" << "Kernel used to test the Single Particle Method (SPM)" << endl;
    //     cout << endl<< endl;

    //     cout << "For a zero-dimensional reactor, provide:";
    //     cout << "\t" << "-alpha" << "\t\t" << "inflow factor" << endl;
    //     cout << "\t" << "-beta" << "\t\t" << "outflow factor (=alpha if omitted)" << endl;
    //     cout << endl<< endl;

    //     cout << "For a quasi 1D reactor, provide:";
    //     cout << "\t" << "-cells" << "\t\t" << "number of cells" << endl;
    //     cout << "\t" << "-length" << "\t\t" << "length of domain in x direction" << endl;
    //     cout << "\t" << "-u" << "\t\t" << "uniform velocity in x direction" << endl;
    //     cout << endl<< endl;

    //     cout << "0D Examples:" << endl << endl;
    //     cout << "* To run with inflow rate=outflow rate=1, const kernel, 16 outer loops and a max cluster size of 2^10 use:" << endl;
    //     cout << "\ttime " << argv[0] << " -alpha 1 -loops 16 -p 10" << endl;
    //     cout << "* To run with the additive kernel and default in/outflow rates use:" << endl;
    //     cout << "\ttime " << argv[0] << " -k additive -loops 256 -p 20" << endl;
    //     cout << "* In order to achieve convergence with more complicated kernels lower the inflow rate:" << endl;
    //     cout << "\ttime " << argv[0] << " -alpha 0.1 -k multiplicative -loops 64 -p 16" << endl;
    //     cout << "\ttime " << argv[0] << " -alpha 0.05 -k freemolecular -loops 64 -p 16" << endl;
    //     cout << "* To run with a constant kernel, with a max cluster size of 16=2^4, with a max residual in all of m0-m3 of 1e-6:" << endl;
    //     cout << "\t(time " << argv[0] << " -alpha 0.1 -k constant -res 1e-10 -p 4 -mass) |& tee run.log" << endl;

    //     cout << "* To run solve the Cauchy problem only (no coagulation), with inflow rate of 0.1, outflow rate of 0.2, a max cluster size of 16=2^4, with a max residual in all of m0-m3 of 1e-10 in mass flow form:" << endl;
    //     cout << "\t(time " << argv[0] << " -alpha 0.1 -beta 0.2 -res 1e-10 -p 16 -mass -nocoag) |& tee run.log" << endl;

    //     cout << "* To run with the continuum kernel, with inflow rate of 0.1, outflow rate of 0.2, a max cluster size of 16=2^4, with a max residual in all of m0-m3 of 1e-10 in mass flow form (for comparison with MFA codes):" << endl;
    //     cout << "\t(time " << argv[0] << " -alpha 0.1 -beta 0.2 -k continuum -res 1e-10 -p 16 -mass) |& tee run.log" << endl;
        
    //     cout << endl<< endl;
    //     cout << "1D Examples:" << endl << endl;
    //     cout << "* To run a reactor of length 1m, with 100 cells and uniform velocity of u=1m/s, constant kernel, a max cluster size of 2^10 with max residual 1e-10 use (in mass flow form):" << endl;
    //     cout << "\ttime " << argv[0] << " -cells 100 -length 1 -u 1 -k constant -p 10 -res 1e-10 -mass"  << endl;
             
        
        
    //     cout << endl<< endl;
    //     cout << "\ttime N.B., you should use one of -loops, -iters, or -res." << endl;
    //     cout << endl;
    //     return 1;
    // }


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
        else if (strcmp(argv[i], "-mass") == 0) {
            // Solves the equation in mass flow form
            numberDensityRep = false;
        }// n_in distribution
        else if (strcmp(argv[i], "-nin") == 0) {
            char *ninDist = argv[++i];
            if (strcmp(ninDist, "mono") == 0) {
                inDist = mono;
                inDistName = "delta";
            } else {
                inDist = uniform;
                inDistName = "uniform";
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
                kernel = new Multiplicative(1.0); //kernelType = multiplicative;
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
                kernel = new Constant(2.0); //kernelType = constant; // actually this is default anyway
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

    /*
    // Find out which kernel type is selected
    switch (kernelType) {
        case continuum:
            kernelName = "continuum";
            break;
        case freemolecular:
            kernelName = "freemolecular";
            break;
        case kinetic:
            kernelName = "kinetic";
            break;
        case shearlinear:
            kernelName = "shearlinear";
            break;
        case shearnonlinear:
            kernelName = "shearnonlinear";
            break;
        case settling:
            kernelName = "settling";
            break;
        case inertiasettling:
            kernelName = "inertiasettling";
            break;
        case berry:
            kernelName = "berry";
            break;
        case condensation:
            kernelName = "condensation";
            break;
            // Analytic kernels
        case additive:
            kernelName = "additive";
            break;
        case multiplicative:
            kernelName = "multiplicative";
            break;
        case spmtest:
            kernelName = "spmtest";
            break;
        default: // constant kernel
            kernelName = "constant";
    }

    if (!coagOn)
        kernelName = "nocoag";
    */

    //const int L=outerItLoops*floor(log2(N)); // Number of iterations to perform
    if (L == 0 && maxRes == 0e0) {
        L = outerItLoops*p;
    }

    N = pow(2, p); // Max particle size, i.e., i<N in n_i. # of particles is sum_i n_i
    // I choose a power of 2, because for pure coagulations the cluster sizes double with each iteration
    // so we can't do more than log2(N)=p iterations before gelation occurs.
       
    if (alpha == 0 && beta == 0 && noCells == 1 && gridLength == 0 && u == 0)
    {
        cout << "Must provide alpha and beta (0D) or noCells, length and u (1D)." << endl;
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
        cout << kernelName << " kernel selected." << endl;
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
    precalculatedK = new double*[N];
    for(unsigned long i=1;i<=N;i++) // Loop over N particle sizes
    {
        precalculatedK[i] = new double[N];
    }
      
    for(unsigned long i=1;i<=N;i++) // Loop over N particle sizes
    {
        for(unsigned long j=i;j<=N;j++) // Loop over N particle sizes
        {
            //if 
            precalculatedK[i][j] = kernel->k(i,j);
            if(i != j)
                precalculatedK[j][i] = precalculatedK[i][j];

        }
    }
    /*
    for(unsigned long i=1;i<=N;i++) // Loop over N particle sizes
    {
        for(unsigned long j=1;j<=N;j++) // Loop over N particle sizes
        {
            std::cout << "(" << i << ", " << j<< ") = " << precalculatedK[i][j]<< " ";
        }
        std::cout << std::endl;
    }
    */
}
