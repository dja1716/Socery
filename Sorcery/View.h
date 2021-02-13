#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "ascii_graphics.h"

using namespace std;

typedef std::vector<std::string> card_template_t;


class View {

	vector <card_template_t> myBoard;
	vector <card_template_t> secondRow;

	void PlayerNames ();

	public:

	void Clear () ;

	void Draw (string name1, string name2) const ;

	void DrawPlayer (string name, bool isTurn, int magic, int life) const;

	void LoadBoardCard (string name, int cost, string type, string description, int attack, int defense, 
		int abilityCost, int numCharges, int activCost, int cardType)  ;

	void LoadBoard ()  ;

	void LoadGraveyard (string name, int cost, string type, string description, int attack, int defense, 
		int abilityCost, int numCharges, int activCost, int cardType) ;

	void LoadRitual (string name, int cost, int activCost, string description, int numCharges) ;



	void LoadPlayer (string name, bool isTurn, int magic, int life, int player) ;

	void DrawBoard () ;

	void DrawSecondRow () ;

	void DrawHand () const; 

	void DrawError (string error) const; 

	void DrawRitual () const;

	void DrawInspect () const;

	void DrawCenter () ;

};



#endif

