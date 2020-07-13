/*
 *  visualise_currents.cpp
 *  MOM EFIE
 *
 *  Created by Conor Brennan on 21/07/2011.
 *  Copyright 2011 Dublin City University. All rights reserved.
 *
 */

#include	"visualise_currents_and_fields.h"
#include	"global_definitions.h"
#include	"ComplexVector.hh"
#include	"set_up_matrix_problem.h"
#include	"integration_routines.h"

CComplexVector	contribute_current( CPoint3d field_point, int edge_number, int triangle_type) {
CComplexVector	result ; 

	
	if(triangle_type == 1) 
		result = (CComplexVector(field_point - edges[edge_number].free1()))*(edges[edge_number].length()*0.5/edges_plus_triangle_area[edge_number])*J[edge_number] ; 
	if(triangle_type == -1) 
		result = (CComplexVector(edges[edge_number].free2() - field_point))*(edges[edge_number].length()*0.5/edges_minus_triangle_area[edge_number])*J[edge_number] ; 
	
return result ; 
}

void			compute_currents_on_grid(){
	int				ct1, ct2, ct3, NO_OF_STEPS , inside_the_plus_triangle, inside_the_minus_triangle; 
	CPoint3d		field_point, step1, step2, temp_vec ;
	CComplexVector	the_current ; 
	ofstream		the_output ; 
	
	int number_of_basis_functions = 0  ; 
	
    // The following directory structure must exist! Otherwise file not written
	the_output.open("../../../../../../../../MOM 3D Flat Plate/output_data/currents_contour.res") ;
	
	
	NO_OF_STEPS = ceil((plate_corners[1] - plate_corners[0]).abs()/contour_disc_length) ; 
	
	the_output << omega << " " << 0.0 << " " << 0.0 << " " << 0.0 << endl ; 
	the_output << NO_OF_STEPS + 1 << " " << 0.0 << " " << 0.0 << " " << 0.0 << endl ; 
	
	step1 =		(bounding_box[1] - bounding_box[0])/NO_OF_STEPS ;	//	Step in x direction
	step2 =		(bounding_box[3] - bounding_box[0])/NO_OF_STEPS ;	//	Step in y direction
	
	for(ct1 = 0 ; ct1 <= NO_OF_STEPS ; ct1++) {
		if(ct1%10 ==0) 
			cout <<  "Processing contour current - ct1 equals " << ct1 << " of " << NO_OF_STEPS << endl ; 
		
		for(ct2 = 0 ; ct2 <= NO_OF_STEPS ; ct2++) {
			
			number_of_basis_functions = 0  ; 
			
			field_point		= bounding_box[0] + step1*(ct2) + step2*(ct1) ; 
			
			the_current = CComplexVector() ; 
			
			for(ct3 = 0 ; ct3 <= last_edge_number ; ct3++) { 
				
			
				inside_the_plus_triangle = edges[ct3].inside_plus(field_point) ; 
				
				if(inside_the_plus_triangle == 2){ 
					temp_vec = edges[ct3].free1() - field_point ; 
					field_point = field_point - temp_vec*edges[ct3].length()/10000.0; 
				}
				if(inside_the_plus_triangle == 3){ 
					temp_vec = edges[ct3].p2() - field_point ; 
					field_point = field_point - temp_vec*edges[ct3].length()/10000.0 ; 
				}
				if(inside_the_plus_triangle == 4){ 
					temp_vec = edges[ct3].p1() - field_point ; 
					field_point = field_point - temp_vec*edges[ct3].length()/10000.0 ; 
				}
				
					
				if(inside_the_plus_triangle == 1) 
				{
					the_current = the_current + contribute_current(field_point,ct3,1) ; 
					number_of_basis_functions ++ ; 
				} 
				
				inside_the_minus_triangle = edges[ct3].inside_minus(field_point) ; 
				
				if(inside_the_minus_triangle == 2){ 
					temp_vec = edges[ct3].free2() - field_point ; 
					field_point = field_point - temp_vec*edges[ct3].length()/10000.0 ; 
				}
				if(inside_the_minus_triangle == 3){ 
					temp_vec = edges[ct3].p2() - field_point ; 
					field_point = field_point - temp_vec*edges[ct3].length()/10000.0 ; 
				}
				if(inside_the_minus_triangle == 4){ 
					temp_vec = edges[ct3].p1() - field_point ; 
					field_point = field_point - temp_vec*edges[ct3].length()/10000.0 ; 
				}
				
					
				if( inside_the_minus_triangle == 1)   
				{
					the_current = the_current + contribute_current(field_point,ct3,-1) ; 
					number_of_basis_functions ++ ; 
					}
				
				
			}
		
			/*if(number_of_basis_functions > 3 ) {
				cout << " More than 3 basis functions: There are " << number_of_basis_functions << endl ; 
			cout << " Field point equals " << field_point << endl ; 
			cout << " Field point x+y equals " << field_point.xcoord() + field_point.ycoord() << endl ; 
			} */
			
			the_output << the_current.xcoord() <<  " " << the_current.ycoord() << endl ; 

			
		}
	}
	
	the_output.close() ; 
}

void compute_currents_along_lines(){
	CPoint3d		the_step, field_point ; 
	int				ct1, ct2, ct3, NO_OF_STEPS, inside_the_plus_triangle, inside_the_minus_triangle ; 
	double			slice_length ;
	CComplexVector	the_current ; 
	ofstream		current1, current2  ;
	CPoint3d		temp_vec ;
	
	current1.open("../../../../../../../../MOM 3D Flat Plate/output_data/current_values1.res") ;
	current2.open("../../../../../../../../MOM 3D Flat Plate/output_data/current_values2.res") ;
	
	current_slice_start[0]	=	CPoint3d(current_slice_start_x0, current_slice_start_y0,0.0) ;
	current_slice_finish[0]	=	CPoint3d(current_slice_finish_x0, current_slice_finish_y0,0.0) ;	
	current_slice_start[1]	=	CPoint3d(current_slice_start_x1, current_slice_start_y1,0.0) ;
	current_slice_finish[1]	=	CPoint3d(current_slice_finish_x1, current_slice_finish_y1,0.0) ;	
	
	for(ct1 = 0 ; ct1 < 2 ; ct1++) {
		
		slice_length = (current_slice_finish[ct1] - current_slice_start[ct1]).abs() ; 
		NO_OF_STEPS  =	ceil(slice_length/disc_length) ;
		the_step  = (current_slice_finish[ct1] - current_slice_start[ct1])/(double)NO_OF_STEPS ; 
		
		for(ct2 = 0 ; ct2 < NO_OF_STEPS ; ct2++) { 
			field_point = current_slice_start[ct1] + the_step*(ct2+0.5);	
			the_current = CComplexVector() ;
			
			for(ct3 = 0 ; ct3 <= last_edge_number ; ct3++) { 
				
				inside_the_plus_triangle = edges[ct3].inside_plus(field_point) ;
				if(inside_the_plus_triangle == 2){ 
					temp_vec = edges[ct3].free1() - field_point ; 
					field_point = field_point - temp_vec*edges[ct3].length()/10000.0; 
				}
				if(inside_the_plus_triangle == 3){ 
					temp_vec = edges[ct3].p2() - field_point ; 
					field_point = field_point - temp_vec*edges[ct3].length()/10000.0 ; 
				}
				if(inside_the_plus_triangle == 4){ 
					temp_vec = edges[ct3].p1() - field_point ; 
					field_point = field_point - temp_vec*edges[ct3].length()/10000.0 ; 
				}
				
				if(inside_the_plus_triangle == 1 ) 
				{
					the_current = the_current + contribute_current(field_point,ct3,1) ; 
				} 
				
				inside_the_minus_triangle = edges[ct3].inside_minus(field_point) ; 
				
				if(inside_the_minus_triangle == 2){ 
					temp_vec = edges[ct3].free2() - field_point ; 
					field_point = field_point - temp_vec*edges[ct3].length()/10000.0 ; 
				}
				if(inside_the_minus_triangle == 3){ 
					temp_vec = edges[ct3].p2() - field_point ; 
					field_point = field_point - temp_vec*edges[ct3].length()/10000.0 ; 
				}
				if(inside_the_minus_triangle == 4){ 
					temp_vec = edges[ct3].p1() - field_point ; 
					field_point = field_point - temp_vec*edges[ct3].length()/10000.0 ; 
				}
				
				if(inside_the_minus_triangle == 1 ) 
				{
					the_current = the_current + contribute_current(field_point,ct3,-1) ; 
				}
				
			} // end of ct3 
		
			if(ct1 == 0) 
				current1 << the_step.abs()*(ct2+0.5) << " " << the_current.xcoord() << " " <<  the_current.ycoord() << "  " << the_current.zcoord() << endl ; 
			if(ct1 == 1) 
				current2 << the_step.abs()*(ct2+0.5) << " " << the_current.xcoord() << " " <<  the_current.ycoord() << "  " << the_current.zcoord() << endl ; 
			
		} // end of ct2  
				
	}// end of ct1
	current1.close() ;
	current2.close() ;
	
}

void			compute_incident_fields_on_grid(){
	int				ct1, ct2, NO_OF_STEPS ; 
	CPoint3d		field_point, step1, step2 ;
	CComplexVector	the_inc_field ; 
	ofstream		the_output ; 
	
	the_output.open("../../../../../../../../MOM 3D Flat Plate/output_data/incident_fields_contour.res") ;
	
	
	NO_OF_STEPS = ceil((plate_corners[1] - plate_corners[0]).abs()/disc_length) ; 
	
	the_output << omega << " " << 0.0 << endl ; 
	the_output << NO_OF_STEPS << " " << 0.0 << endl ; 
	
	step1 =		(bounding_box[1] - bounding_box[0])/NO_OF_STEPS ;	//	Step in x direction
	step2 =		(bounding_box[3] - bounding_box[0])/NO_OF_STEPS ;	//	Step in y direction
	
	for(ct1 = 0 ; ct1 < NO_OF_STEPS ; ct1++) {
		for(ct2 = 0 ; ct2 < NO_OF_STEPS ; ct2++) {
			
			field_point		= bounding_box[0] + step1*(ct2+0.5) + step2*(ct1*0.5) ; 
			the_inc_field	= inc_field(k_v, field_point, E0, dipole, orient, za, wave_number); 
			the_output << the_inc_field.xcoord() << endl ; 
		}
	}
	
	the_output.close() ; 
}


/******************************************************************/
/***********	get_field computes the scattered field	***********/
/***********	at a specified point, using a specified	***********/
/***********	wave_number and using a specified current	*******/
/***********	vector - maybe the exact one, or one of		*******/
/***********	several approximates..						*******/
/******************************************************************/

CComplexVector  get_field( CPoint3d field_point, double the_wave_number) {
	CComplexVector E = CComplexVector( 0.0 , 0.0 , 0.0 ) ; 
	int j ; 
	double lj, A_plus_j, A_minus_j  ; 
	CPoint3d u, rj_plus_1 , rj_plus_2, rj_plus_3, cen_plus_j  ; 
	CPoint3d rj_minus_1 , rj_minus_2, rj_minus_3, cen_minus_j ; 
	
	
	for( j = 0 ; j <= last_edge_number ; j++) { 
		lj= edges[j].length() ; 
		u = cross (edges[j].p2()  - edges[j].free1() , edges[j].p1() - edges[j].free1() );
		A_plus_j = sqrt (  (u*u)) / 2.0;
		rj_plus_1 = edges[j].free1() ; 
		rj_plus_2 = edges[j].p2() ; 
		rj_plus_3 = edges[j].p1() ; 
		cen_plus_j = (rj_plus_1 + rj_plus_2 + rj_plus_3)/3.0 ; 
		// cen_plus_i is the centroid of the integration (j) plus triangle. 
		
		
		
		E +=   A_scatter (rj_plus_1, rj_plus_2, rj_plus_3, field_point, lj , the_wave_number) * J[j] ; 
		E +=   phi_scatter( rj_plus_1 , rj_plus_2, rj_plus_3, field_point, lj, the_wave_number ) * J[j] ; 
		
		
		
		u = cross (edges[j].p2()  - edges[j].free2() , edges[j].p1() - edges[j].free2() );
		A_minus_j = sqrt (  (u*u)) / 2.0;
		rj_minus_1 = edges[j].free2() ; 
		rj_minus_2 = edges[j].p2() ; 
		rj_minus_3 = edges[j].p1() ; 
		cen_minus_j = (rj_minus_1 + rj_minus_2 + rj_minus_3)/3.0 ; 
		// cen_minus_i is the centroid of the integration (j) plus triangle. 
		
		
		E -=   A_scatter (rj_minus_1, rj_minus_2, rj_minus_3, field_point, lj, the_wave_number) * J[j] ; 
		E -=   phi_scatter (rj_minus_1, rj_minus_2, rj_minus_3, field_point, lj, the_wave_number) * J[j] ; 
		
		
	} 
	
	return   E ; 
	
}

void compute_fields_along_lines(){
	
	CPoint3d		the_step, field_point ; 
	int				ct1, ct2, NO_OF_STEPS ; 
	double			slice_length ;
	CComplexVector	e_sca, e_inc, e_tot ; 
	ofstream		field1, field2  ;
	ofstream		inc_field1, inc_field2  ;
	CPoint3d		temp_vec ;
	
	field1.open("../../../../../../../../MOM 3D Flat Plate/output_data/field_values1.res") ;
	field2.open("../../../../../../../../MOM 3D Flat Plate/output_data/field_values2.res") ;
	inc_field1.open("../../../../../../../../MOM 3D Flat Plate/output_data/inc_field_values1.res") ;
	inc_field2.open("../../../../../../../../MOM 3D Flat Plate/output_data/inc_field_values2.res") ;
	
	field_slice_start[0]	=	CPoint3d(field_slice_start_x0, field_slice_start_y0, field_slice_start_z0) ;
	field_slice_finish[0]	=	CPoint3d(field_slice_finish_x0, current_slice_finish_y0, field_slice_finish_z0) ;	
	field_slice_start[1]	=	CPoint3d(field_slice_start_x1, current_slice_start_y1, field_slice_start_z1) ;
	field_slice_finish[1]	=	CPoint3d(field_slice_finish_x1, current_slice_finish_y1,field_slice_finish_z1 ) ;	
	
	for(ct1 = 0 ; ct1 < 2 ; ct1++) {
		
		slice_length = (field_slice_finish[ct1] - field_slice_start[ct1]).abs() ; 
		NO_OF_STEPS  =	ceil(slice_length/disc_length) ;
		the_step  = (field_slice_finish[ct1] - field_slice_start[ct1])/(double)NO_OF_STEPS ; 
		
		for(ct2 = 0 ; ct2 < NO_OF_STEPS ; ct2++) { 
			field_point = field_slice_start[ct1] + the_step*(ct2+0.5);	
			e_sca	= get_field(field_point,wave_number) ; 
			e_inc	= inc_field(k_v, field_point, E0, dipole, orient, za, wave_number); 
			e_tot	= e_inc + e_sca ; 
			
	if(ct1 == 0) 
		field1 << the_step.abs()*(ct2+0.5) << " " << e_tot.xcoord() << " " <<  e_tot.ycoord() << "  " << e_tot.zcoord() << endl ; 
	if(ct1 == 1) 
		field2 << the_step.abs()*(ct2+0.5) << " " << e_tot.xcoord() << " " <<  e_tot.ycoord() << "  " << e_tot.zcoord() << endl ; 
	
			if(ct1 == 0) 
				inc_field1 << the_step.abs()*(ct2+0.5) << " " << e_inc.xcoord() << " " <<  e_inc.ycoord() << "  " << e_inc.zcoord() << endl ; 
			
			if(ct1 == 1) 
				inc_field2 << the_step.abs()*(ct2+0.5) << " " << e_inc.xcoord() << " " <<  e_inc.ycoord() << "  " << e_inc.zcoord() << endl ; 
			
		}
		
	}
	
	field1.close() ; 
	field2.close() ; 
	
	inc_field1.close() ; 
	inc_field2.close() ; 
	
}

void compute_fields_along_grid()  {
	CPoint3d		the_step[2], field_point, contour_start_point ; 
	int				ct1, ct2, NO_OF_STEPS ; 
	CComplexVector	e_sca, e_inc, e_tot ; 
	ofstream		field  ;
	CPoint3d		temp_vec ;
	
	contour_start_point = CPoint3d(field_contour_start_x,field_contour_start_y,field_contour_start_z) ; 
	
	field.open("../../../../../../../../MOM 3D Flat Plate/output_data/contour_field_values.res") ;
	NO_OF_STEPS  =	ceil(field_grid_distance/contour_field_disc_length) ;
	
	the_step[0]  = (direction1*field_grid_distance)/(double)NO_OF_STEPS ; 
	the_step[1]  = (direction2*field_grid_distance)/(double)NO_OF_STEPS ; 
	
	field << omega << " " << 0.0 << " " << 0.0 << " " << 0.0 << " " << 0.0 << " " << 0.0 << endl ; 
	field << NO_OF_STEPS  << " " << 0.0 <<  " " << 0.0 << " " << 0.0 << " " << 0.0 << " " << 0.0 << endl ; 
	
	for(ct1 = 0 ; ct1 < NO_OF_STEPS ; ct1++) { 
		
		if(ct1%10 ==0) 
			cout <<  "Processing contour field - ct1 equals " << ct1 << " of " << NO_OF_STEPS << endl ; 
		
		for(ct2 = 0 ; ct2 < NO_OF_STEPS ; ct2++) { 
			field_point = contour_start_point + the_step[0]*(ct1+0.5) + the_step[1]*(ct2+0.5) ; 
			e_sca	= get_field(field_point,wave_number) ; 
			e_inc	= inc_field(k_v, field_point, E0, dipole, orient, za, wave_number); 
			e_tot	= e_inc  + e_sca ; 
			
			field << e_tot.xcoord() << " " << e_tot.ycoord() <<  " " << e_tot.zcoord()  << endl ; 
		}
	}
	
	field.close(); 
}


double  get_RCS( CPoint3d field_point, double the_wave_number) {
	
	CComplexVector E = CComplexVector( 0.0 , 0.0 , 0.0 ) ; 
	int j ; 
	double lj, A_plus_j, A_minus_j  ; 
	CPoint3d u, rj_plus_1 , rj_plus_2, rj_plus_3, cen_plus_j  ; 
	CPoint3d rj_minus_1 , rj_minus_2, rj_minus_3, cen_minus_j ; 
	
	
	for( j = 0 ; j <= last_edge_number ; j++) { 
		lj= edges[j].length() ; 
		u = cross (edges[j].p2()  - edges[j].free1() , edges[j].p1() - edges[j].free1() );
		A_plus_j = sqrt (  (u*u)) / 2.0;
		rj_plus_1 = edges[j].free1() ; 
		rj_plus_2 = edges[j].p2() ; 
		rj_plus_3 = edges[j].p1() ; 
		cen_plus_j = (rj_plus_1 + rj_plus_2 + rj_plus_3)/3.0 ; 
	
		
		E +=   RCS_scatter (rj_plus_1, rj_plus_2, rj_plus_3, field_point, lj , the_wave_number) * J[j] ; 
		
		u = cross (edges[j].p2()  - edges[j].free2() , edges[j].p1() - edges[j].free2() );
		A_minus_j = sqrt (  (u*u)) / 2.0;
		rj_minus_1 = edges[j].free2() ; 
		rj_minus_2 = edges[j].p2() ; 
		rj_minus_3 = edges[j].p1() ; 
		cen_minus_j = (rj_minus_1 + rj_minus_2 + rj_minus_3)/3.0 ; 
		// cen_minus_i is the centroid of the integration (j) plus triangle. 
		
		
		E -=   RCS_scatter (rj_minus_1, rj_minus_2, rj_minus_3, field_point, lj, the_wave_number) * J[j] ; 
		
		
	} 
	

	return   10.0*log10(4.0*pi*pow(E.euclideanNorm(),2)) ; 
	
}

// Compute far_field_patterns computes far_fields along two distinct arcs. You can vary theta or phi. 
void compute_far_field_patterns() {
	double		angle ;
	int			ct1 ; 
	CPoint3d	RCS_direction ; 
	double		RCS ;
	ofstream	the_RCS1, the_RCS2 ; 


	the_RCS1.open("../../../../../../../../MOM 3D Flat Plate/output_data/phi_RCS.res") ;
	the_RCS2.open("../../../../../../../../MOM 3D Flat Plate/output_data/theta_RCS.res") ;
	
	for(ct1 = 0 ; ct1 < 2 ; ct1++) {

		angle = 0.0 ; 
		while( angle < 2.0*pi ) {
			
		if( ct1 == 0 ) // Varying phi
		{
			RCS_direction = CPoint3d(sin(THETA_FOR_PHI_SLICE)*sin(angle),sin(THETA_FOR_PHI_SLICE)*cos(angle),cos(THETA_FOR_PHI_SLICE)) ; 
			}
		if( ct1 == 1 ) // Varying theta 
		{
			RCS_direction = CPoint3d(sin(angle)*sin(PHI_FOR_THETA_SLICE),sin(angle)*cos(PHI_FOR_THETA_SLICE),cos(angle)) ; 
		}
		
			RCS = get_RCS(RCS_direction,wave_number) ; 
			
			if(ct1 == 0 ) 
			the_RCS1 << angle << " " << RCS  << endl ; 
			if(ct1 == 1 ) 
				the_RCS2 << angle << " " << RCS  << endl ; 
			
	
			angle += RCS_angle_step_in_radians ;
			
		}
		
		
		
	}
	
	the_RCS1.close() ;
	the_RCS2.close() ;
	
	
}



