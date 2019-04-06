/*
  title.h:  Header file for the title.cpp
  contains class definition
  Programmer: Pierre Abraham Mulamba
  @KAUST, Sat May 7, 2011, 01:05
  Last updated;

*/

#ifndef TITLE_H
#define TITLE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <cctype>

class Title{
 public:
  Title(std::string arg1, std::string arg2);// constructor
  
  ~Title(); // destructor
 private:
  std::string prog;
  std::string release;
};

class End{
 public:
  End(std::string prog);// constructor
  
  ~End();		//destructor
};

#endif
