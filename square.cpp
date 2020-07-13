//=========================================================================
// COPYRIGHT (c) 1995-2003 by Trinity College Dublin, Dublin 2, IRELAND
// All rights reserved  
//=========================================================================
// Author:                Conor Brennan
// Principal Researcher:  Dr. Peter J. Cullen
// First Modification:    3rd December 2001
// Last Modification:     Dated Below "Added dd/mm/yy"
// Previous Projects:     Storms, FMW/ARG (based on segment.cpp)
// Current  Project:      IP2000 STIWRO
// Software Tool Version: 1.0
//=========================================================================

#include "square3d.hh"

ostream& operator<<( ostream& os, const CSquare3d& sq )
{
  os << "< " << sq.p1() << " , "  << sq.p2() <<  " , " << sq.p3() << " , " << sq.p4() << ">"  << sq.act1() << sq.act2() << sq.act3()  << endl ; 
	
  return os;
}


void CSquare3d::setPointOne( const CPoint3d& PointOne )
{
  v1 = PointOne ; 
}

void CSquare3d::setPointTwo( const CPoint3d& PointTwo )
{
  v2 = PointTwo;
}

void CSquare3d::setPointThree( const CPoint3d& PointThree )
{
  v3 = PointThree;
}

void CSquare3d::setPointFour( const CPoint3d& PointFour )
{
  v4 = PointFour;
}

void CSquare3d::setBasisOne( const int& BasisOne )
{
  b1 = BasisOne ; 
}
void CSquare3d::setBasisTwo( const int& BasisTwo )
{
  b2 = BasisTwo ; 
}
void CSquare3d::setBasisThree( const int& BasisThree )
{
  b3 = BasisThree ; 
}


void CSquare3d::activateBasisOne( )
{
  bas1 = 1 ; 
 }
void CSquare3d::activateBasisTwo( )
{
  bas2 = 1 ; 
 }
void CSquare3d::activateBasisThree( )
{
  bas3 = 1 ; 
 }


CSquare3d& CSquare3d::operator=( const CSquare3d& sq )
{
  v1 = sq.v1;
  v2 = sq.v2;
  v3 = sq.v3 ;
  v4 = sq.v4 ;
	bas1 = sq.bas1 ;
	bas2 = sq.bas2 ;
	bas3 = sq.bas3 ;
	b1  = sq.b1 ; 
	b2  = sq.b2 ; 
	b3  = sq.b3 ; 

  return *this;
}

