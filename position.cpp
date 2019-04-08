#include "position.h"

std::vector<int> compute_total_position(const std::vector<std::vector<int>>& v, unsigned int sz)
{
  std::vector<int> position[ sz ];	//(*nucleotides.begin()).size() gives the number of column in the matrix nucleotides
  std::vector<int> total_pos;
  std::string base("agct");
  
    for (unsigned int j = 0 ; j < sz ; j++) {
      for (unsigned int i = 0; i < base.size() ; i++) {
	position[j].push_back( v[i][j] );
      }
      total_pos.push_back(sumVec(position[j]));
    }
    
    return total_pos;
  }
