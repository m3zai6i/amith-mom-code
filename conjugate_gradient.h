/*
 *  conjugate_gradient.h
 *  MOM EFIE
 *
 *  Created by Conor Brennan on 20/07/2011.
 *  Copyright 2011 Dublin City University. All rights reserved.
 *
 */

using namespace std ; 
#include "complex.hh"

void	cgne( ) ; 

void	arr_vec_mult(   complex *A, complex *B, int conjugate, int trans,  int N, int M );

complex inner_prod( complex* z1, complex* z2, int conjugate, int N ) ;
void	check_the_answer( )  ; 


