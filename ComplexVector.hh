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

#ifndef COMPLEX_VECTOR_3D_HH
#define COMPLEX_VECTOR_3D_HH

#include "userconst.hh"
#include "point3d.hh"

#include <iostream>
#include <math.h>

class CComplexVector
//==========================================================================
// = FUNCTION 
// 	ComplexVector.hh
//
// = AUTHOR
//      Eamonn M. Kenny
//
// = DESCRIPTION
//   Definition of a structure which will allow the user to manipulate complex
//   vectors in 3D space. Each vector has components x, y and z each of which 
//   are complex. 
//
// = VERSION
//     1.0
//
// = COPYRIGHT
//     COPYRIGHT (c) 1995-2003 by Trinity College Dublin, Dublin 2, IRELAND
//     All rights reserved 
//==========================================================================
{
  public:
    complex x, y, z;

    CComplexVector()
    {
      //   cout << " Constructing Vector!!" << endl;
      x = ComplexZero;
      y = ComplexZero;
      z = ComplexZero;
    }

    CComplexVector( complex x1, complex y1, complex z1)
    {
      x = x1;
      y = y1;
      z = z1;
    }

    CComplexVector( double x1, double y1, double z1)
    {
      x = x1;
      y = y1;
      z = z1;
    }


    CComplexVector( CPoint3d p1, CPoint3d p2)
    {
      x = p1.xcoord() + complex(0.0, 1.0)*p2.xcoord() ;
      y = p1.ycoord() + complex(0.0, 1.0)*p2.ycoord() ;
	  z = p1.zcoord() + complex(0.0, 1.0)*p2.zcoord() ;
	  }

 CComplexVector( CPoint3d p1, complex z)
    {
      x = p1.xcoord() * z ;
      y = p1.ycoord() * z ;
	  z = p1.zcoord() * z   ;
	  }

    CComplexVector( const CPoint3d& v )
    {
      x = v.x;
      y = v.y;
      z = v.z;
    }

    CComplexVector( const CComplexVector&  V1 );
    // Copy constructor 

    CComplexVector&  operator=( const CComplexVector& V1 );
    //
    // Overload = operator
    //

    CComplexVector&  operator=( const CPoint3d&  V1 );
    //
    // Overload = operator (cast a double CPoint3d as a complex CPoint3d)
    //

    boolean   operator==( const CComplexVector&  V1 ) const;
    //
    // Overload == operator
    //

    boolean   operator!=( const CComplexVector&  V1 ) const;
    //
    // Overload != operator
    //

    CComplexVector& operator+=( const CComplexVector&  V1 );
    //
    // Overload += operator
    //

	CComplexVector& operator-=( const CComplexVector&  V1 );
    //
    // Overload -= operator
    //

    CComplexVector operator-( const CComplexVector& V1 ) const;
    //
    // Overload - operator
    //

    CComplexVector  operator+( const CComplexVector& V1 );
    CComplexVector  operator+( const complex& d  );
    //
    // Overload + operator
    //

    CComplexVector& operator*=( const complex& V1 );
    //
    // Overload *= operator
    //

    CComplexVector operator*( const double&  dd );
    CComplexVector operator*( const complex& z ) const;
    //
    // Overloaded multiplication by a complex number
    //

    complex      operator*( const CComplexVector&  v ) const;
    complex      operator*( const CPoint3d& v );
    //
    // Overloaded dot product
    //

    CComplexVector operator/( const complex& d1 ) const;
    CComplexVector operator/( const CComplexVector& v ) const;
    //
    // Overloaded division by a complex number
    //

    CComplexVector   operator^( const CComplexVector V1 );
    //
    // Overloaded cross product 
    //

    CComplexVector  sphericalToRectangular( double theta, double phi );
    //
    // convert a complex vector in spherical polar system to rectangular 
    // system complex vector
    //

    friend ostream& operator<<( ostream& I, const CComplexVector& v );
    //
    // Define the convention for outputting a vector v to the ostream I. 
    //

    double euclideanNorm() const;
    //
    // Euclidean Norm defined for a Complex Vector
    //

	CComplexVector conjvector() ; 

    complex xcoord() const { return x; }
    complex ycoord() const { return y; }
    complex zcoord() const { return z; }
	

    //~CComplexVector(){}
};

#endif
