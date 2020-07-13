//=========================================================================
// COPYRIGHT (c) 1995-2003 by Trinity College Dublin, Dublin 2, IRELAND
// All rights reserved  
//=========================================================================
// Author:                Conor Brennan 
// Principal Researcher:  Dr. Peter J. Cullen
// First Modification:    15 January 2002
// Last Modification:     15 January 2002
// Previous Projects:     Storms, FMW/ARG (based on segment.hh 2D)
// Current  Project:      IP2000 STIWRO
// Software Tool Version: 1.0
//=========================================================================

#ifndef BASIS_3D_HH
#define BASIS_3D_HH

#include "point3d.hh"
#include <iostream>
//#include "ComplexVector.hh" 

using namespace std ;



class CBasis3d 
//=========================================================================
// = FUNCTION 
//     basis3d.hh
//
// = AUTHOR
//     Conor Brennan
//
// = DESCRIPTION
//     A three dimensional RWG basis class.
//     Based on an old 2D segment implementation
//
// = VERSION
//     1.0
//
// = COPYRIGHT
//     COPYRIGHT (c) 1995-2003 by Trinity College Dublin, Dublin 2, IRELAND
//     All rights reserved 
//=========================================================================
{
private:
  CPoint3d   v1, v2, fc1, fc2  ; 
  
	// v1 = start, v2 = end, fc(1,2) = freecorners
	// fc1 determines the position of Tplus 
	// fc2 determines the position of Tminus 
	

   

  public:
    //CBasis3d( CPoint3d p1, CPoint3d q1, CPoint3d fr0, CPoint3d fr1, int the_plate, int tab ) : v1(p1), v2(q1), fc1(fr0), fc2(fr1) { }
  // Some constructors 
    CBasis3d( CPoint3d p1, CPoint3d q1, CPoint3d fr1, CPoint3d fr2) { 
	    v1 = p1 ; 
	     v2 = q1 ; 
	      fc1 = fr1 ; 
	       fc2  = fr2 ; 
	       }

    CBasis3d(): v1( CPoint3d( 0.0, 0.0, 0.0 ) ), v2( CPoint3d( 0.0, 0.0, 0.0 ) ), fc1( CPoint3d( 0.0, 0.0, 0.0 ) ), fc2( CPoint3d( 0.0, 0.0, 0.0 ))  { }
	

    CBasis3d( const CBasis3d& bas ) { v1 = bas.v1, v2 = bas.v2, fc1 = bas.fc1, fc2 = bas.fc2 ;  }
    CBasis3d& operator=( const CBasis3d& seg );

    
    CPoint3d p1() const {return v1; }
    CPoint3d p2()   const {return v2; }
    CPoint3d free1() const{ return fc1 ; } 
	CPoint3d free2() const{return fc2;  } 
	

    
    double xcoord1() const { return v1.xcoord(); }
    double xcoord2() const { return v2.xcoord(); }
	double fc1xcoord() const { return fc1.xcoord(); }
    double fc2xcoord() const { return fc2.xcoord(); }
    
	double ycoord1() const { return v1.ycoord(); }
    double ycoord2() const { return v2.ycoord(); }
    double fc1ycoord() const { return fc1.ycoord(); }
    double fc2ycoord() const { return fc2.ycoord(); }

    double zcoord1() const { return v1.zcoord(); }
    double zcoord2() const { return v2.zcoord(); }
	double fc1zcoord() const { return fc1.zcoord(); }
    double fc2zcoord() const { return fc2.zcoord(); }
    //
    // extraction of coordinates of the segment
    //

    friend ostream& operator<<( ostream& s, const CBasis3d& seg );

    //
    // Output the segment to a stream
    //

    double length() const;
    //
    // Calculate the length along the segment
    int inside_plus( const CPoint3d& p ) const;    
	int	inside_minus( const CPoint3d& p ) const;    
    
};

#endif
