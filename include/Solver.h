/* 
 * File:   solver.h
 * Author: ajs224
 *
 * Created on 18 August 2014, 15:02
 */

#ifndef SOLVER_H
#define	SOLVER_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Cell.h"
#include "Kernel.h"

class Cell; // Forward declaration (say Cell class exists without defining it)

class Solver
{  
    
public:
    Solver();
    Solver(const Solver& orig);
    virtual ~Solver();
    
    
    int parseArgs(int argc, char *argv[]);
    void setup();
    
    // Accessor methods
    double getIn() {return alpha;}
    double getOut() {return beta;}
    
    //std::string getKernelName(){ return kernelName;}
    const unsigned int get_p(){return p;} 
    const unsigned long getN(){return N;}
    const unsigned long getL(){return L;}
    
    bool isNumberDensityRep() {return numberDensityRep;}
    bool isCoagOn() {return coagOn;}

    double delta_x(){return gridLength/(double) noCells;}
    int getNoCells() {return noCells;} 
    double getU(){return u;}
    
    //std::ofstream & getOutputFile(){return &outputFile;};
    //std::ofstream & getMomentsFile(){return &momentsFile;};

    double getMaxRes(){return maxRes;}
    
    void precalculateK();
    void writeK();
    bool readK();
    
        
    //double k(unsigned long int i, unsigned long int j){return kernel->k(i,j);}// Calculates each time   
    double k(unsigned long int i, unsigned long int j){return precalculatedK[i][j];}// Used precalculated values for speed  
    
    void writeMoments(int l, double * moments);
    void writeFinalMoments(int cell, double x, double u, double * moments, int iter, double res);
    //void writeFinalMoments(double * moments);
    void writeOutput(Cell & reactorCell);
    //void writeOutput(int cell, double x, double u, Cell & reactorCell, int iter, double res);
    
private:
    // 0D parameters
    double alpha; // inflow rate
    double beta; // outflow rate
    
    // 1D parameters
    int noCells;// = 100; // grid consists of 100 cells
    double gridLength;// = 1; // grid has length 1m
    double u;// = 1; // velocity in x direction of domain in m/s
    
    // Common parameters
    bool numberDensityRep;
    mfaAnalytic::distributions inDist;
    std::string inDistName;
    //std::string kernelName;
    
    Kernel * kernel;
    
    bool coagOn;
    unsigned int p;
    unsigned int outerItLoops;
    unsigned long int L;
    double maxRes;
    unsigned long N; 
    
    //ofstream diamsFile;
    std::string outputFileName;
    std::string momentsFileName;
    
    // Set up output file streams
    std::ofstream outputFile;
    std::ofstream momentsFile;
    double ** precalculatedK;
    
    
};

#endif	/* SOLVER_H */

