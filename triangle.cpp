//=========================================================================
// COPYRIGHT (c) 1995-2003 by Trinity College Dublin, Dublin 2, IRELAND
// All rights reserved  
//=========================================================================
// Author:                Eamonn M. Kenny, Liam O' Brien
// Principal Researcher:  Dr. Peter J. Cullen
// First Modification:    3rd December 2001
// Last Modification:     Dated Below "Added dd/mm/yy"
// Previous Projects:     Storms, FMW/ARG (based on segment.cpp)
// Current  Project:      IP2000 STIWRO
// Software Tool Version: 1.0
//=========================================================================

#include "triangle3d.hh"

ostream& operator<<( ostream& os, const CTriangle3d& tri )
{
  os << "< " << tri.p1() << " , "  << tri.p2() <<  " , " << tri.p3() << ">"    ; 
  return os;
}


void CTriangle3d::setPointOne( const CPoint3d& PointOne )
{
  v1 = PointOne ; 
}

void CTriangle3d::setPointTwo( const CPoint3d& PointTwo )
{
  v2 = PointTwo;
}

void CTriangle3d::setPointThree( const CPoint3d& PointThree )
{
  v3 = PointThree;
}
CTriangle3d& CTriangle3d::operator=( const CTriangle3d& t )
{
  v1 = t.v1;
  v2 = t.v2;
  v3 = t.v3 ;
  return *this;
}

