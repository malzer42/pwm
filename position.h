/**
   position.h: Header file for the implementation of the position program
   Progammer(s): Pierre Abraham Mulamba
   Date of creation (modification): 20190407 (20190407)
   Description:  computing total number of observations -- the sum of all nucleotides occurences in a column or position
   this sum is used in the transformation of the position frequency matrix to position weight matrix
 */


#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <vector>
#include <string>
#include "sum.h"


std::vector<int> compute_total_position(const std::vector<std::vector<int>>& v, unsigned int sz);

#endif /* POSITION_H */
