#the compiler: 
CC = g++ 
#compiler flags 
CFLAGS = -Wall 
TARGET = output
SRCS = mom_code.cpp set_up_and_discretise_plate.cpp global_definitions.cpp point3d.cpp square.cpp basis3d.cpp ComplexVector.cpp complex.cpp complex_functions.cpp set_up_matrix_problem.cpp integration_routines.cpp conjugate_gradient.cpp visualise_currents_and_fields.cpp
HEADERS = set_up_and_discretise_plate.h global_definitions.h point3d.hh square3d.hh basis3d.hh ComplexVector.hh complex.hh complex_functions.hpp set_up_matrix_problem.h integration_routines.h conjugate_gradient.h visualise_currents_and_fields.h
all: 
	$(CC) $(CFLAGS) -o $(TARGET)  $(SRCS) $(HEADERS) 
clean:
	$(RM) output 
