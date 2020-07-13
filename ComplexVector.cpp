//=========================================================================
// COPYRIGHT (c) 1995-2003 by Trinity College Dublin, Dublin 2, IRELAND
// All rights reserved  
//=========================================================================
// Author:                Eamonn M. Kenny
// Project Manager:       Dr. Peter J. Cullen
// Last Modification:     October 2001
// Previous Projects:     Storms, FMW/ARG
// Current  Project:      IP2000 STIWRO
// Software Tool Version: 1.0
//=========================================================================
#include "ComplexVector.hh"
#include "complex_functions.hpp"

CComplexVector& CComplexVector::operator=( const CComplexVector& v1 )
{
  x = v1.x;
  y = v1.y;
  z = v1.z;
  return *this;
}

CComplexVector& CComplexVector::operator=( const CPoint3d& v1 )
{
  x = complex( v1.x, 0.0 );
  y = complex( v1.y, 0.0 );
  z = complex( v1.z, 0.0 );
  return *this;
}

CComplexVector::CComplexVector( const CComplexVector& v1 )
{
  x = v1.x;
  y = v1.y;
  z = v1.z;
}



boolean CComplexVector::operator==( const CComplexVector& v1 ) const
{
		
	if( fabs ( x - v1.x ) < TOL  && fabs( y - v1.y) < TOL  && fabs (z -  v1.z) < TOL  ) 
	return true ;
	return false;
}

boolean CComplexVector::operator!=( const CComplexVector& v1 ) const
{
  if (*this == v1 ) return false;
  return true;
}

CComplexVector& CComplexVector::operator+=( const CComplexVector& v1 )
{
  x += v1.x;
  y += v1.y;
  z += v1.z;

  return *this;
}

CComplexVector& CComplexVector::operator-=( const CComplexVector& v1 )
{
  x -= v1.x;
  y -= v1.y;
  z -= v1.z;

  return *this;
}

CComplexVector& CComplexVector::operator*=( const complex& v1 )
{
  x *= v1;
  y *= v1;
  z *= v1;

  return *this;
}

CComplexVector CComplexVector::operator-( const CComplexVector& v1 ) const
{
  return CComplexVector( x - v1.x, y - v1.y, z - v1.z );
}

CComplexVector CComplexVector::operator^( const CComplexVector v1 )
{

  return CComplexVector( y * v1.z - z * v1.y, z * v1.x - x * v1.z,
                         x * v1.y - y * v1.x );
}

CComplexVector CComplexVector::operator+( const complex& dd )
{
  return CComplexVector( x + dd, y + dd, z + dd );
}

CComplexVector CComplexVector::operator+( const CComplexVector& v1 )
{
  return CComplexVector( x + v1.x, y + v1.y, z + v1.z );
}

CComplexVector CComplexVector::operator*( const double& dd )
{
  return CComplexVector( x * dd, y * dd, z * dd );
}

CComplexVector CComplexVector::operator*( const complex& dd ) const
{
  return CComplexVector( x * dd, y * dd, z * dd );
}

complex CComplexVector::operator*( const CComplexVector& v ) const
{
  return( x * v.x + y * v.y + z * v.z );
}

complex CComplexVector::operator*( const CPoint3d& v )
{
  return( x * v.x + y * v.y + z * v.z );
}

double CComplexVector::euclideanNorm() const
{
  return( sqrt( qsqr(fabs(x)) + qsqr(fabs(y)) + qsqr(fabs(z)) ) );
}

CComplexVector CComplexVector::operator/( const CComplexVector& v ) const
{
  return CComplexVector( x / v.x, y / v.y, z / v.z );
}

CComplexVector CComplexVector::operator/( const complex& dd ) const
{

  return CComplexVector( x / dd, y / dd, z / dd );
}

CComplexVector CComplexVector::sphericalToRectangular( double theta, double phi)
{
  return CComplexVector( sin( theta ) * cos( phi ) * x + cos( theta ) * cos( phi ) * y 
	                  - sin( phi ) * z, sin( theta ) * sin( phi ) * x + cos( theta ) * sin( phi ) * y 
      + cos( phi ) * z, cos( theta ) * x - sin( theta ) * y );
}

CComplexVector CComplexVector::conjvector()
{
  return( CComplexVector( conj(x), conj(y) , conj(z) ) );
}



ostream&  operator<<( ostream& s, const CComplexVector& v )
{
  return s  << " " << v.x << " " << v.y << " " << v.z;
}
