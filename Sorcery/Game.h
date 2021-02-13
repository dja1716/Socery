#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <vector>
#include <cstdlib>

#include "operator.h"
#include "Player.h"

// Implement players (only having names for now), the game loop, and the -init command line argument.
// Make each command simply echo itself for now, so that you can verify that all of these work correctly.

//Class Player;
//Class Board;

class Game {

	Operator myOperator;

	bool testingMode = false;
	string deck1FileName = "";
	string deck2FileName = "";

	ifstream infile;

	string initFileName;
	string curLine;
	bool stillReadingFromInit = false;

	bool recentSwitch = false;
	bool endOfTurn = false;
	bool startOfTurn = true;
	int playerIndex = 0;
	int inactiveIndex = 1;


	//help , end, quit, draw, discard, attack, play , use , inspect , hand, board, 
	int lastDecision;

	enum InputStates
	{
	  HELP = 0,
	  END = 1,
	  QUIT = 2,
	  DRAW = 3,
	  DISCARD = 4,
	  ATTACK = 5,
	  PLAY = 6,
	  USE = 7,
	  INSPECT = 8,
	  HAND = 9,
	  BOARD = 10
	};  



  int GetUserInput(); 
  void ProcessInput ();

  void StartOfTurn ();
  void EndOfTurn ();
  void MinionTrigger () ;
  


public:

	int mode = 1;
	int inspectElement = 0;
	bool player1Turn = true;
	vector <Player> players;

	string GetPlayer1Name () const;
	string GetPlayer2Name () const;

	void SetTestingMode (bool mode);
	void SetDeck1FileName (string name);
	void SetDeck2FileName (string name);
	void SetinitFileName (string name);

  	void Start();
  	void ProcessTurn (); 

  	int Update();

};

#endif


