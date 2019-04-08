/**
   matrix.h: Header file for the creation of the nucleotide matrix
   Progammer(s): Pierre Abraham Mulamba
   Date of creation (mofification): 20190406 (20190406)
   Description:
   1. Read a line from the input file. Each line read is saved as 
   a row of the nucleotides matrix one character at a time
   2. Convert the nucleotides matrix charaters to lower case after creation of the matrix
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>


std::vector<std::string> create_nucleotides_matrix(std::ifstream& fin);

#endif /* MATRIX_H */
