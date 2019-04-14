/**
   site_spec.h: Header file for the site_spec.cpp
   Programmer(s): Pierre Abraham Mulamba
   Date of creation (modification): 20190411 (20190411)
   Description: compute the site specific scoring matrix based on 
   the position weight matrix and the total position vector
 */

#ifndef SITE_SPEC_H
#define SITE_SPEC_H

#include <iostream>
#include <vector>
#include <string>


std::vector<std::vector<double>>
compute_site_spec_scoring_mat(std::vector<std::vector<int>>& v1, std::vector<int>& v2, unsigned int sz);


#endif /* SITE_SPEC_H */
