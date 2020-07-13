/*
 *  global_definitions.h
 *  3D EFIE MOM
 *
 *  Created by Conor Brennan on 19/07/2011.
 *  Copyright 2011 Dublin City University. All rights reserved.
 *
 */

#include	"point3d.hh"
#include	"square3d.hh"
#include	"basis3d.hh"

using namespace std ;


extern double  pi  ; 


/********************************************************************************************/
/********* In this code we assume that we are dealing with a square plate		*************/
/********* we define the length of each side. The centre is at (0,0,0)			*************/

extern	double		side_length ; 

extern	double		SOUTH_WESTx ; 
extern	double		SOUTH_WESTy ; 
extern	double		SOUTH_WESTz ; 

extern	double		SOUTH_EASTx ; 
extern	double		SOUTH_EASTy ; 
extern	double		SOUTH_EASTz ; 

extern	double		NORTH_EASTx ; 
extern	double		NORTH_EASTy ; 
extern	double		NORTH_EASTz ; 

extern	double		NORTH_WESTx ; 
extern	double		NORTH_WESTy ; 
extern	double		NORTH_WESTz ; 

extern	int			NO_OF_DISCS_PER_SIDE  ;  
extern	int			TOTAL_NO_OF_SQUARES ; 


extern	CPoint3d	plate_corners[4] ;
extern	CPoint3d	bounding_box[4] ; 

extern 	CPoint3d	plate_centre[1] ; 
extern	CSquare3d	*fine_grid ; 
extern	CBasis3d	*edges ;
extern	double		*edges_plus_triangle_area ; 
extern	double		*edges_minus_triangle_area ; 
extern	CPoint3d	*edges_plus_centroid ; 
extern	CPoint3d	*edges_minus_centroid ; 


extern	int			last_edge_number ; 



/********	Define some physical parameters	***********************/
/********	Also - define the frequency etc.	*******************/

extern	double	eps ;
extern	double	mu ; 
extern	double	c  ; 
extern	double	MHz ; 
extern	double  f  ; 
extern	double	omega ; 
extern	double  lambda ; 
extern	double	wave_number ; 
extern	double	eta  ;

extern	double		edge_length	;
extern	int			NO_OF_DISCS_PER_SIDE ;
extern	int			TOTAL_NO_OF_SQUARES ;




/*********	int_opt is a remnant from an old code..	leave set to 1.. Lose this!***/
extern int int_opt  ; 


/*****************	Information about the incident field.***********/
/*****************	Can be plane wave or dipole.		************/

extern	double		INC_THETA  ; 
extern	double		INC_ALPHA   ; 
extern	double		INC_PHI  ;
extern	double		big_R ; // distance for RCS calculation.. 
extern	CPoint3d	E0 ; 
extern	CPoint3d	k_v ;

extern	double		xa  ;
extern	double		ya ;
extern	double		za ;
extern	double		length_of_dipole ; 
extern	int			dipole ; 
extern	int			orient   ; 

/*****************************************************************/
/****************	Dipole location and length..	**************/
/****************	Also - a flag for choosing		**************/
/****************	dipole incident field or plane	**************/
/****************	wave..							**************/
extern double xa ; 
extern double ya  ; 
extern double za   ; 
extern double length_of_dipole  ; 
extern int dipole ; 
extern int orient   ; 


/******************************************************************/
/****** GEOM_TOL is needed to identify which matrix terms *********/
/******	require special attention ( self terms - possibly	*******/
/******	singular - they require a special integration procedure	***/
/******************************************************************/

extern double GEOM_TOL ; 

extern	complex	**Z ;
extern	complex *J ; 
extern	complex *V ; 

extern	int		CONJ  ;  
extern	int		NO_CONJ   ; 
extern	int		TRANS  ; 
extern	int		NO_TRANS   ; 


/**************	Information used in plotting currents	*************/
extern	double		disc_length ; 
extern	double		contour_disc_length	;


extern	CPoint3d	current_slice_start[2]	;
extern	CPoint3d	current_slice_finish[2]	;
extern	CPoint3d	field_slice_start[2]	;
extern	CPoint3d	field_slice_finish[2]	;

extern	double	current_slice_start_x0	; 
extern	double	current_slice_start_y0	 ; 
extern	double	current_slice_finish_x0	; 
extern	double	current_slice_finish_y0	; 

extern	double	current_slice_start_x1	 ;
extern	double	current_slice_start_y1	; 
extern	double	current_slice_finish_x1	; 
extern	double	current_slice_finish_y1	;

// External field point slice information below 
extern	double	field_slice_start_x0	; 
extern	double	field_slice_start_y0	; 
extern	double	field_slice_start_z0	;

extern	double	field_slice_finish_x0	;
extern	double	field_slice_finish_y0	; 
extern	double	field_slice_finish_z0	;

extern	double	field_slice_start_x1	 ; 
extern	double	field_slice_start_y1	;
extern	double	field_slice_start_z1	;

extern	double	field_slice_finish_x1	;
extern	double	field_slice_finish_y1	 ; 
extern	double	field_slice_finish_z1	;


// Some information about the grid of points to compute fields on

extern	double	field_contour_start_x; 
extern	double	field_contour_start_y ; 
extern	double	field_contour_start_z ; 

extern	CPoint3d	direction1  ; 
extern	CPoint3d	direction2  ; 
extern	double	field_grid_distance  ; 
extern	double		contour_field_disc_length ; 


extern	double		THETA_FOR_PHI_SLICE   ; 
extern	double		PHI_FOR_THETA_SLICE  ; 
extern	double		RCS_angle_step_in_degrees  ; 
extern	double		RCS_angle_step_in_radians ; 

