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

#include	"basis3d.hh"
#include	"ComplexVector.hh"

ostream& operator<<( ostream& s, const CBasis3d& bas )
{

  s << "Basis end points at " << bas.p1() << " and  " << bas.p2() << "\n It has free corners at" << bas.free1() << " and  " << bas.free2() ;
  return s;
}

double CBasis3d::length() const
{
  return sqrt(( v1 - v2 ) * ( v1- v2 ));
}

CBasis3d& CBasis3d::operator=( const CBasis3d& bas )
{
  v1 = bas.p1();
  v2 = bas.p2();
  fc1 = bas.free1() ; 
  fc2 = bas.free2(); 
   return *this;
}



int CBasis3d::inside_plus( const CPoint3d& p ) const
{
  
  int result  ; 
  CComplexVector vec1, vec2, cross_p1, cross_p2 , cross_p3 ;
  
	result = 0 ; 

	vec1 = v2 - v1 ; 
	vec2 = p - v1 ; 
	cross_p1  =  vec1^vec2 ; 


// Check to see whether the point is on the basis edge. 
if( vec1/vec1.euclideanNorm()  == vec2/vec2.euclideanNorm() ) { 
if( vec1.euclideanNorm() >= vec2.euclideanNorm() ) { 
	if( (vec1*vec2).real() > 0.0 ){  
   result = 2 ; // This means that the point is in both T+ and T-. 
				// Be careful not to double count.
	}
		 } 
	} 

	vec1 = v1 - fc1 ; 
	vec2 = p - fc1 ; 
	cross_p2  =  vec1^vec2 ;

	if( vec1/vec1.euclideanNorm()  == vec2/vec2.euclideanNorm() ) { 
		if( vec1.euclideanNorm() >= vec2.euclideanNorm() ) { 
			if( (vec1*vec2).real() > 0.0 ){  
				result = 3 ; 
			}		}}
	
 	vec1 = fc1 - v2 ; 
	vec2 = p - v2 ; 
	cross_p3  =  vec1^vec2 ;
	
	if( vec1/vec1.euclideanNorm()  == vec2/vec2.euclideanNorm() ) { 
		if( vec1.euclideanNorm() >= vec2.euclideanNorm() ) { 
			if( (vec1*vec2).real() > 0.0 ){  
				result = 4 ; 
			}		}}
	
 if( result != 2 ) { 
	if( (cross_p3*cross_p2).real() > 0.0  ) { 
		if( (cross_p1*cross_p3).real() > 0.0 )   { 
				 result = 1 ; 
				 	}} 
 } 


	return result  ; 

}

int CBasis3d::inside_minus( const CPoint3d& p ) const
{
  int result  = 0  ; 
  CComplexVector vec1, vec2, cross_p1, cross_p2 , cross_p3 ;
    
	vec1 = v2 - v1 ; 
	vec2 = p - v1 ; 
	cross_p1  =  vec1^vec2; 
	
	 if( vec1/vec1.euclideanNorm()  == vec2/vec2.euclideanNorm() ) { 
	if( vec1.euclideanNorm() >= vec2.euclideanNorm() ) { 
		if( (vec1*vec2).real() > 0 ){  
	   result = 2 ; 
		}} } 

	vec1 = v1 - fc2 ; 
	vec2 = p - fc2 ; 
	cross_p2  =  vec1^vec2 ;

	
	if( vec1/vec1.euclideanNorm()  == vec2/vec2.euclideanNorm() ) { 
		if( vec1.euclideanNorm() >= vec2.euclideanNorm() ) { 
			if( (vec1*vec2).real() > 0.0 ){  
				result = 3 ; 
			}		}} 
	
	vec1 = fc2 - v2 ; 
	vec2 = p - v2 ; 
	cross_p3  =  vec1^vec2 ;

	
	if( vec1/vec1.euclideanNorm()  == vec2/vec2.euclideanNorm() ) { 
		if( vec1.euclideanNorm() >= vec2.euclideanNorm() ) { 
			if( (vec1*vec2).real() > 0.0 ){  
				result = 4 ; 
			}		}}
	
	
	if( result != 2 ){ 			
	if( (cross_p3*cross_p2).real() > 0.0  ) { 
		if( (cross_p1*cross_p3).real() > 0.0) { 
			 result = 1 ; 
	}} } 
    
    
   	return result  ; 

}

