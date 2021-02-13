#include <fstream>
#include <vector>
#include <cstdlib>

#include "Game.h"
#include "operator.h"
#include "Player.h"


Operator myOperator;

int mode = 2;
int inspectElement = 0;
//1 = board
//2 = hand
//3 = inspect
//4 = help


bool testingMode = false;
string deck1FileName = "";
string deck2FileName = "";

ifstream infile;

string initFileName;
string curLine;
bool stillReadingFromInit = false;

bool player1Turn = true;
bool recentSwitch = false;
bool endOfTurn = false;
bool startOfTurn = true;
int playerIndex = 0;
int inactiveIndex = 1;

int lastDecision;

vector <Player> players;

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




void Game::SetTestingMode (bool mode) {

  this->testingMode = mode;
}

void Game::SetDeck1FileName (string name) {

  this->deck1FileName = name;
}

void Game::SetDeck2FileName (string name) {

  this->deck2FileName = name;
}

void Game::SetinitFileName (string name) {

  this->initFileName = name;
  this->stillReadingFromInit = true;

  infile.open (initFileName);
}


string Game::GetPlayer1Name () const {

    return players[0].GetName();
}

string Game::GetPlayer2Name () const {

    return players[1].GetName();
}







void Game::Start() {

  string name1; 
  string name2; 
  lastDecision = -1;

  cout << "Welcome to Sorcery!!! " << endl;


  cout << "Please enter the name for player 1" << endl; 
  

  if (stillReadingFromInit) { //if it is still getting the input from the file

    //get name from first line of file
    getline(infile,name1);

  }
  else {

    getline(cin,name1);
  }


  cout << "Please enter the name for player 2" << endl; 
  
  if (stillReadingFromInit) { //if it is still getting the input from the file

    //get name from second line of file
    getline(infile,name2);

  }
  else {
     getline(cin,name2);
  }
  


  //generates the players and loads their decks
  if (deck1FileName != "") {

    Player player1; 
    players.push_back(player1) ;
    players[0].SetName(name1);
    players[0].SetLoadDeck(true);
    players[0].SetFileName(deck1FileName);
    players[0].LoadDeck();
    players[0].MarkAsPlayer1();
  }
  else {

    Player player1; 
    players.push_back(player1) ;
    players[0].SetName(name1);
    players[0].LoadDeck();
    players[0].MarkAsPlayer1();

  }

  if (deck2FileName != "") {

    Player player2; 
    players.push_back(player2) ;
    players[1].SetName(name2);
    players[1].SetLoadDeck(true);
    players[1].SetFileName(deck2FileName);
    players[1].LoadDeck();
  }
  else {

    Player player2; 
    players.push_back(player2);
    players[1].SetName(name2);
    players[1].LoadDeck();
  }

  if (testingMode) {

    players[0].SetTestingMode();
    players[1].SetTestingMode();
  }

  //makes the players draw their cards
  players[0].DrawCards(4);
  players[1].DrawCards(4);

  //Clears the screen before drawing new stuff
  system("clear");

}




int Game::GetUserInput() {

  int userInput; 
  bool readSuccess = false;

  if (stillReadingFromInit) { //if it is still getting the input from the file

    string readIn; 

    if (getline(infile,readIn)) {

      userInput = myOperator.GameLoopInput(testingMode, readIn); //temp example, the 2nd argument should be the line from the file
      readSuccess = true;
    } 
  }
  
  if (!readSuccess) { //if it is getting input from stdin

    userInput = myOperator.GameLoopInput(testingMode, "");

  }


  return userInput;
}

void Game::ProcessInput() {

  int arg1;
  int arg2;
  int arg3;

  switch (lastDecision) {

    case HELP:

      //display help menu
      mode = 4;

      break;

    case END: //switch players turn
   
      player1Turn = !player1Turn;
      endOfTurn = true;
      recentSwitch = true;

      break;

    case DRAW:  //testing only

      if (players[playerIndex].IsDeckEmpty() == false &&
            players[playerIndex].IsHandFull() == false) {

          players[playerIndex].DrawCards(1);
      }

      break;

    case DISCARD: //testing only

      arg1 = myOperator.GetArgument1();
      players[playerIndex].Discard(arg1);

      break;

    case ATTACK:

      if (myOperator.GetNumOfArguments() == 1) {

          arg1 = myOperator.GetArgument1();
          players[playerIndex].Attack(arg1, players[inactiveIndex] ) ;
      }
      else {

          arg1= myOperator.GetArgument1();
          arg2 = myOperator.GetArgument2();
          players[playerIndex].Attack(arg1, arg2, players[inactiveIndex] ) ;
      }

      break;

    case PLAY: 

      if (myOperator.GetNumOfArguments() == 1) {

        arg1 = myOperator.GetArgument1();
        players[playerIndex].Play(arg1, players[inactiveIndex] );

      }
      else {

        arg1 = myOperator.GetArgument1();
        arg2 = myOperator.GetArgument2();
        arg3 = myOperator.GetArgument3();
        players[playerIndex].Play(arg1,arg2, arg3, players[inactiveIndex]);
      }

      break;

    case USE:

      if (myOperator.GetNumOfArguments() == 1) {

        arg1 = myOperator.GetArgument1();
        players[playerIndex].Use(arg1, players[inactiveIndex] );

      }
      else {

        arg1 = myOperator.GetArgument1();
        arg2 = myOperator.GetArgument2();
        arg3 = myOperator.GetArgument3();
        players[playerIndex].Use(arg1,arg2, arg3, players[inactiveIndex]);
      }


      break;

    case INSPECT: 

      arg1 = myOperator.GetArgument1();
      inspectElement = arg1;
      mode = 3;

      break;

    case HAND:

      mode = 2;

      break;

    case BOARD:

      mode = 1;

      break;


  }
}


void Game::ProcessTurn () {

    if (player1Turn) {
      
      playerIndex = 0;
      inactiveIndex = 1;

    }
    else {

      playerIndex = 1;
      inactiveIndex = 0;

    }

    players[playerIndex].ClearError();
    players[inactiveIndex].ClearError();
}


void Game::StartOfTurn () {

  if (startOfTurn) {

    //marks all the minions as unused as of this turn
    players[playerIndex].UnUseMinions();

    //checks if its first turn
    if (players[playerIndex].IsFirstTurn()) {

      players[playerIndex].SetFirstTurn();
    }
    else {

      //increases magic
      players[playerIndex].GainMagic();

      //Draws card if nessesary
      if (players[playerIndex].IsDeckEmpty() == false &&
            players[playerIndex].IsHandFull() == false) {

            players[playerIndex].DrawCards(1);
      }
    }

    //Trigger
    players[playerIndex].StartOfTurn (true);
    players[inactiveIndex].StartOfTurn (false);

    startOfTurn = false;

  }
}

void Game::EndOfTurn() {

  //end of turn
  if (endOfTurn) {


    players[playerIndex].EndOfTurn (true);
    players[inactiveIndex].EndOfTurn (false);

    startOfTurn = true;
    endOfTurn = false;
  }
}

void Game::MinionTrigger () {

  //APNAP order
  players[playerIndex].MinionEnters ( players[inactiveIndex] , true);
  players[inactiveIndex].MinionEnters ( players[playerIndex]  , false);

  players[playerIndex].UnEnterMinions();

}



int Game::Update() {

  if (recentSwitch == false) {

    ProcessTurn(); 

    StartOfTurn(); //trigger

  }

  recentSwitch = false;

  //actions  
  if ((lastDecision = GetUserInput()) ==  QUIT) { return 3; }

  ProcessInput(); 

  MinionTrigger(); 

  EndOfTurn(); //trigger

  if (players[0].IsDead()) {
    return 1;
  }
  else if (players[1].IsDead()) {
    return 2;
  }

  players[playerIndex].CheckMyMinions();
  players[inactiveIndex].CheckMyMinions();

  if (recentSwitch) {

    ProcessTurn(); 

    StartOfTurn();

  }
  
  return 0;
}


