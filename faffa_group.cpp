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

#include "faffa_group.hh"

ostream& operator<<( ostream& os, const CFaffaGroup& sq )
{
  os << "< " << sq.p1() << " , "  << sq.p2() <<  " , " << sq.p3() << " , " << sq.p4() << ">"  << " Southern: " << sq.Southern() << " Northern: " << 
	 sq.Northern() << " Eastern: " << sq.Eastern() << "Western: " << sq.Western() << " Inside: " <<   sq.Inside() <<   "Boundary: " << sq.Boundary() << endl ; 
  return os;
}


void CFaffaGroup::setPointOne( const CPoint3d& PointOne )
{
  v1 = PointOne ; 
}

void CFaffaGroup::setPointTwo( const CPoint3d& PointTwo )
{
  v2 = PointTwo;
}

void CFaffaGroup::setPointThree( const CPoint3d& PointThree )
{
  v3 = PointThree;
}

void CFaffaGroup::setPointFour( const CPoint3d& PointFour )
{
  v4 = PointFour;
}

void CFaffaGroup::setSouthern( const int& aperture )
{
  southern_aperture = aperture;
}

void CFaffaGroup::setNorthern( const int& aperture )
{
  northern_aperture = aperture;
}

void CFaffaGroup::setEastern( const int& aperture )
{
  eastern_aperture = aperture;
}

void CFaffaGroup::setWestern( const int& aperture )
{
  western_aperture = aperture;
}

void CFaffaGroup::setInside( const int& aperture )
{
  inside_aperture = aperture;
}

void CFaffaGroup::setBoundary( const int& temp )
{
  boundary =  temp ;
}


void CFaffaGroup::setBasisStart( const int& basis )
{
  start_basis = basis;
}


void CFaffaGroup::setBasisFinish( const int& basis )
{
  finish_basis = basis;
}

CFaffaGroup& CFaffaGroup::operator=( const CFaffaGroup& sq )
{
  v1     = sq.v1;
  v2     = sq.v2;
  v3     = sq.v3;
  v4     = sq.v4;
  return *this;
}

CPoint3d CFaffaGroup::GroupCentre() const
{
  CPoint3d p2;

  p2 = (v1 + v2 + v3 + v4 )*0.25 ; 
  return p2;
}

