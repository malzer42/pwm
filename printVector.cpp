/*
	printVector.cpp: Implementation of the print_vector() prototype
	Programmer: Pierre Abraham Mulamba
	@KAUST, Sat May 7, 2011, 01:05
	Last updated;

*/

#include "printVector.h"

void print(int i )
{
    cout  << i << endl;
}

void print_vector(const vector< int >& v)
{
    for_each(v.begin() , v.end() , print );
    
    //for(int i = 0 ; i < v.size() ; i++ )
      //  cout << setw(w) << v[i] << endl;
}