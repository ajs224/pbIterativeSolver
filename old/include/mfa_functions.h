#ifndef MFA_FUNCS_H
#define MFA_FUNCS_H

// Function headers
double k(double x, double y); // Collision kernel
double kt(double x, double y); // Majorant kernel
double* computeMoments(double* diamArray, int noMoments);
double theta(double x); // Outflow rate

#endif
