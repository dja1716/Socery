#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Operator {

	int numArgs = -1; 
	string restOfInput = ""; 
	string inputFeed = "";

	bool fromFile = false;
	string fileLine = ""; 

	int argument1 = 1000;
	int argument2 = 1000;
	int argument3 = 1000;

	public: 

	int GetArgument1 (); 
	int GetArgument2 (); 
	int GetArgument3 (); 

	int Convert (string input, int argNum);
	int GetNumOfArguments ();
	int NumArguments (string input);
	string GetArgument (int index, string input);

	int ArgumentExtrator (int acceptableNum1, int acceptableNum2); 


	int GameLoopInput (bool testingMode, string command);


};



#endif

