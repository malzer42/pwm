/**
   argument.cpp: Cpp file to implement the argument function
   Progammer: Pierre Abraham Mulamba
   @Laval, Friday 20190405
*/

#include "argument.h"

void argument( int arg)
{
   //section: checking the number of argument to provide at the command line
    if (arg != 3) {
      std::cout << "USAGE:\n" 
		<< " ./xpos_weight_mat input_file_name1 input_file_names2 \n" 
		<< " ./xpos_weight_mat Executable program\n " 
		<< " input_file_name1 File containing sequences to generate the position weight matrix\n"
		<< " input_file_name2 File containing sequences to scan , create sliding windows and use the position weight matrix\n" 
		<< " output_file_name File to hold the results\n"
		<< " howto: From the command line type\n"
		<< " ./xpos_weight_mat bicoidMotif.seq Donor_acceptor.fa\n\n";
      exit(0);
    }
}
