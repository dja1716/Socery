#include <iostream>
#include <string>
#include <sstream>

#include "operator.h"

using namespace std;

int numArgs = -1; 
string restOfInput = ""; 

bool fromFile = false;
string fileLine = ""; 
string inputFeed = "";

int argument1 = 1000;
int argument2 = 1000;
int argument3 = 1000;


//Getters for the arguments the user may put in for commands like play, use, inspect
int Operator::GetArgument1 () { 
	return argument1; 
}

int Operator::GetArgument2 () { 
	return argument2; 
} 

int Operator::GetArgument3 () { 
	return argument3; 
}

int Operator::GetNumOfArguments () {

	return numArgs;
}


//Will have following commands:
// help , end, quit, draw, discard, attack, play , use , inspect , hand, board, 

int Operator::Convert (string input, int argNum) {

	int output;
	stringstream convert(input);

	//Checks if it is the one exception of play
	if ( (inputFeed == "play" || inputFeed == "use") && argNum == 3) {

		if (input == "r") {
			return -69;
		}
	}

	if (convert>>output) {

		if (output >= 0) {

			return output;
		}
		else {

			cout << "PLEASE SUPPLY A NON-NEGATIVE INTEGER VALUE!! " << endl;
			return -11;
		}

	}  
	else { //unsuccesfull convert

		cout << "THE ARGUMENT SUPPLIED IS NOT A VALID INTEGER VALUE!! " << endl; 
		return -4; 
	}
}

int Operator::NumArguments (string input) {

	bool isFirst = true;
	bool insideArgument = false; 
	int numOfArgs = 0;

	for (int i = 0; i < input.length(); i++) {

		if (isFirst) {

			if (input[i] != ' ') {

				isFirst = false;	
				numOfArgs = 1;
				insideArgument = true;
			}
		}
		else {

			if (input[i] == ' ') {

				if (insideArgument) {

					insideArgument = false;
				}

			} else {

				if (!insideArgument) {

					insideArgument = true;
					numOfArgs++;
				}
			}
		}
	}

	return numOfArgs;
}

string Operator::GetArgument (int index, string input) {

	int curArg = 0;
	bool isFirst = true;
	bool insideArgument = false;
	string argument = "";

	//sanity check that you are checking for an argument that actually exists
	if ( (index > numArgs) || (index < 0)) {

		return argument;
	}  


	for (int i = 0; i < input.length(); i++) {

		if (isFirst) {

			if (input[i] != ' ') {

				isFirst = false;
				insideArgument = true;
				curArg = 1;

				if (index == curArg) {

					argument += input[i];
				}
			}
		}
		else {

			if (input[i] == ' ') {

				if (insideArgument) {

					insideArgument = false;
				}

			}
			else {

				if (insideArgument) {

					if (curArg == index) {

						argument += input[i];
					}
				}
				else {

					insideArgument = true;
					curArg++;

					if (curArg == index) {

						argument += input[i];
					}
				}
			}
		}
	}


	return argument;
}



int Operator::ArgumentExtrator (int acceptableNum1, int acceptableNum2) {

	if (fromFile || (getline(cin, restOfInput))  ) { //this gets the remainder of the line

		if (fromFile) {

			for (int i = 2; i <= numArgs; i++) {

				restOfInput += GetArgument(i,fileLine);
				restOfInput += " ";
			}
		}


		//delete later
		//cout << restOfInput << endl;

		if (restOfInput == "") { //if the user entered nothing after a required command

			if (acceptableNum1 == 0 || acceptableNum2 == 0) { //if zero arguments is acceptable

				return 0;
			}
			else {
				
				cout << "INVALID INPUT! YOU MUST INCLUDE AN ARGUMENT WITH THIS COMMAND!! " << endl;
				return -1; 
			}
		}
		else {

			numArgs = NumArguments(restOfInput);
			
			//delete later
			//cout << "num of arguments: ";
			//cout << numArgs << endl;


			if (numArgs == acceptableNum1 || numArgs == acceptableNum2) { //if user provides valid # of args

				if (numArgs >= 1) {
					argument1 =  Convert(GetArgument(1,restOfInput), 1);
					//cout << argument1 << endl;
				}

				if (numArgs >= 2) {
					argument2 = Convert(GetArgument(2,restOfInput), 2);
					//cout << argument2 << endl;
				}

				if (numArgs >= 3) {

					argument3 = Convert(GetArgument(3,restOfInput), 3);
					//cout << argument3 << endl;
				}

				if (argument1 <= 0 || argument2 <= 0 || (argument3 <= 0 && argument3 != -69) ) {

					cout << "PLEASE SUPPLY ONLY POSITIVE NUMBERS" << endl;
					return -1; 
				}
			}
			else {

				cout << "Invalid number of arguments supplied!! " << endl;
				return -1; 
			}
		}
	}
	else { //if somehow this failed

		cout << "an unexpected error occured";
		return -1;
	}

	return 0;

}





int Operator::GameLoopInput (bool testingMode, string command) {

	int userDecision = -2;
	fromFile = false;
	inputFeed = "";
	fileLine = "";
	restOfInput = "";

	while (true) {

		argument1 = 1000;
		argument2 = 1000;
		argument3 = 1000;

		if (command == "") { //if accepting input from stdin

			if (cin >> inputFeed) {

			} 
			else {

			}
		}
		else { //if accepting input from a file
			
			fromFile = true;
			fileLine = command;

			numArgs = NumArguments(fileLine);

			if (numArgs >= 1) {

				inputFeed = GetArgument( 1 , fileLine); 
			}
		}


	    if (inputFeed == "help") { 
	    	
	    	userDecision = ArgumentExtrator(0,0);
	    }
	    else if (inputFeed == "end") { 

	    	if ((userDecision = ArgumentExtrator(0,0)) == 0 ) { userDecision = 1; }

	    }
	    else if (inputFeed == "quit") { 

	    	if ((userDecision = ArgumentExtrator(0,0)) == 0) { userDecision = 2; }
	    }
	    else if (inputFeed == "draw") { 

	    	if (testingMode) { //This command is only available in -testing mode.
	    		
	    		if ((userDecision = ArgumentExtrator(0,0)) == 0) { userDecision = 3; }
	    	}
	    	else {

	    		cout << "IM SORRY!!! YOU ARE NOT IN TESTING MODE, YOU CANNOT ACCESSS THIS FEATURE!" << endl; 
	    	}
	    }
	    else if (inputFeed == "discard") { 

	    	if (testingMode) { //This command is only available in -testing mode.
	    		
	    		if ((userDecision = ArgumentExtrator(1,1)) == 0) { userDecision = 4; }
	    	}
	    	else {
	    		
	    		cout << "IM SORRY!!! YOU ARE NOT IN TESTING MODE, YOU CANNOT ACCESSS THIS FEATURE!" << endl; 
	    	}
	    }
	    else if (inputFeed == "attack") {  

	    	if ((userDecision = ArgumentExtrator(1,2)) == 0) { userDecision = 5; } 

	    }
	    else if (inputFeed == "play") {  

	    	
	    	if ((userDecision = ArgumentExtrator(1,3)) == 0) { userDecision = 6; } 

	    }
	    else if (inputFeed == "use") {  

	    	
	    	if ((userDecision = ArgumentExtrator(1,3)) == 0) {userDecision = 7; };
	    }
	    else if (inputFeed == "inspect") { 
    	
	     	if ((userDecision = ArgumentExtrator(1,1)) == 0) {userDecision = 8; };
	    }
	    else if (inputFeed == "hand") {  
	      
	    	if ((userDecision = ArgumentExtrator(0,0)) == 0) { userDecision = 9; };
	    }
	    else if (inputFeed == "board") { 
	      
	    	if ((userDecision = ArgumentExtrator(0,0)) == 0) { userDecision = 10; }
	    }
	    else {

	    	cout << "COMMAND NOT RECOGNIZED!" << endl;
	    	userDecision = -1;
	    }
    	
    	if (userDecision >= 0 || fromFile) {

    		break;
    	}
	}


	return userDecision; 
}

