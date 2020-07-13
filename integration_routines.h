/*
 *  integration_routines.h
 *  MOM EFIE
 *
 *  Created by Conor Brennan on 20/07/2011.
 *  Copyright 2011 Dublin City University. All rights reserved.
 *
 */

#include	"complex.hh"
#include	"point3d.hh"
#include	"ComplexVector.hh" 



void	self(CPoint3d r1, CPoint3d r2, CPoint3d r3,  complex *Magnx, 
				 complex *Magny, complex *Phi, double Aq, CPoint3d centr, double the_wave_number) ;
complex patch(CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d ro1, CPoint3d ro2, CPoint3d ro3,
				 double ln, double mult, double obs_triangle , double Aq, int opt, double the_wave_number) ;

void	imped(CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d centr, complex *I, complex *Icsi, complex *Ieta,
				 double the_wave_number,  int the_self_term ) ;

complex factor(CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d ro1, CPoint3d ro2, CPoint3d ro3,
				double ln, double mult, double obs_triangle, int opt, double the_wave_number,  int self_term) ;

complex fun1(double k, double eta, double csi, CPoint3d r1, 
				 CPoint3d r2, CPoint3d r3, CPoint3d rcp, int the_derivative, int the_self_term);

complex fun2(double k, double eta, double csi, CPoint3d r1, 
				 CPoint3d  r2, CPoint3d r3, CPoint3d rcp, int the_derivative, int the_self_term);

complex fun3(double k, double eta, double csi, CPoint3d  r1,  
				 CPoint3d r2, CPoint3d r3, CPoint3d rcp, int the_derivative,int the_self_term);

complex fa(double k, double xcp, double q, double m, double phi) ;
complex fb(double k, double ycp, double q, double m, double phi) ;
complex fc(double k, double q, double m, double phi) ;
double	ro(double phi, double q, double m) ;



CComplexVector  A_scatter( CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d field_point, double lj, double the_wave_number) ;
CComplexVector  phi_scatter( CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d field_point, double lj, double the_wave_number) ;

void			imped2 (CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d centr, complex *I2, complex *Icsi, complex *Ieta, double the_wave_number) ;
complex			phi_fun1 (double k, double eta, double csi, CPoint3d r1,  CPoint3d r2, CPoint3d r3, CPoint3d rcp) ;
complex			phi_fun2 (double k, double eta, double csi, CPoint3d r1, CPoint3d  r2, CPoint3d r3, CPoint3d rcp ) ;
complex			phi_fun3 (double k, double eta, double csi, CPoint3d  r1, CPoint3d r2, CPoint3d r3, CPoint3d rcp) ;


CComplexVector  RCS_scatter( CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d field_point, double lj, double the_wave_number) ;

void imped_rcs (CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d centr, complex *I, complex *Icsi, complex *Ieta, double the_wave_number ) ;

complex			RCS_fun1 (double k, double eta, double csi, CPoint3d r1,  CPoint3d r2, CPoint3d r3, CPoint3d rcp) ;
complex			RCS_fun2 (double k, double eta, double csi, CPoint3d r1, CPoint3d  r2, CPoint3d r3, CPoint3d rcp ) ;
complex			RCS_fun3 (double k, double eta, double csi, CPoint3d  r1, CPoint3d r2, CPoint3d r3, CPoint3d rcp) ;


