/*
 *  global_definitions.cpp
 *  3D EFIE MOM
 *
 *  Created by Conor Brennan on 19/07/2011.
 *  Copyright 2011 Dublin City University. All rights reserved.
 *
 */

#include <cmath>

#include "global_definitions.h"
#include "point3d.hh"
#include "square3d.hh"

	double  pi =  acos(-1.0) ; 


/********************************************************************************************/
/********* In this code we assume that we are dealing with a square plate		*************/
/********* we define the length of each side. The centre is at (0,0,0)			*************/
 
	double		side_length  = 1.0  ;

	double		SOUTH_WESTx ; 
	double		SOUTH_WESTy ; 
	double		SOUTH_WESTz ; 

	double		SOUTH_EASTx ; 
	double		SOUTH_EASTy ; 
	double		SOUTH_EASTz ; 

	double		NORTH_EASTx ; 
	double		NORTH_EASTy ; 
	double		NORTH_EASTz ; 

	double		NORTH_WESTx ; 
	double		NORTH_WESTy ; 
	double		NORTH_WESTz ; 


	CPoint3d	plate_corners[4] ; 
 	CPoint3d	plate_centre[1] ; 
	CPoint3d	bounding_box[4] ; 

	CSquare3d	*fine_grid ; 
	CBasis3d	*edges ;
	double		*edges_plus_triangle_area ; 
	double		*edges_minus_triangle_area ; 
	CPoint3d	*edges_plus_centroid ; 
	CPoint3d	*edges_minus_centroid ; 

int			last_edge_number ; 



	
/********	Define some physical parameters	***********************/
/********	Also - define the frequency etc.	*******************/

	double		eps			= 8.85419412e-12;
	double		mu			= 1.256637061e-6;
	double		c			= 1 / sqrt( mu * eps );
	double		MHz			= 1000000.0 ; 
	double		f			= 300.0*MHz    ; 
	double		omega		= 2.0*pi*f ; 
	double		eta			= sqrt(mu/eps) ;   
	double		lambda		= c/f  ; 
	double		wave_number = 2.0*pi/(lambda) ;

	double		edge_length	=	lambda/10.0 ; 
	int			NO_OF_DISCS_PER_SIDE  = ceil(side_length/edge_length) ;
	int			TOTAL_NO_OF_SQUARES  = NO_OF_DISCS_PER_SIDE*NO_OF_DISCS_PER_SIDE ;







/*********	int_opt is a remnant from an old code..	leave set to 1.. Lose this!***/
	int int_opt =  1  ; 


/*****************	Information about the incident field.***********/
/*****************	Can be plane wave or dipole.		************/

	double		INC_THETA =  pi/4.0  ;
	double		INC_ALPHA =	pi    ; 
	double		INC_PHI  = 0.0  ;
	double		big_R = 1000.0 ; // distance for RCS calculation.. 
	double		xa = 0.0*sqrt(3.0) ; 
	double		ya = -10.0*sqrt(3.0) ; 
	double		za = 10.0  ; 
	double		length_of_dipole = lambda/2.0 ; 
	int			dipole = 0; 
	int			orient  = 0 ; 
	CPoint3d	E0 ; 
	CPoint3d	k_v ; 


/******************************************************************/
/****** GEOM_TOL is needed to identify which matrix terms *********/
/******	require special attention ( self terms - possibly	*******/
/******	singular - they require a special integration procedure	***/
/******************************************************************/

double GEOM_TOL =  .00001 ; 

/***********	Information about the linear system to be solved ****/
complex **Z ; 
complex *J ; 
complex *V;

int		CONJ  = -1;
int		NO_CONJ  = 1;
int		TRANS =  1;
int		NO_TRANS  = 0;


/**************	Information used in plotting currents	*************/
/**************	Code computes current along two slices	*************/
/**************	Code also computes contour plot of current on entire surface	*************/

double	disc_length					= lambda/20.0 ; 
double	contour_disc_length			= lambda/10.0 ; 

CPoint3d	current_slice_start[2]	;
CPoint3d	current_slice_finish[2]	;
CPoint3d	field_slice_start[2]	;
CPoint3d	field_slice_finish[2]	;
double		THETA_FOR_PHI_SLICE  = pi/2.0 ; 
double		PHI_FOR_THETA_SLICE  = 0.0 ; 
double		RCS_angle_step_in_degrees = 1.0 ; 
double		RCS_angle_step_in_radians = pi*RCS_angle_step_in_degrees/180.0  ; 



// Current slice information below - Default are horizontal and vertical slices
double	current_slice_start_x0	= -side_length/2.0 ; 
double	current_slice_start_y0	= 0.0  ; 
double	current_slice_finish_x0	= side_length/2.0 ;
double	current_slice_finish_y0	= 0.0  ;

double	current_slice_start_x1	= 0.0 ; 
double	current_slice_start_y1	= -side_length/2.0 ; 
double	current_slice_finish_x1	= 0.0 ;  
double	current_slice_finish_y1	= side_length/2.0 ; 
 
// External field point slice information below 
double	field_slice_start_x0	= -4.0*lambda  ; 
double	field_slice_start_y0	= 0.0  ; 
double	field_slice_start_z0	= 5.0*lambda   ; 

double	field_slice_finish_x0	= 4.0*lambda ;
double	field_slice_finish_y0	= 0.0  ;
double	field_slice_finish_z0	= 5.0*lambda  ;

double	field_slice_start_x1	= -4.0*lambda  ; 
double	field_slice_start_y1	= 0.0  ; 
double	field_slice_start_z1	= -5.0*lambda   ; 

double	field_slice_finish_x1	= 4.0*lambda ;
double	field_slice_finish_y1	= 0.0  ;
double	field_slice_finish_z1	= -5.0*lambda  ;


// Some information about the grid of points to compute fields on

double	field_contour_start_x	= -8.0*lambda  ; 
double	field_contour_start_y	= 0.0  ; 
double	field_contour_start_z	= 8.0*lambda   ; 

CPoint3d	direction1 = CPoint3d(1.0,0.0,0.0) ; 
CPoint3d	direction2 = CPoint3d(0.0,0.0,-1.0) ; 
double		field_grid_distance = 16.0*lambda ; 
double		contour_field_disc_length = lambda/4.0 ; 










