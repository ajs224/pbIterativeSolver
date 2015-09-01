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
// Multicell version of code
// Can implement in two ways:
// 1.) reach steady-state in each cell before marching to the next
// 2.) iterate over all cells, reaching steady-state globally
// Suspect 1 is most efficient - this is correct
//
// * This version of the code precalculates the kernel, which is more effcient for complex kernels
// * If the directory kernelsDir exists and contains previously calculated kernel data in a binary file
// this is read rather the re-calculating, which will speed up repeat calculations with the same number of particles (but say different lengths, numbers of cells or residual tolerances)
//
//---------------------------------------------------------------/

// Example runs:
// To run with inflow rate=outflow rate=1, const kernel, 16 outer loops and a max cluster size of 2^10 use: 
// time ./pbSolverIterative -alpha 1 -k constant -loops 16 -p 10

// To run with the additive kernel and defaul in/outflow rates use:
// time ./pbSolverIterative -k additive -loops 256 -p 20

// In order to achieve convergence with the additive (and multiplicative?) kernels lower the inflow rate:
// time ./pbSolverIterative -alpha 0.1 -k additive -loops 256 -p 10
//time ./pbSolverIterative -alpha 0.1 -k multiplicative -loops 64 -p 16

// Simulate coagulation in the continuum regime in a fluid flowing at 1m/s in a pipe of length 1m (using 100 cells)
//(time ./pbIterativeSolver -cells 100 -length 1 -u 1 -k continuum -res 1e-12 -p 12 -mass -nin mono) &> data/continuum_p12_res1e-12_delta_cells100_length1_u1_mf.log &



/*
 Structure of the code is as follows:
 * The Solver class contains all of the simulation parameters and hold methods for writing moments etc * 
 
 * The Cell class contains all of the data for a single cell (n, moments, etc).
 * A vector of these Cell classes can be strung together to create a quasi-1d reactor
 */

/*
 To do:
 * compare solution with non-steady solution t<->x, u = 1 m/s
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iterator>

#include "blurb.h"
#include "random.h"
#include "mfa_functions.h"
#include "mfa_params.h"
#include "Solver.h"

int main(int argc, char *argv[])
{
  using namespace std;
  using namespace mfaAnalytic;
  using namespace ajsRandom;
  
  bool loadRandState = false; // Generate a new set of seeds
  bool saveRandState = true; // Write the state so we can rewread later
  
  // Declare a Mersenne Twister random number generator - used for uniform distribution of inflowing particles
  MTRand mtrand; // = intRand(loadRandState);
  
  int maxIter = 1000;
  double resCutOff = 1e10;
  
  double currMaxRes;
  bool converged = false; // global convergence
  int cell;
  
  // Output program blurb and check if correct number of command line arguments passed
  if(blurb(argc, argv))
    {
      // Didn't enter any arguments, graciously exit the program
      return 0;
    }
  
  // Valid parameters where entered, call the solver constructor and parse the arguments
  
  // Create new single cell simulation
  Solver reactorSolver;
  reactorSolver.parseArgs(argc, argv);

  // Check if dataDir exists
  if(!reactorSolver.checkDir())
    {
      cerr << "I/O error! The directory " << dataDir << " does not exist!" << endl;
      return 1;
    }

  // Setup up filenames and print summary of parameters    
  reactorSolver.setup();
  
  // Precalculate kernel values (or load from a binary file if it exists)
  reactorSolver.precalculateK();
    
  cout << endl;
  
  double delta_x = reactorSolver.delta_x();
  
  enum convergenceTypes {globalConvergence, cellWise};
  
  //convergenceTypes convergenceType = globalConvergence;
  convergenceTypes convergenceType = cellWise; // As we may expect cellwise is more efficient
  
  if (convergenceType == cellWise) {
    // Output header
    if (reactorSolver.getNoCells() <= 1) // Print 0d reactor header
      cout << "Iter\t\tm0\t\t\tm1\t\t\tm2\t\t\tm3" << endl;
    else // Print quasi-1d reactor header
      cout << "Cell\t\tm0\t\t\tm1\t\t\tm2\t\t\tm3\t\t# iters\t\t\tres" << endl;
    
    double in, out;
    
    if (reactorSolver.getNoCells() > 1) {
      // This is a quasi-1d reactor, alpha and beta are fixed by the velocity and dimensions of the grid
      // Inflow (alpha) and outflow rates (beta) are given by alpha^(-1) = beta^(-1) = u/delta_x
      //cellIter->setIORates(delta_x/u,delta_x/u);
      in = out = delta_x / reactorSolver.getU();
    } else {
      // This is a 0d reactor with prescribed in and outflow rates
      in = reactorSolver.getIn();
      out = reactorSolver.getOut();
    }
    
    // Initialise a reactor as a network of noCells cells (1 in the 0d case)
    vector<Cell> reactor(reactorSolver.getNoCells()+1, Cell(in, out, reactorSolver.getN()));
    
    /*
      for(vector<Cell>::iterator cellIter = reactor.begin(); cellIter != reactor.end(); cellIter++)
      {
      unsigned long cellId = cellIter - reactor.begin();
      cellIter->setId(cellId);
      }
    */
    
    // Loop through all cells in the domain, converging to steady-state in each
    for (vector<Cell>::iterator cellIter = reactor.begin(); cellIter != reactor.end(); cellIter++) {
      cell = cellIter - reactor.begin();
      
      //cout << "Initialising cell " << cell << endl;
      
      // Initialise initial distribution of particles in current cell to delta distribution (mono-dispersed)
      cellIter->initDist(mono); // Always use mono-dispersed initial conditions
      
      // Initialise moments in current cell
      cellIter->initMoments();
      
      /* // Old method
	 if (cell == 0)
	 {
	 //cout << "Setting n_in distribution to mono-dispersed" << endl;
	 cellIter->initInDist(mono); // first cell has mono-dispersed distribution
	 }
	 else
	 {
	 //cout << "Setting n_in distribution to steady-state distributionin cell " << cell-1 << endl;
	 vector<Cell>::iterator prevCell = cellIter - 1;
	 cellIter->initInDist(prevCell->getDist()); // get steady-state distribution from previous cell        
	 }
      */
      
      int l = 1; // iteration number
      bool cellConverged = false; // cell-wise convergence
      
      // First cell in domain, apply the boundary condition
      if (cell == 0) {
	// Set n = nin
	// Already called cellIter->initDist(mono), so just need to stop iteration for first cell
	cellConverged = true;

	// Set Inflowing distribution (0D case) or boundary condition (1D case)
	// In the 1D case, this is not relevant, the infowing distribtuion
	// becomes a boundary conditions, i.e., initDist for cell 0
	cellIter->initInDist(reactorSolver.getInDist()); // first cell has inDist distribution (from -nin arg)
	cellIter->initDist(reactorSolver.getInDist()); // first cell has inDist distribution (from -nin arg)

	//cellIter->initInDist(uniform); // first cell has mono-dispersed distribution
	//cellIter->initDist(uniform); // first cell has mono-dispersed distribution
	//cout << "In dist = " << reactorSolver.getInDist() << endl;
	
	cellIter->calculateMoments();
	currMaxRes = 0e0;

	
      } else { // Not the fist cell in domain, set n_in to steady-state distribution from pevious cell
	//cout << "Setting n_in distribution to steady-state distributionin cell " << cell-1 << endl;
	vector<Cell>::iterator prevCell = cellIter - 1;
	cellIter->initInDist(prevCell->getDist()); // get steady-state distribution from previous cell        
      }
      
      // Find steady-state solution in each cell
      while (!cellConverged) {
	// Let's compute the moments of the distribution and get the current maximum residual
	currMaxRes = cellIter->calculateMoments();
	
	// If this a 0D sim, output the moment convergents to screen and file
	if (reactorSolver.getNoCells() <= 1)
	  reactorSolver.writeMoments(l, cellIter->getMoments());
	
	// Update old distribution to new distribution
	cellIter->updateDist();
	
	// Iterate over all particle (cluster) sizes in cell
	if(reactorSolver.isNumberDensityRep()) // Number density representation
	  {
	    //cellIter->iterateND(reactorSolver, *cellIter);
	    cellIter->iterateAccelND(reactorSolver, *cellIter);
	  }
	else // Mass density representation
	  {
	    //cellIter->iterateMD(reactorSolver, *cellIter); // No acceleration   
	    //cellIter->iterateAitkenMD(reactorSolver, *cellIter); // Aitken acceleration

	    // Not it's legitimate to use continue to skip over small values of oldNumDens
	    // which won't affect the coagSum much, but dangerous to break out of the loop all together
	    // when numDens is small for remaining clusters
	    // Note currently the dangerous acceleration method is implemented to should be aware if this
	    // if there's large discrepancies in the calculation
	    cellIter->iterateAccelMD(reactorSolver, *cellIter); // Dangerous acceleration  
	  }
	
	if (reactorSolver.getL() != 0) {
	  cellConverged = !(l <= reactorSolver.getL());
	}
	else if (currMaxRes < reactorSolver.getMaxRes()) {
	  // Have reached steady-state with a tolerance of maxRes
	  //cout << "Cell: "<< cell << "Steady-state reached in " << l << " iterations, with a maximum residual of " << currMaxRes << "!" << endl;
	  cellConverged = true;
	}
	
	l++; // Update iteration counter
	
	if (l > maxIter || currMaxRes > resCutOff) {
	  cout << "Carried out " << l << " iterations, with a current residual of " << currMaxRes << ". Check that there is a steady-state solution." << endl;
	  cellConverged = true;
	}
	
      } // Single cell convergence loop
      
      
      /*
	cout << cell << "\t"; 
	reactorSolver.writeFinalMoments(cellIter->getMoments());
	cout << "\t" << --l << "\t\t" << currMaxRes << endl;
      */
      
      // Print steady-state moments in current cell (if this a 1D sim)
      if (reactorSolver.getNoCells() > 1)
	reactorSolver.writeFinalMoments(cell, cell * delta_x, reactorSolver.getU(), cellIter->getMoments(), l-1, currMaxRes);
      
      
      // Dump data to file
      //reactorSolver.writeOutput(reactorCell)
      //reactorSolver.writeOutput(cell, cell*delta_x, reactorCell)   
      
    } // Cell iterator
  }
  

  // This method turns out to be less efficient than cell-wise convergence in most cases, so this section
  // of the code is largely ignored
  else if (convergenceType == globalConvergence) 
    {
      double in, out;
      
      double globalMaxRes = 0e0;
      if (reactorSolver.getNoCells() > 1) {
	// This is a quasi 1d reactor, alpha and beta are fixed by the velocity and dimensions of the grid
	// Inflow (alpha) and outflow rates (beta) are given by alpha^(-1) = beta^(-1) = u/delta_x
            //cellIter->setIORates(delta_x/u,delta_x/u);
	in = out = reactorSolver.delta_x() / reactorSolver.getU();
      }
      else
        {
	  in = reactorSolver.getIn();
	  out = reactorSolver.getOut();
        }
      
      // Initialise a reactor as a network of noCells cells
      vector<Cell> reactor(reactorSolver.getNoCells()+1, Cell(in, out, reactorSolver.getN()));
      
      /*
        for(vector<Cell>::iterator cellIter = reactor.begin(); cellIter != reactor.end(); cellIter++)
        {
	unsigned long cellId = cellIter - reactor.begin();
	cellIter->setId(cellId);
        }
         */

      // Loop through all cells once to initialise distributions in each cell
      for (vector<Cell>::iterator cellIter = reactor.begin(); cellIter != reactor.end(); cellIter++) {
	
	// Initialise initial distribution of particles in current cell
	cellIter->initDist(mono);
	
	// Initialise moments in current cell
	cellIter->initMoments();
      }
      
      bool globallyConverged = false;
      
      int l = 1; // iteration number
      
      while (!globallyConverged)
        {
	  globalMaxRes = 0e0;
	  globallyConverged = false;
	  
	  // Loop through all cells in the domain, converging to steady-state in each
	  for (vector<Cell>::iterator cellIter = reactor.begin(); cellIter != reactor.end(); cellIter++) {
	    
	    cell = cellIter - reactor.begin();
	    
	    // Let's compute the moments of the distribution and get the current maximum residual
	    currMaxRes = cellIter->calculateMoments();
            
	    if (currMaxRes > globalMaxRes)
	      globalMaxRes = currMaxRes;
	    
	    // First cell in domain, apply the boundary condition
	    if (cell == 0) {
	      continue; // this is the boundary condition, don't need to iterate
	    }
	    else 
	      {
		vector<Cell>::iterator prevCell = cellIter - 1;
		cellIter->initInDist(prevCell->getDist()); // get steady-state distribution from previous cell        
		
		// Find steady-state solution in each cell

		// Update old distribution to new distribution
		cellIter->updateDist();
		
		// Iterate over all particle (cluster) sizes in cell
		cellIter->iterate(reactorSolver, *cellIter);
		
		
	      }
	  }
	  
	  cout << "Iteration" << l;
	  cout << ". Global max residual: " << globalMaxRes << endl;
	  
          
	  if (reactorSolver.getL() != 0) {
	    globallyConverged = !(l <= reactorSolver.getL());
	  } else if (globalMaxRes < reactorSolver.getMaxRes()) {
	    // Have reached steady-state with a tolerance of maxRes
	    //cout << "Cell: "<< cell << "Steady-state reached in " << l << " iterations, with a maximum residual of " << currMaxRes << "!" << endl;
	    globallyConverged = true;
	  }
	  
	  if (l > maxIter || globalMaxRes > resCutOff) {
	    //cout << "Carried out " << l << " iterations, with a current residual of " << currMaxRes << ". Check that there is a steady-state solution." << endl;
	    globallyConverged = true;
	  }
	  
	  
	  
	  l++; // Update iteration counter   
        } // Complete first iteration across all cells in domain
      
      // Output header
      if (reactorSolver.getNoCells() <= 1)
        {
	  vector<Cell>::iterator cellIter = reactor.begin();
	  cout << "Iter\t\tm0\t\t\tm1\t\t\tm2\t\t\tm3" << endl;
	  reactorSolver.writeMoments(l, cellIter->getMoments());
        }
      else
        {
	  cout << "Cell\t\tm0\t\t\tm1\t\t\tm2\t\t\tm3\t\t# iters\t\t\tres" << endl;
	  for (vector<Cell>::iterator cellIter = reactor.begin(); cellIter != reactor.end(); cellIter++)
            {
	      cell = cellIter - reactor.begin();
	      // Print steady-state moments in current cell (if this a 1D sim)
	      reactorSolver.writeFinalMoments(cell, cell * delta_x, reactorSolver.getU(), cellIter->getMoments(), l-1, currMaxRes);
            }
        }
      
      
    } // Convergence type
  
} //Main
