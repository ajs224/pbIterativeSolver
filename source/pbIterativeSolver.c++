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
// Suspect 1 is most efficient
//---------------------------------------------------------------/

// To run with inflow rate=outflow rate=1, const kernel, 16 outer loops and a max cluster size of 2^10 use: 
// time ./pbSolverIterative -alpha 1 -k constant -loops 16 -p 10
// To run with the additive kernel and defaul in/outflow rates use:
// time ./pbSolverIterative -k additive -loops 256 -p 20
// In order to achieve convergence with the additive (and multiplicative?) kernels lower the inflow rate:
// time ./pbSolverIterative -alpha 0.1 -k additive -loops 256 -p 10
//time ./pbSolverIterative -alpha 0.1 -k multiplicative -loops 64 -p 16

/*
 Structure of the code is as follows:
 * The Solver class contains all of the simulation parameters and hold methods for writing moments etc * 
 
 * The Cell class contains all of the data for a single cell (n, moments, etc).
 * A vector of these Cell classes can be strung together to create a quasi-1d reactor
 */



/*
 To do:
 * encapsulation tutorial
 * put iterate into cell class
 * add multicell functionality
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

#include "random.h"
#include "mfa_functions.h"
#include "mfa_params.h"
#include "Solver.h"

int main(int argc, char *argv[]) {
    using namespace std;
    using namespace mfaAnalytic;
    using namespace ajsRandom;

    bool loadRandState = false; // Generate a new set of seeds
    bool saveRandState = true; // Write the state so we can rewread later

    // Declare a Mersenne Twister random number generator
    MTRand mtrand; // = intRand(loadRandState);

    // Parameters
    int maxIter = 1000;
    double resCutOff = 1e10;
    int noCells = 10; // grid consists of 100 cells
    double gridLength = 1; // grid has length 1m
    double u = 1; // velocity in x direction of domain in m/s
    double delta_x = gridLength/(double) noCells;

    double currMaxRes;
    //bool isRunning = true;
    bool converged = false; // global convergence
    int cell;
    
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
    if (reactorSolver.parseArgs(argc, argv)) {
        // Didn't enter any arguments
        return 0;
    }

    // Setup up filenames and print summary of parameters    
    reactorSolver.setup();

    // Output header
    //cout << "Iter\t\tm0\t\t\tm1\t\t\tm2\t\t\tm3" << endl;
    cout << "Cell\t\tm0\t\t\tm1\t\t\tm2\t\t\tm3\t\t# iters\t\t\tres" << endl;
       
    // Initialise a reactor as a network of noCells cells
    vector<Cell> reactor(noCells, Cell(reactorSolver.getIn(), reactorSolver.getOut(), reactorSolver.getN()));
  
    for(vector<Cell>::iterator cellIter = reactor.begin(); cellIter != reactor.end(); cellIter++)
    {
        unsigned long cellId = cellIter - reactor.begin();
        cellIter->setId(cellId);
    }
    
    /*
    for(vector<Cell>::iterator cellIter = reactor.begin(); cellIter != reactor.end(); cellIter++)
    {
        unsigned long cellId = cellIter - reactor.begin();
        cellIter->setId(cellId);
    }

    */
    
    // Loop through all cells in the domain, converging to steady-state in each
    for(vector<Cell>::iterator cellIter = reactor.begin(); cellIter != reactor.end(); cellIter++)
    {
        cell = cellIter - reactor.begin();
        
        //cout << "Initialising cell " << cell << endl;

        // Initialise initial distribution of particles in current cell
        cellIter->initDist(mono);

        // Initialise moments in current cell
        cellIter->initMoments();
        
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
        
        // Inflow (alpha) and outflow rates (beta) are given by alpha^(-1) = beta^(-1) = u/delta_x
        cellIter->setIORates(delta_x/u,delta_x/u);
        
        double cellBirthSum, cellDeathSum;

        int l = 1; // iteration number
        bool cellConverged = false; // cell-wise convergence
            
        while (!cellConverged) 
        {
            // Let's compute the moments of the distribution and get the current maximum residual
            currMaxRes = cellIter->calculateMoments();

            // Output the moments to screen and file
            //reactorSolver.writeMoments(l, cellIter->getMoments());

            // Update old distribution to new distribution
            cellIter->updateDist();

            // Iterate over all particle (cluster) sizes in cell
            cellIter->iterate(reactorSolver, *cellIter, cellBirthSum, cellDeathSum);

            if (reactorSolver.getL() != 0) {
                cellConverged = !(l <= reactorSolver.getL());
            } else if (currMaxRes < reactorSolver.getMaxRes()) {
                // Have reached steady-state with a tolerance of maxRes
                //cout << "Cell: "<< cell << "Steady-state reached in " << l << " iterations, with a maximum residual of " << currMaxRes << "!" << endl;
                cellConverged = true;
            }

            l++; // Update iteration counter

            if (l > maxIter || currMaxRes > resCutOff) 
            {
                //cout << "Carried out " << l << " iterations, with a current residual of " << currMaxRes << ". Check that there is a steady-state solution." << endl;
                cellConverged = true;
            }
        }
        
        // Print steady-state moments in current cell
        //reactorSolver.writeFinalMoments(cellIter->getMoments());
        cout << cell << "\t"; 
        reactorSolver.writeFinalMoments(cellIter->getMoments());
        cout << "\t" << --l << "\t\t" << currMaxRes << endl;
    }



    

    
    return 0;
    
    // Single cell case   
    Cell reactorCell = Cell(reactorSolver.getIn(), reactorSolver.getOut(), reactorSolver.getN());
    reactorCell.initDist(mono); // Set initial number density distribution 
    reactorCell.initInDist(mono); // Set distribution of inflowing particles
    reactorCell.initMoments(); // Initialise the moments array
    
    
    int l = 1;
    double birthSum, deathSum;

    bool isRunning = true;
    
    // Iterate L times
    while (isRunning) {
        // Let's compute the moments of the distribution and get the current maximum residual
        double currMaxRes = reactorCell.calculateMoments();

        // Output the moments to screen and file
        reactorSolver.writeMoments(l, reactorCell.getMoments());

        // Update old distribution to new distribution
        reactorCell.updateDist();

        // Iterate over all particle (cluster) sizes in cell
        reactorCell.iterate(reactorSolver, reactorCell, birthSum, deathSum);

        if (reactorSolver.getL() != 0) {
            isRunning = (l <= reactorSolver.getL());
        } else if (currMaxRes < reactorSolver.getMaxRes()) {
            // Have reached steady-state with a tolerance of maxRes
            cout << "Steady-state reached in " << l << " iterations, with a maximum residual of " << currMaxRes << "!" << endl;
            isRunning = false;
        }


        l++; // Update iteration counter

        if (l > maxIter || currMaxRes > resCutOff) {
            cout << "Carried out " << l << " iterations, with a current residual of " << currMaxRes << ". Check that there is a steady-state solution." << endl;
            isRunning = false;
        }
    }

    // Dump steady-state PSD
    reactorSolver.writeOutput(reactorCell);

    return 0;

}