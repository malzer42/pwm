#include "print.h"


void print(const std::vector<std::vector<int>>& v)
{
  for (unsigned int i = 0; i < v.size(); i++){
    for(unsigned int j = 0; j < v[i].size(); j++){
      std::cout << v[i][j] << '\t';
    }
    std::cout << '\n';
  }
}
