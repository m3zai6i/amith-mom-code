/*
 *  conjugate_gradient.cpp
 *  MOM EFIE
 *
 *  Created by Conor Brennan on 20/07/2011.
 *  Copyright 2011 Dublin City University. All rights reserved.
 *
 */

#include "conjugate_gradient.h"
#include "complex.hh"
#include "complex_functions.hpp"
#include "global_definitions.h"

void cgne()
{
	complex		*r0, *p0, *s0, *t0 ; 
	r0 = new complex[last_edge_number+1] ;
	p0 = new complex[last_edge_number+1] ;
	s0 = new complex[last_edge_number+1] ;
	t0 = new complex[last_edge_number+1] ;
	complex e0, d, a1, b1, y, temp, z, prev_e0;
	
	double tol = 1.0e-20;
	register int k = 0, i;
	
	J = new complex[last_edge_number+1] ; 

	cout << "\n Inversion using cgne starting " << endl << endl;
	
	for ( i = 0; i <= last_edge_number ; i++ )
	{
		r0[i] = complex( 0.0, 0.0 );
		J[i]  = r0[i];
		s0[i] = r0[i];
	}
	
	arr_vec_mult(  V, r0, CONJ, TRANS, last_edge_number, last_edge_number); // r0 = conj(Z)*B
    
	for ( i = 0; i <= last_edge_number; i++ )
	{
    p0[i] = r0[i];  }
	
	
	e0 = inner_prod( r0, r0, CONJ, last_edge_number ); // e0 = sum( r0^2 ) 
	
	prev_e0 = complex(1e-16,0.0) ;
	
	//----- Conjugate gradient squares method as described by Van Der Vorst ----
	
	while (e0.real()  > tol)
	{
		k++;
		d = e0;
		
		arr_vec_mult(  p0, t0, NO_CONJ, NO_TRANS, last_edge_number, last_edge_number );
		arr_vec_mult( t0, s0, CONJ, TRANS, last_edge_number, last_edge_number );
		y = inner_prod( p0, s0, CONJ, last_edge_number ); // y = sum(p0*s0)
		a1 = e0/y; // a1 = e0/y
		
		for ( i = 0; i <= last_edge_number; i++ )
		{
			J[i]  += a1 * p0[i]; // J  = J  + a1*p0
			r0[i] -= a1 * s0[i]; // r0 = r0 - a1*s0
		}
		
		e0 = inner_prod( r0, r0, CONJ, last_edge_number ); // e0 = sum(r0^2)
		b1 = e0/d;
		
		for ( i = 0; i <= last_edge_number; i++ )
		{
			p0[i] = r0[i] + b1 * p0[i]; // p0 = r0 + b1*p0
		}
		
		if( fabs(e0/prev_e0) < 0.1){ 
		cout << "Iteration equals: " << k << ". e0 equals " << e0 << endl ;
		prev_e0 = e0 ; }
		
	}
	cout << "\n Inverted in " << k << " iterations with error "  << e0.real()   << endl ; 
}


//----------- Group of functions necessary to invert a matrix --------------
//-- other functions also needed include cdiv(),cmult(),cadd() and csub() --
//---------- The four functions above are contained in arithmetic.c --------

//---------------- array by vector multiplication --------------------------

void arr_vec_mult(  complex *A, complex *B, int conjugate, int trans,  int N, int M )
{
	register int i,j;
	
	//////////////////////////////////////////////////////////////////////////
	// Parallel Region Starts here using CUDA
	//////////////////////////////////////////////////////////////////////////
	// Calculate conj(Transpose(Z))*X or Transpose(Z)*X
	
	
	for ( i = 0; i <= M; i++ )
	{
		B[i] = complex( 0.0, 0.0 );
		for ( j = 0; j <= N; j++ )
		{
			if (trans == TRANS)
			{
				if ( conjugate == CONJ )
				{
					B[i] += conj( Z[j][i] ) * A[j];
				}
				else if ( conjugate == NO_CONJ )
				{
					B[i] += Z[j][i]  * A[j];
				}
			}
			else if ( trans == NO_TRANS )
			{
				if ( conjugate == CONJ )
				{
					B[i] += conj( Z[i][j]  ) * A[j];
				}
				else if ( conjugate == NO_CONJ )
				{
					B[i] += Z[i][j]  * A[j];
				}
			}
		}
	}
}

	//////////////////////////////////////////////////////////////////////////
	// Parallel region ends
	//////////////////////////////////////////////////////////////////////////
	// calculate the inner product of a vector 

complex inner_prod( complex* z1, complex* z2, int conjugate, int N ) 
{
	
	complex z;
	register int i;
	
	z = complex( 0.0, 0.0 );
	for ( i = 0; i <= N; i++ ) 
	{
		if ( conjugate == CONJ ) z += z1[i] * conj( z2[i] );
		else
			if ( conjugate == NO_CONJ ) z += z1[i] * z2[i];
	}
	return (z);
}


void check_the_answer( ) {
	int ct1, ct2 ; 
	complex sum , error ; 
	
	for(ct1 = 0 ; ct1 <= last_edge_number ; ct1++) { 
		sum = complex(0.0,0.0) ; 
		for(ct2 = 0 ; ct2 <= last_edge_number ; ct2++) { 
			sum = sum + Z[ct1][ct2]*J[ct2] ; 
			}
		error = error + fabs(V[ct1] - sum)*fabs(V[ct1]-sum) ; 
		}
	cout << " Error norm equals " << sqrt(error) << endl ; 
}



