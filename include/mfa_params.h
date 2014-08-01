#ifndef MFA_PARAMS_H
#define MFA_PARAMS_H

#include <vector>
#include <string>


namespace MFA
{
    // COMMON TYPEDEFS.

    // Real numbers in Sprog, so they can be easily changed.
    typedef double real;

    // Real number STL vector.
    typedef std::vector<real> fvector; 


    // MATHEMATICAL CONSTANTS.

    const real PI = 3.1415926535897932384626433832795;
    const real ONE_THIRD  = 3.3333334e-01;
    const real TWO_THIRDS = 6.6666667e-01;


    // PHYSICAL CONSTANTS.
	// These numbers are added by Vinod
	const real kB	= 1.380658e-23; // Boltzmann constant
	const real EPSILON0 = 8.854187816e-12;
	// conversion factors
	const real Debye__ = 3.33564e-30; // 
	const real Angstroem__ = 1.0e-10;
    // Avogadro's number (source = NIST website, physics.nist.gov).
    // Error = 3.0e16 /mol.
    const real NA    = 6.02214179e23; // 1/mol.

    // Gas constant (source = NIST website, physics.nist.gov).
    // Error = 1.5e-5 J/mol/K.
    const real R     = 8.314472e0; // J/mol/K   (SI).
	//const real R = kB*NA;
    const real R_CGS = 8.314472e7; // ergs/mol/K (CGS).
    const real RCAL  = 1.9872e-3;  // kcal/mol/K (calories).


} //namespace MFA

#endif
