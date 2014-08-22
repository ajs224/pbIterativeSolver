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
    
    std::string getKernelName(){ return kernelName;}
    const unsigned int get_p(){return p;} 
    const unsigned long getN(){return N;}
    const unsigned long getL(){return L;}
    
    bool isNumberDensityRep() {return numberDensityRep;}
    bool isCoagOn() {return coagOn;}
    
    //std::ofstream & getOutputFile(){return &outputFile;};
    //std::ofstream & getMomentsFile(){return &momentsFile;};

    double getMaxRes(){return maxRes;}
    
    void writeMoments(int l, double * moments);
    void writeOutput(Cell & reactorCell);
    
private:
    double alpha;
    double beta;
    bool numberDensityRep;
    mfaAnalytic::distributions inDist;
    std::string inDistName;
    std::string kernelName;
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
    
};

#endif	/* SOLVER_H */

