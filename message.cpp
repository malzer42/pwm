/*
	message.cpp: contains class definition
	Programmer: Pierre Abraham Mulamba
	@KAUST, Sat May 7, 2011, 01:05
	Last updated;

*/

#include "message.h"

Message::Message(string message)
{
	cout << endl;

	string trait(message.size()+1, '-');
	cout <<setw(125) << trait << endl << endl;
	
	cout << setw(125) << message  << endl << endl;
	cout <<setw(125) << trait << endl << endl;
}

Message::~Message()
{
	
}