/* 
 * File:   Cell.h
 * Author: ajs224
 *
 * Created on 18 August 2014, 15:03
 */

#ifndef CELL_H
#define	CELL_H

#include "mfa_params.h"

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
    

    
     double * getDist(){return n;}
     double * getOldDist(){return nold;}
    
     void updateDist();
     void initDist(mfaAnalytic::distributions inDist);    
     
     double getNumDens(unsigned long i) {return n[i];}
     double getOldNumDens(unsigned long i) {return nold[i];}

     void setNumDens(unsigned long i, double ni) {n[i] = ni;} 

     void initInDist(mfaAnalytic::distributions inDist);
     void initInDist(double * newInDist);
     
     double getInDist(unsigned long int i){return nIn[i];}
     
private:
    
    double alpha, beta;
    unsigned long int N;

    double *nIn;
    double *n; //new double[N+1];
    double *nold; //new double[N+1];
    
};

#endif	/* CELL_H */

