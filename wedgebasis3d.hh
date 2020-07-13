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

#ifndef WEDGE_BASIS_3D_HH
#define WEDGE_BASIS_3D_HH

#include "point3d.hh"
#include <iostream>
#include "ComplexVector.hh" 

class CWedgeBasis3d 
//=========================================================================
// = FUNCTION 
//     wedgebasis3d.hh
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
  CPoint3d   v1, v2, fc0, fc1  ; 
  int plate, tabulated   ; 
  // v1 = start, v2 = end, fc(0,1) = freecorners
  // fc0 determines the position of Tplus 
  // fc1 determines the position of Tminus 
  // plate tells us which plate the basis is on..
  //  tabulated  tells us whether the basis functions interactions have been tabulated..
  

   

  public:
    //CWedgeBasis3d( CPoint3d p1, CPoint3d q1, CPoint3d fr0, CPoint3d fr1, int the_plate, int tab ) : v1(p1), v2(q1), fc0(fr0), fc1(fr1), plate(the_plate), tabulated(tab) { }
  // Some constructors 
    CWedgeBasis3d( CPoint3d p1, CPoint3d q1, CPoint3d fr0, CPoint3d fr1, int the_plate, int tab ) { 
	    v1 = p1 ; 
	     v2 = q1 ; 
	      fc0 = fr0 ; 
	       fc1  = fr1 ; 
	        plate = the_plate ; 
	       tabulated = tab ; }

	//CWedgeBasis3d( CPoint3d p1, CPoint3 q1, CPoint3d fc0) : v1(p1), v2(q1), fc0(fc0) { }

    CWedgeBasis3d(): v1( CPoint3d( 0.0, 0.0, 0.0 ) ), v2( CPoint3d( 0.0, 0.0, 0.0 ) ), fc0( CPoint3d( 0.0, 0.0, 0.0 ) ), fc1( CPoint3d( 0.0, 0.0, 0.0 )) , plate(0) , tabulated(0)  { }
	

    CWedgeBasis3d( const CWedgeBasis3d& bas ) { v1 = bas.v1, v2 = bas.v2, fc0 = bas.fc0, fc1 = bas.fc1 ,   plate = bas.plate , tabulated = bas.tabulated ;  }
    CWedgeBasis3d& operator=( const CWedgeBasis3d& seg );

    
    CPoint3d p1() const {return v1; }
    CPoint3d p2()   const {return v2; }
    CPoint3d free0() const{ return fc0 ; } 
	CPoint3d free1() const{return fc1;  } 
	int  Plate() const{ return plate  ;  } 
	int  Tabulated() const{  return tabulated;  } 
	//
    // extraction of first or last point of basis
    

    
    double xcoord1() const { return v1.xcoord(); }
    double xcoord2() const { return v2.xcoord(); }
	double fc0xcoord1() const { return fc0.xcoord(); }
    double fc1xcoord2() const { return fc1.xcoord(); }
    
	double ycoord1() const { return v1.ycoord(); }
    double ycoord2() const { return v2.ycoord(); }
    double fc0ycoord1() const { return fc0.ycoord(); }
    double fc1ycoord2() const { return fc1.ycoord(); }

    double zcoord1() const { return v1.zcoord(); }
    double zcoord2() const { return v2.zcoord(); }
double fc0zcoord1() const { return fc0.zcoord(); }
    double fc1zcoord2() const { return fc1.zcoord(); }
    //
    // extraction of coordinates of the segment
    //

    friend ostream& operator<<( ostream& os, const CWedgeBasis3d& seg );
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
