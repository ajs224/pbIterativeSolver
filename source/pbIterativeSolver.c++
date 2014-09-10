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

    int maxIter = 1000;
    double resCutOff = 1e10;

    double currMaxRes;
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

    double delta_x = reactorSolver.delta_x();

    enum convergenceTypes {globalConvergence, cellWise};
    
    //convergenceTypes convergenceType = globalConvergence;
    convergenceTypes convergenceType = cellWise; // As we may expect cellwise is more efficient
    
    if (convergenceType == cellWise) {
        // Output header
        if (reactorSolver.getNoCells() <= 1)
            cout << "Iter\t\tm0\t\t\tm1\t\t\tm2\t\t\tm3" << endl;
        else
            cout << "Cell\t\tm0\t\t\tm1\t\t\tm2\t\t\tm3\t\t# iters\t\t\tres" << endl;

        double in, out;

        if (reactorSolver.getNoCells() > 1) {
            // This is a quasi 1d reactor, alpha and beta are fixed by the velocity and dimensions of the grid
            // Inflow (alpha) and outflow rates (beta) are given by alpha^(-1) = beta^(-1) = u/delta_x
            //cellIter->setIORates(delta_x/u,delta_x/u);
            in = out = reactorSolver.delta_x() / reactorSolver.getU();
        } else {
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

        // Loop through all cells in the domain, converging to steady-state in each
        for (vector<Cell>::iterator cellIter = reactor.begin(); cellIter != reactor.end(); cellIter++) {
            cell = cellIter - reactor.begin();

            //cout << "Initialising cell " << cell << endl;

            // Initialise initial distribution of particles in current cell
            cellIter->initDist(mono);

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
                cellIter->calculateMoments();
                currMaxRes = 0e0;
                //cellIter->initDist(mono);
                //cellIter->initInDist(mono); // first cell has mono-dispersed distribution
            } else {
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
                if(reactorSolver.isNumberDensityRep())
                    cellIter->iterateND(reactorSolver, *cellIter);
                else
                {
                    //cellIter->iterateMD(reactorSolver, *cellIter);   
                    //cellIter->iterateAitkenMD(reactorSolver, *cellIter);   
                    cellIter->iterateAccelMD(reactorSolver, *cellIter);   
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
                    //cout << "Carried out " << l << " iterations, with a current residual of " << currMaxRes << ". Check that there is a steady-state solution." << endl;
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