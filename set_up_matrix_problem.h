#include	"complex.hh"
#include	"global_definitions.h"
#include	"ComplexVector.hh"

using namespace std ;

void			initialise_incident_field_information() ; 	
void			create_V_vector()  ;
complex			make_V_element(int i);
complex			inc_contr (CPoint3d k_v, CPoint3d E0, CPoint3d ro1, CPoint3d ro2, CPoint3d ro3, int opt, int dipole, int orient, double za, double obs_triangle ,double the_wave_number) ;
CComplexVector	inc_field (CPoint3d k , CPoint3d r , CPoint3d E0, int dipole , int orient, double za ,double the_wave_number) ;

void			make_Z_matrix( ) ;
complex			make_Z_element( int m , int n, double the_wave_number , int the_derivative ) ;

