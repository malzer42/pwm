/**
   sum.cpp: implementation of the sum function
   Programmer: Pierre Abraham Mulamba
   @KAUST, Sat May 7, 2011, 01:05
   Last updated;
*/

#include "sum.h"

int sumVec(const std::vector<int>& v)
{
  int total(0);
  for(unsigned int i = 0 ; i < v.size(); i++ ) total += v[i];
  return total;
}

