/*
 *  File:		set_up_and_discretise_plate.cpp
 *  Project:	3D EFIE MOM
 *
 *  Created by Conor Brennan on 19/07/2011.
 *  Copyright 2011 Dublin City University. All rights reserved.
 *
 */

#include "set_up_and_discretise_plate.h"
#include "global_definitions.h"
#include "point3d.hh"
#include "basis3d.hh"
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std ;

void set_up_plate_parameters() { 

	SOUTH_WESTx =  -side_length/2.0  ; 
	SOUTH_WESTy =  -side_length/2.0   ; 
	SOUTH_WESTz =  0.0   ; 

	NORTH_WESTx  = SOUTH_WESTx ;   
	NORTH_WESTy  = SOUTH_WESTy + side_length ; 
	NORTH_WESTz  = 0.0   ; 

	NORTH_EASTx  =  SOUTH_WESTx + side_length ; 
	NORTH_EASTy  = SOUTH_WESTy + side_length ; 
	NORTH_EASTz  = 0.0 ; 

	SOUTH_EASTx  = SOUTH_WESTx  + side_length  ; 
	SOUTH_EASTy  = SOUTH_WESTy  ; 
	SOUTH_EASTz = 0.0 ; 
}




void initialise_the_square() {
	int			ct1 ; 
	ofstream	the_plate_corners  ; 
	
	the_plate_corners.open("../../../output data/corners.res") ; 
	
	plate_corners[0] = CPoint3d( SOUTH_WESTx , SOUTH_WESTy, SOUTH_WESTz ) ; 
	plate_corners[1] = CPoint3d( SOUTH_EASTx , SOUTH_EASTy, SOUTH_EASTz ) ; 
	plate_corners[2] = CPoint3d( NORTH_EASTx , NORTH_EASTy, NORTH_EASTz ) ; 
	plate_corners[3] = CPoint3d( NORTH_WESTx , NORTH_WESTy, NORTH_WESTz ) ; 

	for(ct1 = 0 ; ct1 < 4 ; ct1++) { 
	bounding_box[ct1] =	plate_corners[ct1] ;
	}
	
	the_plate_corners << plate_corners[0].xcoord()  << " " << plate_corners[0].ycoord() << endl ; 
	the_plate_corners << plate_corners[1].xcoord()  << " " << plate_corners[1].ycoord() << endl ; 
	the_plate_corners << plate_corners[2].xcoord()  << " " << plate_corners[2].ycoord() << endl ; 
	the_plate_corners << plate_corners[3].xcoord()  << " "<<  plate_corners[3].ycoord() << endl ; 
	
	the_plate_corners.close() ; 
	
	plate_centre[0] = ( plate_corners[0] + plate_corners[1] + 	plate_corners[2] + plate_corners[3] ) *0.25  ; 
	
}


void make_a_fine_grid_of_squares() { 
	int			ct1 , ct2 ; 
	CPoint3d	step1 , step2 ; 
	
	cout << "Discretising plate - Using " << NO_OF_DISCS_PER_SIDE << " discretisations per side " << endl; 
	
	fine_grid	= new CSquare3d[TOTAL_NO_OF_SQUARES] ; 
	
	step1 = (plate_corners[1]  -  plate_corners[0]) / (double) NO_OF_DISCS_PER_SIDE ; 
	step2 = (plate_corners[3]  -  plate_corners[0]) / (double) NO_OF_DISCS_PER_SIDE ; 
		
	
	for( ct1 = 0 ; ct1 < NO_OF_DISCS_PER_SIDE ; ct1++) { 
		for( ct2 = 0 ; ct2 < NO_OF_DISCS_PER_SIDE ; ct2++) { 
			
			fine_grid[ct1*NO_OF_DISCS_PER_SIDE + ct2] = CSquare3d(plate_corners[0] + step1*ct2 + step2*ct1,  
																plate_corners[0] + step1*(ct2+1) + step2*ct1,  
																plate_corners[0] + step1*(ct2+1) + step2*(ct1+1),  
																plate_corners[0] + step1*ct2 + step2*(ct1+1) ) ; 
			}
	}
	
	
	
}

void make_the_basis_fns() {
	
	int				ct1, edge_counter ; 
	int				horizontal , vertical, diagonal  ; 
	CPoint3d		step1, step2, step3, points[4]  ;
	double			max_length = 0.0 ; 
	ofstream		the_edges ; 
	CPoint3d		u ; 
	
	edges						= new	CBasis3d[TOTAL_NO_OF_SQUARES*3] ; 
	edges_plus_triangle_area	= new	double[TOTAL_NO_OF_SQUARES*3] ; 
	edges_minus_triangle_area	= new	double[TOTAL_NO_OF_SQUARES*3] ; 
	edges_plus_centroid			= new	CPoint3d[TOTAL_NO_OF_SQUARES*3] ; 
	edges_minus_centroid		= new	CPoint3d[TOTAL_NO_OF_SQUARES*3] ; 
	
	
	the_edges.open("../../../output data/edges.res")  ; 
	
	edge_counter = 0 ; 
	
	
	for( ct1 = 0 ; ct1 < TOTAL_NO_OF_SQUARES ; ct1++) { 
		
		
		//cout << " fine grid equals " << fine_grid[ct1] << endl ; 
		
		step1 = (plate_corners[1] - plate_corners[0]) / (double) NO_OF_DISCS_PER_SIDE; 
		step2 = (plate_corners[3] - plate_corners[0]) / (double) NO_OF_DISCS_PER_SIDE; 
		
			// Assume that all basis function types are present in the square. 	
			horizontal = 1  ; 
			vertical = 1  ; 
			diagonal = 1  ; 
			
			// Now check to see whether the square is on a boundary of the plate. 
			if( (fine_grid[ct1].p1()).ycoord() == plate_corners[0].ycoord() )  
				horizontal = 0 ; 
		
			if( (fine_grid[ct1].p1()).xcoord() == plate_corners[0].xcoord() ) 
				vertical = 0 ; 
		
		
			// Process the horizontal edge first
			if( horizontal == 1 ) {
				
				points[0] = fine_grid[ct1].p1() ; 
				points[1] = fine_grid[ct1].p1() + step1 ; 
				points[2] = fine_grid[ct1].p1() + step2 ; 
				points[3] = fine_grid[ct1].p1() + step1 - step2 ; 
				
				edges[edge_counter] = CBasis3d( points[0],points[1],points[2],points[3] ) ; 
				
				u = cross (edges[edge_counter].p2()  - edges[edge_counter].free2() , edges[edge_counter].p1() - edges[edge_counter].free2() );
				edges_minus_triangle_area[edge_counter] = u.abs() / 2.0;
				edges_minus_centroid[edge_counter] = (edges[edge_counter].free2() + edges[edge_counter].p2() + edges[edge_counter].p1()) ; 
				
				u = cross (edges[edge_counter].p2()  - edges[edge_counter].free1() , edges[edge_counter].p1() - edges[edge_counter].free1() );
				edges_plus_triangle_area[edge_counter] = u.abs() / 2.0;
				edges_plus_centroid[edge_counter] = (edges[edge_counter].free1() + edges[edge_counter].p2() + edges[edge_counter].p1()) ; 
				
				
				
				fine_grid[ct1].setBasisOne(edge_counter) ; 
				fine_grid[ct1].activateBasisOne() ; 
				
				if( edges[edge_counter].length() > max_length ) 
					max_length = edges[edge_counter].length() ; 
				
				edge_counter++ ;
			}  
			
			// Now process the diagonal edge - this will always be an interior edge 
			if( diagonal == 1) { 
				
				points[0] = fine_grid[ct1].p1() + step2; 
				points[1] = fine_grid[ct1].p1() + step1 ; 
				points[2] = fine_grid[ct1].p1() + step1  + step2 ; 
				points[3] = fine_grid[ct1].p1() ; 
				
				
				edges[edge_counter] = CBasis3d( points[0], points[1], points[2], points[3] ) ; 
				
				u = cross (edges[edge_counter].p2()  - edges[edge_counter].free2() , edges[edge_counter].p1() - edges[edge_counter].free2() );
				edges_minus_triangle_area[edge_counter] = u.abs() / 2.0;
				edges_minus_centroid[edge_counter] = (edges[edge_counter].free2() + edges[edge_counter].p2() + edges[edge_counter].p1()) ; 
				
				u = cross (edges[edge_counter].p2()  - edges[edge_counter].free1() , edges[edge_counter].p1() - edges[edge_counter].free1() );
				edges_plus_triangle_area[edge_counter] = u.abs() / 2.0;
				edges_plus_centroid[edge_counter] = (edges[edge_counter].free1() + edges[edge_counter].p2() + edges[edge_counter].p1()) ; 
				
				
				fine_grid[ct1].setBasisTwo(edge_counter) ; 
				fine_grid[ct1].activateBasisTwo() ; 
				
				if( edges[edge_counter].length() > max_length ) 
					max_length = edges[edge_counter].length() ;
				
				edge_counter++ ; 
			} 
			
			// finally - process the vertical edge. 
		
			if(vertical == 1 ) { 
				
				points[0] = fine_grid[ct1].p1() ; 
				points[1] = fine_grid[ct1].p1() + step2 ; 
				points[2] = fine_grid[ct1].p1() + step1  ; 
				points[3] = fine_grid[ct1].p1() + step2 - step1; 
				
				edges[edge_counter] = CBasis3d( points[0], points[1], points[2], points[3]) ; 
				u = cross (edges[edge_counter].p2()  - edges[edge_counter].free2() , edges[edge_counter].p1() - edges[edge_counter].free2() );
				edges_minus_triangle_area[edge_counter] = u.abs() / 2.0;
				edges_minus_centroid[edge_counter] = (edges[edge_counter].free2() + edges[edge_counter].p2() + edges[edge_counter].p1()) ; 
				
				u = cross (edges[edge_counter].p2()  - edges[edge_counter].free1() , edges[edge_counter].p1() - edges[edge_counter].free1() );
				edges_plus_triangle_area[edge_counter] = u.abs() / 2.0;
				edges_plus_centroid[edge_counter] = (edges[edge_counter].free1() + edges[edge_counter].p2() + edges[edge_counter].p1()) ; 
				
				
				fine_grid[ct1].setBasisThree(edge_counter) ; 
				fine_grid[ct1].activateBasisThree() ; 
				
				if( edges[edge_counter].length() > max_length ) 
					max_length = edges[edge_counter].length() ;
				
				
			edge_counter++ ; }  
			
			
		}
		
	
	//fclose(the_edges) ; 
	last_edge_number = edge_counter - 1 ; 
	
	for(ct1 = 0 ; ct1 <= last_edge_number ; ct1++){
		the_edges << edges[ct1].p1().xcoord() << " " << edges[ct1].p1().ycoord() << endl   ; 
		the_edges << edges[ct1].p2().xcoord() << " " << edges[ct1].p2().ycoord() << endl    ; 
	}
	
	the_edges.close() ; 
	
	cout << " The largest edge is " << max_length/lambda  << " wavelengths in length " << endl ; 
	
}

 



