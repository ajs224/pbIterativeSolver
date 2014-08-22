/* 
 * File:   Cell.c++
 * Author: ajs224
 * 
 * Created on 18 August 2014, 15:03
 */

#include<iostream>
#include <cmath>
#include <cstdlib>
#include "Cell.h"
#include "mfa_functions.h"
#include "mfa_params.h"
 
Cell::Cell() 
{

    using namespace mfaAnalytic;
    alpha = 0.1;
    beta = alpha;
    N = 1024;
    nIn = new double[N+1];
    n = new double[N+1];
    nold = new double[N+1];
    moments = new double[noMoments];
    momentsPrev = new double[noMoments];
}

Cell::Cell(double in, double out, unsigned long int noClusters)
{
    using namespace mfaAnalytic;
    alpha = in;
    beta = out;
    N = noClusters;
    nIn = new double[N+1];
    n = new double[N+1];
    nold = new double[N+1];
    moments = new double[noMoments];
    momentsPrev = new double[noMoments];
    
}

Cell::Cell(const Cell& orig) {
}

Cell::~Cell() 
{
    delete [] nIn;  
    nIn = NULL;  

    delete [] n;  
    n = NULL;    
  
    delete [] nold; 
    nold = NULL;  
         
    delete [] moments;
    moments = NULL; 
  
}

void Cell::updateDist()
{
    for(unsigned long i=1;i<=N;i++)
	{
     	  nold[i]=n[i];
	}   
}

void Cell::initDist(mfaAnalytic::distributions inDist)
{
    
    if(inDist == mfaAnalytic::mono)
    {
        for(unsigned long i=1;i<=N;i++)
	{
            n[i] = 0e0;
        }// delta distribution (nIn(i,a) is delta dist about cluster of size a)
        n[1] = 1e0;
    } 
    else if(inDist == mfaAnalytic::uniform)
    {
        for(unsigned long i=1;i<=N;i++)
	{
            n[i] = 1e0/((double) N); //nIn(i,i); // uniform distribution
        }
    }    
}

void Cell::initInDist(mfaAnalytic::distributions inDist)
{
    if(inDist == mfaAnalytic::mono)
    {
        for(unsigned long i=1;i<=N;i++)
	{
            nIn[i] = 0e0;
        }// delta distribution (nIn(i,a) is delta dist about cluster of size a)
        nIn[1] = 1e0;
    } 
    else if(inDist == mfaAnalytic::uniform)
    {
        for(unsigned long i=1;i<=N;i++)
	{
            nIn[i] = 1e0/((double) N); //nIn(i,i); // uniform distribution
        }
    }    
    else
    {
        std::cout << "m_in distribution error!" << std::endl;
	//return 0;
    }
}

void Cell::initInDist(double * newInDist)
{
    nIn = newInDist;
}


void Cell::initMoments()
{
    // Initialise previous moments array which is used for calculating residuals
    for(int moment=0;moment<mfaAnalytic::noMoments;moment++)
    {
        momentsPrev[moment]=0e0;
    }

}



double Cell::calculateMoments()
{
  
    double currMaxRes = 0e0;
    double currRes;
    // Let's compute the moments of the distribution
    for(int moment=0;moment<mfaAnalytic::noMoments;moment++)
    {
        moments[moment]=0e0;
        for(unsigned long i=1;i<=N;i++)
	{
            moments[moment]+=pow(i,moment)*n[i];
        }
	  
        currRes = std::abs(moments[moment] - momentsPrev[moment]);
	  
        momentsPrev[moment] = moments[moment];
	 
        if(currRes > currMaxRes)
            currMaxRes = currRes;
        
    }
  
    
    return currMaxRes;
    
}

void Cell::iterate(Solver & reactorSolver, Cell & reactorCell, double & birthSum, double & deathSum)
{
    

    for(unsigned long i=1;i<=reactorSolver.getN();i++) // Loop over N particle sizes
    {
        // Compute sums in numerator and denominator
	deathSum=0e0;
	for(unsigned long j=1;j<=reactorSolver.getN();j++)
	{
	    if(reactorSolver.isNumberDensityRep())
                deathSum+=k(i,j)*reactorCell.getOldNumDens(j);
	    else
		deathSum+=k(i,j)*reactorCell.getOldNumDens(j)/j;
	}
	  
	birthSum=0e0;
	for(unsigned long j=1;j<=i-1;j++)
            {
                //summa+=K[i-j][j]*nold[i-j]*nold[j];
                if(reactorSolver.isNumberDensityRep())
                    birthSum+=k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j);
                else
                    birthSum+=k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j)/j;
            }

	if(reactorSolver.isNumberDensityRep())
            birthSum*=0.5;

	if (!reactorSolver.isCoagOn())
            {
                deathSum = 0e0;
                birthSum =0e0;
	    }
        
        // Iterate baby!
        //n[i]=(n_in/alpha+0.5*summa)/(1e0/beta+d);
        reactorCell.setNumDens(i, (reactorCell.getInDist(i) / reactorSolver.getIn() + birthSum) / (1e0 / reactorSolver.getOut() + deathSum));

        //n[i]=0.5*summa/d; // Pure coagulation 

 
    }
}