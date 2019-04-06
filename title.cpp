/**
   title.cpp:	contains classes implementation
   Programmer: Pierre Abraham Mulamba
   @KAUST, Sat May 7, 2011, 01:05
   Last updated;
*/

#include "title.h"

Title::Title(std::string arg1 , std::string arg2)
{
  prog = arg1.substr(2);
  release =arg2;
  std::cout << prog << "\t" << release << '\n';
}

Title::~Title()
{
	
}

End::End(std::string prog)
{
  std::cout << std::setw(95) << prog << " Ended Successfully!" <<'\n';
}

End::~End()
{
  std::cout <<'\n';
  std::cout << std::setw(100) << "BYE!" <<'\n';
}
