/*
	message.h: Header file for the message.cpp contains class definition
	Programmer: Pierre Abraham Mulamba
	@KAUST, Sat May 7, 2011, 01:05
	Last updated;

*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

typedef string::iterator SI;


class Message{
	public:
		Message(string message);			// constructor

		~Message();							//destructor
};

#endif
