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

#ifndef SQUARE_3D_HH
#define SQUARE_3D_HH

#include "point3d.hh"
#include <iostream>

using namespace std ;




class CSquare3d 
//=========================================================================
// = FUNCTION 
//     square3d.hh
//
// = AUTHOR
//     Conor Brennan 
//
// = DESCRIPTION
//     A square class with 4 points and corresponding operators
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
  CPoint3d   v1, v2, v3, v4   ; 
  int  b1, b2 , b3  ; 
  boolean	 bas1, bas2, bas3  ; 

  public:
    CSquare3d( CPoint3d v11 , CPoint3d v22, CPoint3d v33 , CPoint3d v44 ) : v1(v11), v2(v22), v3(v33) , v4(v44), bas1(0), bas2(0) , bas3(0) { }
    CSquare3d(): v1( CPoint3d( 0.0, 0.0, 0.0 ) ), 
                  v2( CPoint3d( 0.0, 0.0, 0.0 ) ), 
				   v3( CPoint3d( 0.0, 0.0, 0.0 ) ),  
				    v4( CPoint3d( 0.0, 0.0 , 0.0) ),
					bas1(0),
					bas2(0), 
					bas3(0){ } 

    CSquare3d( const CSquare3d& squ ) { v1 = squ.v1; v2 = squ.v2 ; v3 = squ.v3 ; v4 = squ.v4  ; }
    //
    // construct for CSquare3d
    //
   
    CSquare3d& operator=( const CSquare3d& sq );
    //
    // copy of CSquare3d
    //

    //boolean  operator==(const CSegment3d& seg );
    //boolean  operator!=(const CSegment3d& seg );
    //
    // operators to evaluate if two squares are equal.
    // Not written yet. 

    CPoint3d p1() const {return v1; }
    CPoint3d p2() const {return v2; }
	CPoint3d p3() const {return v3 ;  }
	CPoint3d p4() const {return v4 ;  }
    //
    // extraction of the points of square
	//

	int bf1() const {return b1; }
    int bf2() const {return b2; }
	int bf3() const {return b3 ;  }
	
    //
    // extraction of the basis functions of square
	//
    boolean act1() const {return bas1; }
    boolean act2()   const {return bas2; }
	boolean act3()   const {return bas3 ;  }
	
    void setPointOne( const CPoint3d& PointOne );
    void setPointTwo(   const CPoint3d& PointTwo );
    void setPointThree(   const CPoint3d& PointThree );
	void setPointFour(   const CPoint3d& PointFour );


	void setBasisOne( const int& BasisOne );
    void setBasisTwo(   const int& BasisTwo );
    void setBasisThree(   const int& BasisThree );
	
	void activateBasisOne(  );
    void activateBasisTwo(  );
    void activateBasisThree(  );
	 
	//
    // set the values of a square individually
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


    friend ostream& operator<<( ostream& os, const CSquare3d& sq);
    //
    // Output the square  to a stream
    //
   
   
};

#endif
