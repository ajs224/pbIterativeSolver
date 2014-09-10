/* 
 * File:   Cell.h
 * Author: ajs224
 *
 * Created on 18 August 2014, 15:03
 */

#ifndef CELL_H
#define	CELL_H

#include "mfa_params.h"
#include "Solver.h"

class Solver; // Forward declaration (say Solver class exists without defining it)

class Cell 
{
public:
    Cell();
    Cell(double in, double out, unsigned long int noClusters);
    Cell(const Cell& orig);
    virtual ~Cell();
    
    /*
    double double getIn(){return alpha;};
    getOut(){return beta};
    
    void setIn(double in){alpha = in;}
    void setOut(double out){beta = out;}
    */
    

    // Accessor methods
    double * getDist(){return n;}
    double * getOldDist(){return nold;}
  
    double * getMoments() {return moments;}
    
    double getNumDens(unsigned long i) {return n[i];}
    double getOldNumDens(unsigned long i) {return nold[i];}

    void setNumDens(unsigned long i, double ni) {n[i] = ni;} 
    double getInDist(unsigned long int i){return nIn[i];}
    
    void setIORates(double in, double out){alpha = in; beta = out;}
        
    void setId(unsigned long cellId){id = cellId;}
    unsigned long int getId(){return id;}
    
    void updateDist();
    void initDist(mfaAnalytic::distributions inDist);  
    
    void initInDist(mfaAnalytic::distributions inDist);
    void initInDist(double * newInDist);

    void initMoments();
    double calculateMoments();
    
    void iterate(Solver & reactorSolver, Cell & reactorCell);
    void iterateND(Solver & reactorSolver, Cell & reactorCell);
    void iterateMD(Solver & reactorSolver, Cell & reactorCell);
    void iterateAitkenMD(Solver & reactorSolver, Cell & reactorCell);
    void iterateAccelMD(Solver & reactorSolver, Cell & reactorCell);
    
private:
    
    double alpha, beta;
    unsigned long int N;
    unsigned long int id;
      
    double * moments;
    double * momentsPrev;
    
    double *nIn;
    double *n; //new double[N+1];
    double *nold; //new double[N+1];
 
};

#endif	/* CELL_H */

