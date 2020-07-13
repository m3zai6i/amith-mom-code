//
//  complex_functions.hpp
//  MOM 3D Flat Plate
//
//  Created by Conor Brennan on 09/06/2020.
//  Copyright © 2020 Conor Brennan. All rights reserved.
//

#ifndef complex_functions_hpp
#define complex_functions_hpp

#include <stdio.h>
#include "complex.hh"

complex  sqrt( complex v );

// Complex exponentials
complex  exp( complex v );
complex  expminusj( complex d );
complex  expminusj( double d );
complex  expj( complex v );
complex  expj( double d );
complex  polar( double r, double theta);

double   fabs( complex v );
complex  conj( complex v );


#endif /* complex_functions_hpp */
