#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime> 
#include <string> 


#include	"set_up_and_discretise_plate.h"
#include	"global_definitions.h"
#include	"set_up_matrix_problem.h"
#include	"conjugate_gradient.h"
#include	"visualise_currents_and_fields.h"

using namespace std ;



int main(int argc, char * const argv[]){
    
//	Set up plate geometry and define basis functions.
/*	The following are contained in set_up_and_discretise_plate.cpp */

set_up_plate_parameters() ; 
initialise_the_square() ; 
make_a_fine_grid_of_squares() ; 
make_the_basis_fns() ; 

//	Set up V and Z for matrix equation 
/*	The following are contained in set_up_matrix_problem */
initialise_incident_field_information() ; 	
	
create_V_vector() ; 
make_Z_matrix() ;
	

//	Solve the matrix equation 
/*	The following is contained in conjugate_gradient.cpp */
cgne() ; 

	
//	Visualise the surface currents and other fields 
/*	The following are contained in visualise_currents */ 
compute_currents_along_lines() ; 
compute_incident_fields_on_grid() ; 
compute_currents_on_grid() ; 


	//Near fields
compute_fields_along_lines();

//compute_fields_along_grid()  ; 
// Far-fields
compute_far_field_patterns() ;
	
	
	
	
	
}





