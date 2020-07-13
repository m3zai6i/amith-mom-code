/*
 *  visualise_currents.h
 *  MOM EFIE
 *
 *  Created by Conor Brennan on 21/07/2011.
 *  Copyright 2011 Dublin City University. All rights reserved.
 *
 */

#include	"ComplexVector.hh" 

CComplexVector	contribute_current( CPoint3d field_point, int edge_number, int triangle_type)  ; 
void			compute_currents_along_lines() ;
void			compute_incident_fields_on_grid() ; 
void			compute_currents_on_grid(); 
void			compute_fields_along_lines() ;

CComplexVector  get_field( CPoint3d field_point, double the_wave_number) ;

void			compute_fields_along_grid()   ; 
void			compute_far_field_patterns()  ; 

double			get_RCS( CPoint3d field_point, double the_wave_number) ;
