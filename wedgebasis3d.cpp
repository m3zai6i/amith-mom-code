//=========================================================================
// COPYRIGHT (c) 1995-2003 by Trinity College Dublin, Dublin 2, IRELAND
// All rights reserved  
//=========================================================================
// Author:                Conor Brennan
// Principal Researcher:  Dr. Peter J. Cullen
// First Modification:    15 January 2002
// Last Modification:     Dated Below "Added dd/mm/yy"
// Previous Projects:     Storms, FMW/ARG (based on segment.cpp)
// Current  Project:      IP2000 STIWRO
// Software Tool Version: 1.0
//=========================================================================

#include "wedgebasis3d.hh"

ostream& operator<<( ostream& os, const CWedgeBasis3d& bas )
{

  os << "Basis end points at " << bas.p1() << " and  " << bas.p2() << "\n It has free corners at" << bas.free0() << " and  " << bas.free1() << " It is on plate " << bas.Plate() << " Tabulation equals " << bas.Tabulated() << endl ;
  return os;
}
double CWedgeBasis3d::length() const
{
  return sqrt(( v1 - v2 ) * ( v1- v2 ));
}

CWedgeBasis3d& CWedgeBasis3d::operator=( const CWedgeBasis3d& bas )
{
  v1 = bas.p1();
  v2 = bas.p2();
  fc0 = bas.free0() ; 
  fc1 = bas.free1(); 
  plate = bas.Plate() ; 
  tabulated = bas.Tabulated(); 
   return *this;
}



int CWedgeBasis3d::inside_plus( const CPoint3d& p ) const
{
  
  int result  ; 
  // Check T_plus first ..... 
  CComplexVector vec1, vec2, cross_p1, cross_p2 , cross_p3 ;
  
	result = 0 ; 

	vec1 = v2 - v1 ; 
	vec2 = p - v1 ; 
	cross_p1  =  vec1^vec2 ; 

if( vec1/vec1.euclideanNorm()  == vec2/vec2.euclideanNorm() ) { 
if( vec1.euclideanNorm() >= vec2.euclideanNorm() ) { 
   result = 2 ; 
		 } 
	} 



	vec1 = v1 - fc0 ; 
	vec2 = p - fc0 ; 
	cross_p2  =  vec1^vec2 ;

 	vec1 = fc0 - v2 ; 
	vec2 = p - v2 ; 
	cross_p3  =  vec1^vec2 ;
	 

 if( result != 2 ) { 
	if( (cross_p3*cross_p2).real() > 0.0  ) { 
		if( (cross_p1*cross_p3).real() > 0.0 )   { 
				 result = 1 ; 
				 	}} 
 } 


	return result  ; 

}

int CWedgeBasis3d::inside_minus( const CPoint3d& p ) const
{
  int result  = 0  ; 
  CComplexVector vec1, vec2, cross_p1, cross_p2 , cross_p3 ;
    
	vec1 = v2 - v1 ; 
	vec2 = p - v1 ; 
	cross_p1  =  vec1^vec2; 
	 if( vec1/vec1.euclideanNorm()  == vec2/vec2.euclideanNorm() ) { 
	if( vec1.euclideanNorm() >= vec2.euclideanNorm() ) { 
	   result = 2 ; 
		 } } 

	vec1 = v1 - fc1 ; 
	vec2 = p - fc1 ; 
	cross_p2  =  vec1^vec2 ;


	vec1 = fc1 - v2 ; 
	vec2 = p - v2 ; 
	cross_p3  =  vec1^vec2 ;

	if( result != 2 ){ 			
	if( (cross_p3*cross_p2).real() > 0.0  ) { 
		if( (cross_p1*cross_p3).real() > 0.0) { 
			 result = 1 ; 
	}} } 
    
    
   	return result  ; 

}
