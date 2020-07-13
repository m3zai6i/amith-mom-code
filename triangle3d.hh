//=========================================================================
// COPYRIGHT (c) 1995-2003 by Trinity College Dublin, Dublin 2, IRELAND
// All rights reserved  
//=========================================================================
// Author:                Conor Brennan
// Principal Researcher:  Dr. Peter J. Cullen
// First Modification:    14th January 2002
// Last Modification:     Dated Below "Added dd/mm/yy"
// Previous Projects:     Storms, FMW/ARG (Based on old segment3d.hh) 
// Current  Project:      IP2000 STIWRO
// Software Tool Version: 1.0
//=========================================================================

#ifndef TRIANGLE_3D_HH
#define TRIANGLE_3D_HH

#include "point3d.hh"
#include <iostream>

class CTriangle3d 
//=========================================================================
// = FUNCTION 
//     triangle3d.hh
//
// = AUTHOR
//     Conor Brennan 
//
// = DESCRIPTION
//     A triangle class with 3 points and corresponding operators
//     in three dimensions. 
//
// = VERSION
//     1.0
//
// = COPYRIGHT
//     COPYRIGHT (c) 1995-2003 by Trinity College Dublin, Dublin 2, IRELAND
//     All rights reserved 
//=========================================================================
{
  CPoint3d   v1, v2, v3; 

  public:
    CTriangle3d( CPoint3d v11 , CPoint3d v22, CPoint3d v33 ) : v1(v11), v2(v22), v3(v33) { }
    CTriangle3d(): v1( CPoint3d( 0.0, 0.0, 0.0 ) ), 
                   v2( CPoint3d( 0.0, 0.0, 0.0 ) ), 
                   v3( CPoint3d( 0.0, 0.0, 0.0 ) )  { }
    CTriangle3d( const CTriangle3d& tri ) 
    { v1 = tri.v1; v2 = tri.v2 ; v3 = tri.v3 ; }
    //
    // construct for CTringle3d
    //
   
    CTriangle3d& operator=( const CTriangle3d& tri );
    //
    // copy of CTriangle3d
    //

    //boolean  operator==(const CSegment3d& seg );
    //boolean  operator!=(const CSegment3d& seg );
    //
    // operators to evaluate if two triangles are equal.
    // Not written yet. 

    CPoint3d p1() const {return v1; }
    CPoint3d p2() const {return v2; }
    CPoint3d p3() const {return v3; }
    //
    // extraction of the points of triangles
    //

    void setPointOne( const CPoint3d& PointOne );
    void setPointTwo(   const CPoint3d& PointTwo );
    void setPointThree(   const CPoint3d& PointThree );

    //
    // set the points of a triangle individually
    //

    double xcoord1() const { return v1.xcoord(); }
    double xcoord2() const { return v2.xcoord(); }
    double xcoord3() const { return v3.xcoord(); }
    double ycoord1() const { return v1.ycoord(); }
    double ycoord2() const { return v2.ycoord(); }
    double ycoord3() const { return v3.ycoord(); }
    double zcoord1() const { return v1.zcoord(); }
    double zcoord2() const { return v2.zcoord(); }
    double zcoord3() const { return v3.zcoord(); }

    //
    // extraction of coordinates of the triangle 
    //

    friend ostream& operator<<( ostream& os, const CTriangle3d& seg );
    //
    // Output the triangle  to a stream
    //
};

#endif
