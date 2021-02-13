#include <iostream>
#include <string>
#include <cstdlib>

#include "Game.h"
#include "View.h"
#include "Controller.h"

using namespace std;


int main (int argc, char* argv[]) {

	Game myGame; 
	View myView;
	Controller myController;
	int gameResult;

	//Clears the screen
	system("clear");

	if (argc > 1) { //if the user actually supplied arguments

		for (int i = 1; i < argc; i++) { //goes through all the arguments

			if (string(argv[i]) == "-testing") {

				myGame.SetTestingMode(true);

			}
			else if (string(argv[i]) == "-init") {

				if (((i + 1) < argc)) {

					myGame.SetinitFileName(string(argv[i + 1]));
					i++;
				}
				else {

					cout << "you failed to provide a file for the -init argument" << endl;
				}
			}
			else if (string(argv[i]) == "-deck1") {

				if (((i + 1) < argc)) {

					myGame.SetDeck1FileName(string(argv[i + 1]));
					i++;

				}
				else {

					cout << "you failed to provide a file for the -deck1 argument" << endl;
				}
			}
			else if (string(argv[i]) == "-deck2") {

				if (((i + 1) < argc)) {

					myGame.SetDeck2FileName(string(argv[i + 1]));
					i++;
				}
				else {

					cout << "you failed to provide a file for the -deck2 argument" << endl;
				}
			}
		}
	}

	
	myGame.Start();

 
	while (true) {

		myController.Draw(myGame, myView);

		if ( (gameResult = myGame.Update()) != 0) {
			break;
		}

		//myController.Draw(myGame, myView); //this is a pass by constant refrence, dont worry
	}

	system("clear");

	if (gameResult == 2) {

		cout << "CONGRATS PLAYER 1 " << myGame.GetPlayer1Name() << " YOU WON!!!" << endl;; 
	}
	else if (gameResult == 1) {

		cout << "CONGRATS PLAYER 2 " << myGame.GetPlayer2Name() << " YOU WON!!!" << endl;
	}

	return 0;


}

