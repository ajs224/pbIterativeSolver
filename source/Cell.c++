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

void Cell::iterate()
{
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

