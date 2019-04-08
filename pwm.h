/**
   pwm.h: Header file for the position weight matrix
   Programmer(s): Pierre Abraham Mulamba
   Date of creation (modification): 20190407 (20190407)
   Description: Create a position weight matrix and return it based on the nucleotides matrix
 */
#ifndef PWM_H
#define PWM_H

#include <utility>
#include <tuple>
#include <iostream>
#include <vector>
#include <string>
#include "sum.h"

std::vector<std::vector<int>>  create_pwm(std::vector<std::string>& v);

#endif /* PWM_H */
