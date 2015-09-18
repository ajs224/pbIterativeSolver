/* 
 * File:   kernel.h
 * Author: ajs224
 *
 * Created on 08 September 2014, 20:36
 */

#ifndef KERNEL_H
#define	KERNEL_H



#include <string>
#include <cmath>
#include <cstdlib>

class Kernel
{
 protected:
  double A;
  std::string kernelName;
 public:
 Kernel(double val, std::string name) : A(val), kernelName(name) {}
  virtual double k(unsigned long int i, unsigned long int j) =0;
  void setA(double val){ A = val;}
  double getA(void){ return A;}
  std::string Name() {return kernelName;}
};

class Constant: public Kernel
{
 public:
 Constant(double val) : Kernel(val, "constant") {}
  double k(unsigned long int i, unsigned long int j) { return A;}
};

class Additive: public Kernel
{
 public:
 Additive(double val) : Kernel(val, "additive") {}
  double k(unsigned long int i, unsigned long int j) { return A*(i+j);}
};

class Multiplicative: public Kernel
{
 public:
 Multiplicative(double val) : Kernel(val, "multiplicative") {}
  double k(unsigned long int i, unsigned long int j) { return A*i*j;}
};


// Brownian motion (continuum regime)
class Continuum: public Kernel
{
 public:
 Continuum(double val) : Kernel(val, "continuum") {}
  double k(unsigned long int i, unsigned long int j) { return A*(pow(i,1e0/3e0)+pow(j,1e0/3e0))*(pow(i,-1e0/3e0)+pow(j,-1e0/3e0));}
};

// Brownian motion (freemolecular regime)
class Freemolecular: public Kernel
{
 public:
 Freemolecular(double val) : Kernel(val, "freemolecular") {}
  double k(unsigned long int i, unsigned long int j) { return A*pow(pow(i,1e0/3e0)+pow(j,1e0/3e0),2e0)*sqrt((1e0/i)+(1e0/j));}
};
// Transition kernel
class Transition: public Kernel
{
 public:
 Transition(double val) : Kernel(val, "transition") {}
  double k(unsigned long int i, unsigned long int j)
  {
    double q = i/(double) j;
    double p = pow(q,0.33333333);
    double beta_c = (2+p+1/p);
    double beta_f = pow(j,0.16666666)*sqrt(1+1/q)*pow(1+p,2);
    return A*beta_c*beta_f/(beta_c+beta_f);

    // Raw calculation is slow
    //return A*(pow(i,1e0/3e0)+pow(j,1e0/3e0))*(pow(i,-1e0/3e0)+pow(j,-1e0/3e0))*1e0/(1e0+(pow(i,1e0/3e0)+pow(j,1e0/3e0))*(pow(i,-1e0/3e0)+pow(j,-1e0/3e0))/(pow(pow(i,1e0/3e0)+pow(j,1e0/3e0),2e0)*sqrt((1e0/i)+(1e0/j))));};

  };

// Based on kinetic theory
class Kinetic: public Kernel
{
 public:
 Kinetic(double val) : Kernel(val, "kinetic") {}
  double k(unsigned long int i, unsigned long int j) { return A*(pow(i,1e0/3e0)+pow(j,1e0/3e0))*pow(i*j,1e0/2e0)*pow(i+j,-3e0/2e0);}
};

// Shear (linear velocity profile)
class Shearlinear: public Kernel
{
 public:
 Shearlinear(double val) : Kernel(val, "shearlinear") {}
  double k(unsigned long int i, unsigned long int j) { return A*pow(pow(i,1e0/3e0)+pow(j,1e0/3e0),3e0);}
};

// Shear (nonlinear velocity profile):
class Shearnonlinear: public Kernel
{
 public:
  Shearnonlinear(double val) : Kernel(val, "shearnonlinear") {}
  double k(unsigned long int i, unsigned long int j) { return A*pow(pow(i,1e0/3e0)+pow(j,1e0/3e0),7e0/3e0);}
};

// Gravitational settling
class Settling: public Kernel
{
 public:
 Settling(double val) : Kernel(val, "settling") {}
  double k(unsigned long int i, unsigned long int j) { return A*pow(pow(i,1e0/3e0)+pow(j,1e0/3e0),2e0)*abs(pow(i,1e0/3e0)-pow(j,1e0/3e0));}
};


// Inertia and gravitational settling
class Inertiasettling: public Kernel
{
 public:
  Inertiasettling(double val) : Kernel(val, "inertiasettling") {}
  double k(unsigned long int i, unsigned long int j) { return A*pow(pow(i,1e0/3e0)+pow(j,1e0/3e0),2e0)*abs(pow(i,2e0/3e0)-pow(j,2e0/3e0));}
};

// Analytic approximation of Berry's kernel
class Berry: public Kernel
{
 public:
 Berry(double val) : Kernel(val, "berry") {}
  double k(unsigned long int i, unsigned long int j) { return A*pow(i-j,2e0)*pow(i+j,-1e0);}
};


// Condensation and/or branched-chain polymerisation
// with constant c=2 
class Condensation: public Kernel
{
 public:
 Condensation(double val) : Kernel(val, "condensation") {}
  double k(unsigned long int i, unsigned long int j) { return A*(i+2)*(j+2);}
};

//SPM test kernel
class SPMtest: public Kernel
{
 public:
 SPMtest(double val) : Kernel(val, "spmtest") {}
  double k(unsigned long int i, unsigned long int j) { return A*pow(i*j,1e0/3e0);}
};


/*
class : public Kernel
{
 public:
 (double val) : Kernel(val, "") {}
  double k(unsigned long int i, unsigned long int j) { return A*;}
};
*/















#endif	/* KERNEL_H */

