//
//  complex_functions.cpp
//  MOM 3D Flat Plate
//
//  Created by Conor Brennan on 09/06/2020.
//  Copyright © 2020 Conor Brennan. All rights reserved.
//

#include "complex.hh"
#include "complex_functions.hpp"

complex polar( double r, double theta )
{
  return complex(r*cos(theta), r*sin(theta));
}
complex expj( double d )
{
  return( complex( cos(d), sin(d) ) );
}
complex expj( complex v )
{
  return( exp( -v.imag() ) * expj( v.real() ) );
}

complex expminusj( complex v )
{
  return( exp( v.imag() ) * expj( -v.real() ) );
}

complex expminusj( double d )
{
  return( complex( cos(d), -sin(d) ) );
}


double fabs( complex v )
{
  return( sqrt( v.real() * v.real() + v.imag() * v.imag() ) );
}

complex conj( complex v )
{
  return( complex( v.real(), -v.imag() ) );
}

complex sqrt( complex v )
{
  double Angle;

  Angle = atan2( v.imag(), v.real() ) / 2.0;
 
  return( sqrt( fabs( v ) ) * expj( Angle ) );
}

complex exp( complex v )
{
  return( exp( v.real() ) * expj( v.imag() ) );
}

