/**
   split.h: Header file for the implementation of the split function
   Progammer(s): Pierre Abraham Mulamba
   Date of creation (modification): 20190410 (20190410)
   Description: split a file name into the name and the extension
 */

#ifndef SPLIT_H
#define SPLIT_H

#include <tuple>
#include <string>
#include <iostream>


std::tuple<std::string, std::string> split(const std::string& s);


#endif /* _SPLIT_H_ */
