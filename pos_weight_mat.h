/**
   pos_weight_mat.h: Header file for the pos_weight_mat.cpp
   Programmer: Pierre Abraham Mulamba
   @KAUST, Sat May 7, 2011, 01:05
   Last updated; Mon Oct 10, 2011 , 02:42
*/
#ifndef POS_WEIGHT_MAT_H
#define POS_WEIGHT_MAT_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "title.h"
#include "message.h"
#include "sum.h"
#include "printVector.h"

typedef std::vector<int>::const_iterator VI; 
typedef std::vector< std::vector<int> > :: size_type VVST; //VVST : Vector Vector Size Type
typedef std::vector<int> :: size_type VST; // VST : Vector Size Type
typedef std::vector<std::string>::const_iterator vsi; // vsi: vector string iterator
typedef std::string::const_iterator si;// si: string iterator
typedef unsigned int UI;

const int INITIAL = 0;
const double THRESHOLD = 0.0;
const double FACTOR = 0.25;

#endif /* POS_WEIGHT_MAT_H */
