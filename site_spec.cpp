#include "site_spec.h"


std::vector<std::vector<double>>
compute_site_spec_scoring_mat(std::vector<std::vector<int>>& v1, std::vector<int>& v2, unsigned int sz)
{
  std::string base ="acgt";
  std::cout << base << std::endl;
  std::vector<std::vector<double>> site_spec_scoring_mat;
  site_spec_scoring_mat.resize(base.size());

  for (unsigned int i = 0; i < site_spec_scoring_mat.size(); i++)
    site_spec_scoring_mat[i].resize(sz);

  
  for (unsigned int i = 0; i < base.size(); i++){
    for (unsigned int j = 0; i <= sz -1; j++){
      site_spec_scoring_mat[i][j] = double(v1[i][j]);
    }
    
  }
  std::cout <<"Before return "<< std::endl;
  return site_spec_scoring_mat;
}
