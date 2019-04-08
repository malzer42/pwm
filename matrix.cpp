/**
   matrix.cpp: Cpp file to implement the creation of a nucleotides matrix
   Programmer(s): Pierre Abraham Mulamba
   Date of creation (modification): 20190407 (20190407)
   Description: 
   1. Read a line from the input file. Each line read is saved as a row of the nucleotides matrix one character at a time
   2. Convert the nucleotides matrix characters to lower case after creation of the matrix
 */

#include "matrix.h"

std::vector<std::string> create_nucleotides_matrix(std::ifstream& fin)
{
  std::vector<std::string> tmp_nucleotides_matrix;
  std::string sequence;
  while(std::getline(fin, sequence)){
      tmp_nucleotides_matrix.push_back(sequence);
    }

    //	section: converting all the characters of the  nucleotides matrix to lower case is created.
    for( std::vector<std::string >::iterator i = tmp_nucleotides_matrix.begin() ; i != tmp_nucleotides_matrix.end() ; i++){
      for( unsigned int j = 0 ; j < (*i).size() ; j++){
	(*i).at(j) = tolower( (*i).at(j) );
      }
    }

    return tmp_nucleotides_matrix;
}
