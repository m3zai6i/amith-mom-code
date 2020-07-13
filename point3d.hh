//=========================================================================
// COPYRIGHT (c) 2001-2003 by Trinity College Dublin, Dublin 2, IRELAND
// All rights reserved  
//=========================================================================
// Author:                Conor Brennan
// Last Modification:     July 2011
//=========================================================================

#ifndef POINT_3D_HH
#define POINT_3D_HH

#include <iostream>
#include <iomanip>
#include <string>

#include "userconst.hh"
#include "complex.hh"

using namespace std ;



#ifndef __GNUG__
  #define EXPORT_CLASS_DECLSPEC class __declspec(dllexport) 
#else
  #define EXPORT_CLASS_DECLSPEC class
#endif


class CPoint3d
//=========================================================================
// = FUNCTION 
//     point3d.hh    
//
// = AUTHOR
//     Eamonn M. Kenny
//
// = DESCRIPTION
//     operations for points consisting of triples of the form (x,y,z)
//
// = VERSION
//     1.0
//
// = COPYRIGHT
//     COPYRIGHT (c) 1995-1999 by Trinity College Dublin, Dublin 2, IRELAND
//     All rights reserved 
//=========================================================================
{
  public:
    double x, y, z;

    CPoint3d()
    {
      //   cout << " Constructing CPoint3d!!" << endl;
    }

    CPoint3d( double x1, double y1, double z1)
    {
      x = x1;
      y = y1;
      z = z1;
    }

    double xcoord() const { return x; }
    double ycoord() const { return y; }
    double zcoord() const { return z; }
    //
    // functions to return x, y or z component of point
    //

    CPoint3d( const CPoint3d& v1 );
    // Copy constructor 

    CPoint3d&  operator=( const CPoint3d& v1 );
    //
    // Overload = operator
    //

    boolean   operator==( const CPoint3d& v1 ) const;
    //
    // Overload == operator
    //

    boolean   operator!=( const CPoint3d& v1 ) const;
    //
    // Overload != operator
    //

    CPoint3d operator-( const CPoint3d& v1 ) const;
    //
    // Overload - operator
    //

    CPoint3d  operator+( const CPoint3d& v1 ) const;
    //
    // Overload + operator
    //

    CPoint3d operator*( const double& d1 ) const;
    //CPoint3d operator*( const double& d1 );
    //
    // Overloaded multiplication by a scalar operator
    //

	
    double    operator*( const CPoint3d& v ) const;
    //
    // Overloaded dot product
    //

    CPoint3d operator/( const double& d1 ) const;
    //
    // Overloaded division by a scalar operator
    //

    CPoint3d   operator^( const CPoint3d& v1 ) const;
    //
    // Overloaded cross product 
    //

    friend istream& operator>>( istream& I, CPoint3d& v );
    friend ostream& operator<<( ostream& I, const CPoint3d& v );
    //
    // Define the convention for outputting a CPoint3d to the ostream I. 
    //

    friend boolean characterStringToPoint( CPoint3d& v, char* CPoint3dString );
    //
    // read a string and convert into a point.
    //

    double abs() const; 
    double abs( const CPoint3d& p ) const;
    //
    // Define a norm on the point (distance from an origin).
    //

    CPoint3d unitVector() const;
    //
    // create unit vector from current vector 3d point
    //
    friend CPoint3d cross ( const CPoint3d&, const CPoint3d& ) ;
    double cosAngle( const CPoint3d& v );
    double angle( const CPoint3d& v );
    //
    // define the angle between the current vector and the vector v
    //
    
    void clear() {};
    //
    // destroys nothing but required by list.hh class
    //

    ~CPoint3d() {};
};

#endif
