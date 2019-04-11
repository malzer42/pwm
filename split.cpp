#include "split.h"

std::tuple<std::string, std::string> split(const std::string& s)
{
  size_t i = s.rfind('.' , s.length());
  if(i != std::string::npos){
    return {s.substr(0, i), s.substr(i+1, s.length()-1)};
  }
  return {"", ""};
}
