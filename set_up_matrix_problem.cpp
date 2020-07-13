/*
 *  set_up_matrix_problem.cpp
 *  3D MoM EFIE plate
 *
 *  Created by Conor Brennan on 19/07/2011.
 *  Copyright 2011 Dublin City University. All rights reserved.
 *
 */

#include	"set_up_matrix_problem.h"
#include	"global_definitions.h"
#include	"complex.hh"
#include	"ComplexVector.hh"
#include	"integration_routines.h"
#include  "complex_functions.hpp"



void initialise_incident_field_information(){ 

	double	polarisation_x, polarisation_y, polarisation_z ;
	double	propagation_x, propagation_y, propagation_z ; 
	
	propagation_x = sin(INC_THETA)*cos(INC_PHI) ; 
	propagation_y = sin(INC_THETA)*sin(INC_PHI) ; 
	propagation_z = cos(INC_THETA) ; 
	
	k_v = CPoint3d (propagation_x, propagation_y, propagation_z) ; 
	cout << " Propagation vector equals " << k_v << endl ;
	
	
	polarisation_x =	cos(INC_THETA)*cos(INC_PHI)*cos(INC_ALPHA) - sin(INC_PHI)*sin(INC_ALPHA) ; 
	polarisation_y =	cos(INC_THETA)*sin(INC_PHI)*cos(INC_ALPHA) + cos(INC_PHI)*sin(INC_ALPHA) ; 
	polarisation_z =	-sin(INC_THETA)*cos(INC_ALPHA)  ; 
	
	E0 = CPoint3d(polarisation_x, polarisation_y, polarisation_z) ; 
	cout << " Polarisation vector equals " << E0 << endl ;
	
}


CComplexVector inc_field (CPoint3d k , CPoint3d r , CPoint3d E0, int dipole , int orient, double za ,double the_wave_number) {
	
	CComplexVector result ; 
	CPoint3d x = CPoint3d (1.0, 0.0, 0.0);
	CPoint3d y = CPoint3d (0.0, 1.0, 0.0);
	CPoint3d z = CPoint3d (0.0, 0.0, 1.0);
	complex a;
	double powr;
	
	/***** Results for plane wave *********/
	if( dipole == 0 ) { 
		powr =	( -the_wave_number*(k * r) );
		a = polar (1.0, powr);
		result = CComplexVector  ( ( E0.xcoord() ) * a , (E0.ycoord()) * a, (E0.zcoord()) * a  );
	} 
	else{ 
		if (orient==0){
			
			CPoint3d s = CPoint3d(xa, ya, za);
			CPoint3d R = r - s;
			CPoint3d x = CPoint3d(1.0, 0.0, 0.0);
			CPoint3d y = CPoint3d(0.0, 1.0, 0.0);
			CPoint3d z = CPoint3d(0.0, 0.0, 1.0);
			double cos_phi, cos_theta, sin_phi, sin_theta;
			CPoint3d th;
			CPoint3d v;
			double a, b;
			complex E_r, E_th;
			double dist;
			double beta;
			
			beta = the_wave_number ; 
			v = R / sqrt((R*R));
			a = (v*x);
			b = (v*y) ; 
			cos_phi = cos (atan2 (b,a));
			sin_phi = sin (atan2 (b,a));
			
			dist = sqrt((R*R));
			R = R * (1/dist);
			cos_theta =  (R*z);
			sin_theta = sin (acos(cos_theta));
			th = x * (cos_theta*cos_phi) + y * (cos_theta*sin_phi) - z * sin_theta;
			
			E_r = eta / (2*pi) * (1/pow(dist,2.0) + (complex(1.0,0.0)/complex(0.0,beta*pow(dist,3.0)))) *
		    cos_theta * polar(1.0,-beta*dist);
			//E_th = eta / (4*pi) * (complex(0.0,beta)/dist + 1/pow(dist,2.0) + (complex(1.0,0.0)/complex(0.0,beta*pow(dist,3.0)))) *
			//	     sin_theta * polar(1.0,-beta*dist);
			
			
			// These are the simplified fields of a dipole ... 
			// Ignoring near field effects .. 
			// Just to compare with Eamo's code...
			
			E_th = (eta*length_of_dipole / (4.0*pi*dist)) * (complex(0.0,beta) ) *  sin_theta * polar(1.0,-beta*dist);
			result =  CComplexVector( E_th*(th*x), E_th*(th*y) , E_th*(th*z) ) ; 
			
			
			
			//	return (complex(   (R*(E_r).real()+th*(E_th).real())*x , (R*(E_r).imag()+th*(E_th).imag())*x)   );
			//	return (complex( (R*E_r.real() +th*E_th.real() ) *y ,(R*E_r.imag()+th*E_th.imag())*y) );
			//	return (complex( (R*E_r.real()+ th*E_th.real())*z,(R*E_r.imag()+th*E_th.imag() ) *z));
			
		}
		
	}
	
	
	
	return result ; 
	
}

complex inc_contr (CPoint3d k_v, CPoint3d E0, CPoint3d ro1, CPoint3d ro2, CPoint3d ro3, int opt, int dipole, int orient, double za, double obs_triangle ,double the_wave_number)
{
	
	CPoint3d origin, x_p, y_p;
	complex sum_l, sum_m;
	CPoint3d c1;
	complex elx, ely;
	CPoint3d e_re, e_im;
    CPoint3d proj;
	CPoint3d rocm;
	CComplexVector e_inc  ; 
	
	complex a0;
	
	// calculate the centroid of the triangle
	c1 = (ro1 + ro2 + ro3) / 3.0;
	
	// evaluate rocm - either vector from free corner to centroid or vice versa.
	rocm = (c1 - ro1)*obs_triangle ; 

	// calculate the field at c1
	e_inc = inc_field(k_v, c1, E0, dipole,  orient, za,the_wave_number) ; 
	sum_l = (e_inc*rocm)*0.5 ; 
	
	return (sum_l);
}

complex make_V_element(int i ) {
	double li ; 
	CPoint3d u , ri_plus_1, ri_plus_2, ri_plus_3 ; 
	CPoint3d ri_minus_1, ri_minus_2, ri_minus_3 ; 
	CPoint3d cen_plus_i , cen_minus_i ; 
	int obs_triangle ; 
	complex result ; 
	
	result = complex(0.0,0.0) ;

	li = edges[i].length() ; 

	/**** Compute contribution in plus triangle first ********/
	ri_plus_1 = edges[i].free1() ; 
	ri_plus_2 = edges[i].p1() ; 
	ri_plus_3 = edges[i].p2() ; 
	obs_triangle = 1  ; 
	
	result += li * inc_contr (k_v, E0, ri_plus_1, ri_plus_2, ri_plus_3, 1, dipole,  orient, za, obs_triangle, wave_number );
	
	/**** Now compute contribution in minus triangle first ********/
	
	ri_minus_1 = edges[i].free2() ; 
	ri_minus_2 = edges[i].p1() ; 
	ri_minus_3 = edges[i].p2() ; 
	obs_triangle = -1  ; 
	result += li * inc_contr (k_v, E0, ri_minus_1, ri_minus_2, ri_minus_3, 1, dipole,  orient, za, obs_triangle , wave_number);
	
	return result ; 
	
}

void create_V_vector() { 
	int ct1  ; 
	V = new complex[last_edge_number+1] ; 
	
	for( ct1 = 0 ; ct1 <= last_edge_number ; ct1 ++) { 
			V[ct1] = make_V_element(ct1) ; }	
}







complex make_Z_element( int m , int n, double the_wave_number , int the_derivative ) {
	
	double A_plus_m, lm , obs_triangle, int_triangle  ;
	double A_minus_m ; 
	CPoint3d u, rm_plus_1, rm_plus_2, rm_plus_3 , cen_plus_m ; 
	CPoint3d  rm_minus_1, rm_minus_2, rm_minus_3 , cen_minus_m ; 
	complex Z_element ; 
	double A_plus_n , ln  ; 
	double A_minus_n; 
	CPoint3d  rn_plus_1, rn_plus_2, rn_plus_3 , cen_plus_n ; 
	CPoint3d  rn_minus_1, rn_minus_2, rn_minus_3 , cen_minus_n ; 
	int self_term ; 

	
    Z_element  = complex(0.0, 0.0 ) ; 

	/*	m is the receiving (observation) basis function */

	lm = edges[m].length() ; 
	
	u = cross (edges[m].p2()  - edges[m].free1() , edges[m].p1() - edges[m].free1() );
	A_plus_m = u.abs() / 2.0;
	rm_plus_1 = edges[m].free1() ; 
	rm_plus_2 = edges[m].p1() ; 
	rm_plus_3 = edges[m].p2() ; 
	cen_plus_m = ( rm_plus_1 + rm_plus_2 + rm_plus_3 ) / 3.0  ; 
    // Centroid of observation (i) triangle. 
    obs_triangle = 1.0  ; 
	
    u = cross (edges[m].p2()  - edges[m].free2() , edges[m].p1() - edges[m].free2() );
	A_minus_m = u.abs() / 2.0;
    rm_minus_1 = edges[m].free2() ; 
    rm_minus_2 = edges[m].p1() ; 
    rm_minus_3 = edges[m].p2() ; 
    cen_minus_m = ( rm_minus_1 + rm_minus_2 + rm_minus_3 ) / 3.0  ; 
    obs_triangle = -1.0  ; 
	

	/*	n is the contributing (integration) basis function */
	ln = edges[n].length() ; 
    u = cross (edges[n].p2()  - edges[n].free1() , edges[n].p1() - edges[n].free1() );
	A_plus_n = u.abs() / 2.0;
	rn_plus_1 = edges[n].free1() ; 
	rn_plus_2 = edges[n].p2() ; 
	rn_plus_3 = edges[n].p1() ; 
	cen_plus_n = (rn_plus_1 + rn_plus_2 + rn_plus_3)/3.0 ; 
    // cen_plus_i is the centroid of the integration (j) plus triangle. 
	obs_triangle = 1  ;
	int_triangle  =  1 ; 
	
	
	// This is the plus-plus term 
	
	if (cen_plus_m.abs(cen_plus_n) <  GEOM_TOL ) { /* Basis function triangles overlap - Need special integration routine */  
		self_term  = 1 ;    
		Z_element +=  lm * patch (rn_plus_1, rn_plus_2, rn_plus_3, rm_plus_1, rm_plus_2, rm_plus_3, ln, int_triangle, obs_triangle, A_plus_n, int_opt, the_wave_number) ; 
		}
	else /* Basis function triangles do not overlap - use standard integration routine */
	{ 
		self_term = 0 ; 
		Z_element +=  (lm * factor (rn_plus_1, rn_plus_2, rn_plus_3, rm_plus_1, rm_plus_2, rm_plus_3, ln, int_triangle, obs_triangle, 1, the_wave_number,self_term)); 
	} 
	
	obs_triangle = -1 ; 
	
	// This is the minus-plus term 
	
	if ( cen_minus_m.abs(cen_plus_n)  <   GEOM_TOL  ){ /* Basis function triangles overlap - Need special integration routine */  
		self_term = 1 ; 
		Z_element +=  lm * patch (rn_plus_1, rn_plus_2, rn_plus_3, rm_minus_1, rm_minus_2, rm_minus_3,  ln, int_triangle, obs_triangle , A_plus_n, int_opt, the_wave_number); 
		} 
	else  /* Basis function triangles do not overlap - use standard integration routine */
	{ 
		self_term = 0 ; 
		Z_element += (lm * factor (rn_plus_1, rn_plus_2, rn_plus_3, rm_minus_1, rm_minus_2, rm_minus_3,  ln, int_triangle, obs_triangle, int_opt, the_wave_number,self_term)) ; 
	} 
	
	ln = edges[n].length() ; 
	u = cross (edges[n].p2()  - edges[n].free2() , edges[n].p1() - edges[n].free2() );
	A_minus_n = u.abs() / 2.0;
	rn_minus_1 = edges[n].free2() ; 
	rn_minus_2 = edges[n].p2() ; 
	rn_minus_3 = edges[n].p1() ; 
	cen_minus_n = (rn_minus_1 + rn_minus_2 + rn_minus_3)/3.0 ; 
    // cen_minus_j is the centroid of the integration (j) minus triangle. 
	
	int_triangle = -1 ; 
	obs_triangle = 1 ; 
	
	// This is the plus-minus term 
	
	if (cen_plus_m.abs(cen_minus_n) < GEOM_TOL ) { /* Basis function triangles overlap - Need special integration routine */  
		self_term =1 ; 
		Z_element +=  lm * patch (rn_minus_1, rn_minus_2, rn_minus_3, rm_plus_1, rm_plus_2, rm_plus_3, ln, int_triangle, obs_triangle, A_minus_n, int_opt, the_wave_number)  ; 
	}  
	else/* Basis function triangles do not overlap - use standard integration routine */
	{ 
		self_term = 0 ; 
		Z_element +=  lm * factor (rn_minus_1, rn_minus_2, rn_minus_3, rm_plus_1, rm_plus_2, rm_plus_3, ln, int_triangle, obs_triangle, int_opt, the_wave_number,self_term) ;  
	}
	
	obs_triangle = -1 ; 

	// This is the minus-minus term 

	if (cen_minus_m.abs(cen_minus_n) < GEOM_TOL  )  {   /* Basis function triangles overlap - Need special integration routine */  
		self_term = 1; 
		Z_element +=  lm * patch(rn_minus_1, rn_minus_2, rn_minus_3, rm_minus_1, rm_minus_2, rm_minus_3,  ln, int_triangle, obs_triangle,  A_minus_n, int_opt, the_wave_number) ;  
	} 
	else { 
		self_term =0 ; 
		Z_element +=  lm * factor(rn_minus_1, rn_minus_2, rn_minus_3, rm_minus_1, rm_minus_2, rm_minus_3, ln, int_triangle, obs_triangle, int_opt, the_wave_number,self_term) ;   
	} 
	
	return Z_element ; 
	
	
}

void make_Z_matrix( ){ 
	int ct1, ct2 ; 
	complex temp ; 
	

	Z = new complex*[last_edge_number+1];
			
	
	for( ct1 = 0 ; ct1 <= last_edge_number ; ct1++) { 
	
		Z[ct1] = new complex[last_edge_number+1];

		if( ct1 % 20 == 0 ) 
		cout << "Processing basis function " << ct1 << " of " << last_edge_number << endl ; 
		
		for( ct2 = 0 ; ct2 <= last_edge_number ; ct2++) {
			Z[ct1][ct2] = make_Z_element(ct1,ct2,wave_number,0) ; 
			}	}
		
}




