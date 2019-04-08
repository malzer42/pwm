/**
   pwm.cpp: Cpp file for the position weight matrix creation
   Programmer(s): Pierre Abraham Mulamba
   Date of creation (modification): 20190407 (20190407)
   Description: create and return a position weight matrix based on the nucleotides matrix
 */

#include "pwm.h"

 std::vector<std::vector<int>> create_pwm(std::vector<std::string>& v)
{
  std::string base("acgt");
  std::vector<std::vector<int>> tmp_pwm;
  tmp_pwm.resize(base.length());
  for(unsigned int i = 0; i < tmp_pwm.size(); i++){
    tmp_pwm[i].resize((*v.begin()).length());
    for(unsigned int j = 0; j < tmp_pwm[i].size(); j++){
      tmp_pwm[i][j] = 0;
    }
  }

  for(std::vector<std::string>::const_iterator i = v.begin() ; i != v.end() ; i++){
    for(unsigned int col = 0 ; col < (*i).length() ; col++){
      for(unsigned int k = 0 ; k < base.size(); k++){
	if( (*i)[col] == base[k]){
	  tmp_pwm[k][col]++;
	}
	else{
	  ;
	}
      }
    }
  }

  return {tmp_pwm};
}

  
