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

#ifndef FAFFA_GROUP_HH
#define FAFFA_GROUP_HH

#include "point3d.hh"
#include <iostream>

class CFaffaGroup 
//=========================================================================
// = FUNCTION 
//     faffa_group.hh
//
// = AUTHOR
//     Conor Brennan 
//
// = DESCRIPTION
//     A group (square) class with 4 points and corresponding operators
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
  CPoint3d   v1, v2, v3, v4 ; 
  int start_basis, finish_basis ; 
  int southern_aperture, northern_aperture, eastern_aperture, western_aperture, inside_aperture, boundary  ; 
  
  public:
    CFaffaGroup( CPoint3d v11 , CPoint3d v22, CPoint3d v33 , CPoint3d v44 	)
	  : v1(v11), v2(v22), v3(v33) , v4(v44) { }
    CFaffaGroup(): v1( CPoint3d( 0.0, 0.0, 0.0 ) ), 
                  v2( CPoint3d( 0.0, 0.0, 0.0 ) ), 
				   v3( CPoint3d( 0.0, 0.0, 0.0 ) ),  
				    v4( CPoint3d( 0.0, 0.0 , 0.0) )
						{ } 

    CFaffaGroup( const CFaffaGroup& gru ) { v1 = gru.v1; v2 = gru.v2 ; v3 = gru.v3 ; v4 = gru.v4  ;	}
    //
    // construct for CFaffaGroup
    //
   
    CFaffaGroup& operator=( const CFaffaGroup& sq );
    //
    // copy of CFaffaGroup
	//
   

    CPoint3d p1() const {return v1; }
    CPoint3d p2() const {return v2; }
	CPoint3d p3() const {return v3 ;  }
	CPoint3d p4() const {return v4 ;  }
	int		StartBasis() const { return start_basis ; } 
	int		FinishBasis() const { return finish_basis ; } 
	int		Southern() const { return southern_aperture ; } 
	int		Northern() const { return northern_aperture ; } 
	int		Eastern() const { return eastern_aperture ; } 
	int		Western() const { return western_aperture; } 
	int		Inside() const { return inside_aperture; } 
	int		Boundary() const { return boundary; } 
	
    //
    // extraction of the points of group
	//
   CPoint3d centre() const{ return (v1+v2+v3+v4)*0.25 ; } 
   double dimension() const{ return ( sqrt( (v1 - v3)*(v1-v3)  ) *0.5) ;  } 
	//
    // extraction of the basis functions of square
	//
    void setPointOne( const CPoint3d& PointOne );
    void setPointTwo(   const CPoint3d& PointTwo );
    void setPointThree(   const CPoint3d& PointThree );
	void setPointFour(   const CPoint3d& PointFour );
    void setBasisStart( const int& basis ) ; 
	void setBasisFinish( const int& basis ) ; 
    void setSouthern( const int& basis ) ; 
	void setNorthern( const int& basis ) ; 
    void setEastern( const int& basis ) ; 
	void setWestern( const int& basis ) ; 
	void setInside( const int& basis ) ; 
	void setBoundary( const int& temp ) ; 

	//
    // set the values of a group individually
    //

    double xcoord1() const { return v1.xcoord(); }
    double xcoord2() const { return v2.xcoord(); }
	double xcoord3() const { return v3.xcoord(); }
	double xcoord4() const { return v4.xcoord(); }
    double ycoord1() const { return v1.ycoord(); }
    double ycoord2() const { return v2.ycoord(); }
	double ycoord3() const { return v3.ycoord(); }
	double ycoord4() const { return v4.ycoord(); }
    double zcoord1() const { return v1.zcoord(); }
    double zcoord2() const { return v2.zcoord(); }
	double zcoord3() const { return v3.zcoord(); }
	double zcoord4() const { return v4.zcoord(); }

    //
    // extraction of coordinates of the square
    //
 CPoint3d GroupCentre() const;
    //
    // create centre point of group.. 
    //
    friend ostream& operator<<( ostream& os, const CFaffaGroup& sq);
    //
    // Output the square  to a stream
    //
   
   
};

#endif
