/* 
 * File:   Cell.c++
 * Author: ajs224
 * 
 * Created on 18 August 2014, 15:03
 */

#include<iostream>
#include <cmath>
#include <cstdlib>
#include <limits> // for machine epsilon std::numeric_limits<T>::epsilon()
#include "Kernel.h"
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
    //std::cout << "Called cell constructor\n";
    //std::cout << "N = " << N;
}

Cell::Cell(const Cell& orig) {
    using namespace mfaAnalytic;
    alpha = orig.alpha;
    beta = orig.beta;
    N = orig.N;
    nIn = new double[N+1];
    n = new double[N+1];
    nold = new double[N+1];
    moments = new double[noMoments];
    momentsPrev = new double[noMoments];

    *nIn = *orig.nIn;
    *n = *orig.n;
    *nold = *orig.nold; 
    *moments = *orig.moments; 
    *momentsPrev = *orig.momentsPrev;  
    //std::cout << "Called cell copy constructor\n";    
    
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
 
    //std::cout << "Called cell destructor\n";
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
    //std::cout << "In initDist\n";
    //std::cout << "N = " << N;

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
    //std::cout << "Initialising in dist to mono" << std::endl;
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
    //std::cout << "Initialising in dist to new dist" << std::endl;
    //*nIn = *newInDist;
     for(unsigned long i=1;i<=N;i++)
	{
            nIn[i] = newInDist[i];
        }
}


void Cell::initMoments()
{
    // Initialise previous moments array which is used for calculating residuals
    //std::cout << "Initialising moments array" << std::endl;
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

void Cell::iterate(Solver & reactorSolver, Cell & reactorCell)
{
    

    for(unsigned long i=1;i<=reactorSolver.getN();i++) // Loop over N particle sizes
    {
        // Compute sums in numerator and denominator
	double coagDeathSum=0e0;
	for(unsigned long j=1;j<=reactorSolver.getN();j++)
	{
	    if(reactorSolver.isNumberDensityRep())
                coagDeathSum+=reactorSolver.k(i,j)*reactorCell.getOldNumDens(j);
	    else
		coagDeathSum+=reactorSolver.k(i,j)*reactorCell.getOldNumDens(j)/j;
	}
	  
	double coagBirthSum=0e0;
	for(unsigned long j=1;j<=i-1;j++)
            {
                //summa+=K[i-j][j]*nold[i-j]*nold[j];
                if(reactorSolver.isNumberDensityRep())
                    coagBirthSum+=reactorSolver.k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j);
                else
                    coagBirthSum+=reactorSolver.k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j)/j;
            }

	if(reactorSolver.isNumberDensityRep())
            coagBirthSum*=0.5;

	if (!reactorSolver.isCoagOn())
            {
                coagDeathSum = 0e0;
                coagBirthSum =0e0;
	    }
        
        double birthSum = reactorCell.getInDist(i) / alpha + coagBirthSum;
        double deathSum = 1e0 / beta + coagDeathSum;
        
        // Iterate baby!
        //n[i]=(n_in/alpha+0.5*summa)/(1e0/beta+d);
        //reactorCell.setNumDens(i, (reactorCell.getInDist(i) / reactorSolver.getIn() + birthSum) / (1e0 / reactorSolver.getOut() + deathSum));
        reactorCell.setNumDens(i,  birthSum/deathSum);
       
        
        //n[i]=0.5*summa/d; // Pure coagulation 

 
    }
}

void Cell::iterateND(Solver & reactorSolver, Cell & reactorCell)
{
    // Note implementing separate number density rep ands mass density iterate routines
    // is faster (according to profiler) though the binary will take more space

    for(unsigned long i=1;i<=reactorSolver.getN();i++) // Loop over N particle sizes
    {
        // Compute sums in numerator and denominator
	double coagDeathSum=0e0;
	for(unsigned long j=1;j<=reactorSolver.getN();j++)
            coagDeathSum+=reactorSolver.k(i,j)*reactorCell.getOldNumDens(j);

	double coagBirthSum=0e0;
	for(unsigned long j=1;j<=i-1;j++)
            coagBirthSum+=reactorSolver.k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j);
              
	coagBirthSum*=0.5;

        /*
	if (!reactorSolver.isCoagOn())
            {
                coagDeathSum = 0e0;
                coagBirthSum =0e0;
	    }
        */
        //double birthSum = reactorCell.getInDist(i) / alpha + coagBirthSum;
        //double deathSum = 1e0 / beta + coagDeathSum;
        
        // Iterate baby!
        //n[i]=(n_in/alpha+0.5*summa)/(1e0/beta+d);
        //reactorCell.setNumDens(i, (reactorCell.getInDist(i) / reactorSolver.getIn() + birthSum) / (1e0 / reactorSolver.getOut() + deathSum));
        //reactorCell.setNumDens(i,  birthSum/deathSum);
        reactorCell.setNumDens(i,  (reactorCell.getInDist(i) / alpha + coagBirthSum)/(1e0 / beta + coagDeathSum));
        //n[i]=0.5*summa/d; // Pure coagulation 

 
    }
}

// original version of the code
void Cell::iterateMD(Solver & reactorSolver, Cell & reactorCell)
{
    // Note implementing separate number density rep ands mass density iterate routines
    // is faster (according to profiler) though the binary will take more space
  
    for(unsigned long i=1;i<=reactorSolver.getN();i++) // Loop over N particle sizes
    {
        // Compute sums in numerator and denominator
	double coagDeathSum=0e0;
	for(unsigned long j=1;j<=reactorSolver.getN();j++)
            coagDeathSum+=reactorSolver.k(i,j)*reactorCell.getOldNumDens(j)/j;
		  
	double coagBirthSum=0e0;
	for(unsigned long j=1;j<=i-1;j++)
            coagBirthSum+=reactorSolver.k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j)/j;
            

       
        //double birthSum = reactorCell.getInDist(i) / alpha + coagBirthSum;
        //double deathSum = 1e0 / beta + coagDeathSum;
        
        // Iterate baby!
        //n[i]=(n_in/alpha+0.5*summa)/(1e0/beta+d);
        //reactorCell.setNumDens(i, (reactorCell.getInDist(i) / reactorSolver.getIn() + birthSum) / (1e0 / reactorSolver.getOut() + deathSum));
        //reactorCell.setNumDens(i,  birthSum/deathSum);
       reactorCell.setNumDens(i,  (reactorCell.getInDist(i) / alpha + coagBirthSum)/(1e0 / beta + coagDeathSum));
        
        //n[i]=0.5*summa/d; // Pure coagulation 

 
    }
}

        
        
// This version uses Aitkin's delta squared process to accelerate convergence
void Cell::iterateAitkenMD(Solver & reactorSolver, Cell & reactorCell)
{
    // Note implementing separate number density rep ands mass density iterate routines
    // is faster (according to profiler) though the binary will take more space

    double n1[reactorSolver.getN()];
    
    // calculate n^(1) = F(n^(0))
    for(unsigned long i=1;i<=reactorSolver.getN();i++) // Loop over N particle sizes
    {
        // Compute sums in numerator and denominator
	double coagDeathSum=0e0, coagBirthSum=0e0;
	for(unsigned long j=1;j<=reactorSolver.getN();j++)
        {
            coagDeathSum+=reactorSolver.k(i,j)*reactorCell.getOldNumDens(j)/j;
            //if(j<=i-1)
            //    coagBirthSum+=reactorSolver.k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j)/j;
            
            // dodgy acceleration strategy - careful here
            if (getOldNumDens(j) < std::numeric_limits<long double>::epsilon())
                break;
        }
         
        
	//double coagBirthSum=0e0;
	for(unsigned long j=1;j<=i-1;j++)
        {
            coagBirthSum+=reactorSolver.k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j)/j;
            if (getOldNumDens(j) < std::numeric_limits<long double>::epsilon())
                break;
        }
        
        //reactorCell.setNumDens(i,  (reactorCell.getInDist(i) / alpha + coagBirthSum)/(1e0 / beta + coagDeathSum));
        n1[i] = (reactorCell.getInDist(i) / alpha + coagBirthSum)/(1e0 / beta + coagDeathSum);
        //std::cout<<"n1[" << i << "] = " << n1[i] << std::endl; 
    }

    
    
    double n2[reactorSolver.getN()];
    
    // calculate n^(2) = F(n^(1)
    for(unsigned long i=1;i<=reactorSolver.getN();i++) // Loop over N particle sizes
    {
        // Compute sums in numerator and denominator
	double coagDeathSum=0e0,coagBirthSum=0e0;
	for(unsigned long j=1;j<=reactorSolver.getN();j++)
        {
            coagDeathSum+=reactorSolver.k(i,j)*n1[j]/j;
            //if(j<=i-1)
            //    coagBirthSum+=reactorSolver.k(i-j,j)*n1[i-j]*n1[j]/j;
            
            // dodgy acceleration strategy - careful here
            if (n1[j] < std::numeric_limits<long double>::epsilon())
                break;
        }
        
	//double coagBirthSum=0e0;
	for(unsigned long j=1;j<=i-1;j++)
        {
            coagBirthSum+=reactorSolver.k(i-j,j)*n1[i-j]*n1[j]/j;
            // dodgy acceleration strategy - careful here
            if (n1[j] < std::numeric_limits<long double>::epsilon())
                break;
        }
            
        n2[i] = (reactorCell.getInDist(i) / alpha + coagBirthSum)/(1e0 / beta + coagDeathSum);
        //std::cout<<"n2[" << i << "] = " << n2[i] << std::endl; 
    }


 
    
    double nAitken[reactorSolver.getN()];
    // calculate nAitken = n^(2) - (n^(2)-n^(1))^2)/deltaSqrd
    for(unsigned long i=1;i<=reactorSolver.getN();i++) // Loop over N particle sizes
    {
        double deltaSqrt = n2[i] - 2*n2[i]+getOldNumDens(i); // getOldNumDens(i) is n0[i]
        
        if (abs(deltaSqrt) > std::numeric_limits<long double>::epsilon()) // don't want to divide by a number which is too small
            nAitken[i] = n2[i] - pow((n2[i]-n1[i]),2)/deltaSqrt;
        else
            nAitken[i] = n2[i];
            //std::cerr << "Warning: denominator too small" << std::endl;
        
        
        /*
        std::cout<<"nAitken[" << i << "] = " << nAitken[i] << std::endl;
        std::cout<<"deltaSqrt = " << deltaSqrt << std::endl;
        std::cout<<"pow((n2[i]-n1[i]),2) = " << pow((n2[i]-n1[i]),2) << std::endl;
        */
        reactorCell.setNumDens(i,  nAitken[i]);
    }

    /*
    std::cin.sync();
    std::cin.get();
    */

} 

void Cell::iterateAccelND(Solver & reactorSolver, Cell & reactorCell)
{
    // Note implementing separate number density rep ands mass density iterate routines
    // is faster (according to profiler) though the binary will take more space
    for(unsigned long i=1;i<=reactorSolver.getN();i++) // Loop over N particle sizes
    {
        // Compute sums in numerator and denominator
	double coagDeathSum=0e0;
	for(unsigned long j=1;j<=reactorSolver.getN();j++)
        {
            coagDeathSum+=reactorSolver.k(i,j)*reactorCell.getOldNumDens(j);
            if (getOldNumDens(j) < std::numeric_limits<long double>::epsilon())
                break;
        }
        
	double coagBirthSum=0e0;
	for(unsigned long j=1;j<=i-1;j++)
        {
            coagBirthSum+=reactorSolver.k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j);
            if (getOldNumDens(j) < std::numeric_limits<long double>::epsilon())
                break;
        }   
            
	coagBirthSum*=0.5;

        reactorCell.setNumDens(i,  (reactorCell.getInDist(i) / alpha + coagBirthSum)/(1e0 / beta + coagDeathSum));
  
    }
}


void Cell::iterateAccelMD(Solver & reactorSolver, Cell & reactorCell)
{
    // Note implementing separate number density rep ands mass density iterate routines
    // is faster (according to profiler) though the binary will take more space
      
    //std::cout << "eps = " << std::numeric_limits<long double>::epsilon() << std::endl;
    
    
    for(unsigned long i=1;i<=reactorSolver.getN();i++) // Loop over N particle sizes
    {
        // Compute sums in numerator and denominator
	double coagDeathSum=0e0;
	for(unsigned long j=1;j<=reactorSolver.getN();j++)
        {
            coagDeathSum+=reactorSolver.k(i,j)*reactorCell.getOldNumDens(j)/j;
            // dodgy acceleration strategy - careful here
            if (getOldNumDens(j) < std::numeric_limits<long double>::epsilon())
                break;
            
            /*
            std::cout<<"k("<<i<<","<<j<<") = " << reactorSolver.k(i,j)<< std::endl;
            std::cin.sync();
            std::cin.get();
            */
        }
	double coagBirthSum=0e0;
	for(unsigned long j=1;j<=i-1;j++)
        {    
            coagBirthSum+=reactorSolver.k(i-j,j)*reactorCell.getOldNumDens(i-j)*reactorCell.getOldNumDens(j)/j;
            // dodgy acceleration strategy - careful here
            if (getOldNumDens(j) < std::numeric_limits<long double>::epsilon())
                break;
        }   
       
        //double birthSum = reactorCell.getInDist(i) / alpha + coagBirthSum;
        //double deathSum = 1e0 / beta + coagDeathSum;
        
        // Iterate baby!
        //n[i]=(n_in/alpha+0.5*summa)/(1e0/beta+d);
        //reactorCell.setNumDens(i, (reactorCell.getInDist(i) / reactorSolver.getIn() + birthSum) / (1e0 / reactorSolver.getOut() + deathSum));
        //reactorCell.setNumDens(i,  birthSum/deathSum);
       reactorCell.setNumDens(i,  (reactorCell.getInDist(i) / alpha + coagBirthSum)/(1e0 / beta + coagDeathSum));
        
        //n[i]=0.5*summa/d; // Pure coagulation 

 
    }
}

