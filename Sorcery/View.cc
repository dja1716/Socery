#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "View.h"
#include "ascii_graphics.h"

using namespace std;


vector <card_template_t> myBoard;
vector <card_template_t> secondRow;

void View::Clear ()  {

	int boardSize = myBoard.size();

	if (boardSize > 0) {

		for (int i = 0; i < boardSize; i++) {

			myBoard.erase(myBoard.begin() + 0);
		}
	}
	

	boardSize = secondRow.size();

	if (boardSize > 0) {

		for (int i = 0; i < boardSize; i++) {

			secondRow.erase(secondRow.begin() + 0);
		}
	}	
}



void View::DrawPlayer (string name, bool isTurn, int magic, int life) const {

	cout << name << endl;

	if (isTurn) {

		cout << "it is your turn " << endl;
	}

	cout << "magic: " << magic << " life: " << life << endl;
}

void View::LoadBoardCard (string name, int cost, string type, string description, int attack, int defense, 
	int abilityCost, int numCharges, int activCost, int cardType) {

	card_template_t meCard;

	string myAttack = to_string(attack);
	string myDefense = to_string(defense);

	switch (cardType) {

		case 1: //Regular minion

			meCard = display_minion_no_ability(name, cost, attack, defense);
			
			break;

		case 2: //triggered minion

			meCard = display_minion_triggered_ability(name, cost, attack, defense,
                                                description);

			break;

		case 3: //activated minion

			meCard = display_minion_activated_ability(name, cost, attack, defense,
                                                 abilityCost, description);

			break;

		case 4: //ritual

			meCard = display_ritual(name, cost, activCost, description, numCharges);

			break;

		case 5: //spell

			meCard = display_spell(name, cost, description);

			break;

		case 6: //enchantment - attack + defense

			meCard = display_enchantment_attack_defence(name, cost, description, myAttack, myDefense);

			break;

		case 7: //enchantment

			meCard = display_enchantment(name, cost,description) ;

			break;

	}

	myBoard.push_back(meCard);

}

void View::LoadBoard ()  {

}

void View::LoadRitual (string name, int cost, int activCost, string description, int numCharges) {

	card_template_t meRitual = display_ritual(name, cost, activCost, description, numCharges);
	
	secondRow.push_back(meRitual);
}

void View::LoadGraveyard (string name, int cost, string type, string description, int attack, int defense, 
		int abilityCost, int numCharges, int activCost, int cardType) {

	card_template_t meCard;


	switch (cardType) {

		case 1: //Regular minion

			meCard = display_minion_no_ability(name, cost, attack, defense);
			
			break;

		case 2: //triggered minion

			meCard = display_minion_triggered_ability(name, cost, attack, defense,
                                                description);

			break;

		case 3: //activated minion

			meCard = display_minion_activated_ability(name, cost, attack, defense,
                                                 abilityCost, description);

			break;
	}


	secondRow.push_back(meCard);
	
}

void View::LoadPlayer (string name, bool isTurn, int magic, int life, int player) {

	if (secondRow.size() == 0) {

		secondRow.push_back(CARD_TEMPLATE_BORDER);
	}

	secondRow.push_back(CARD_TEMPLATE_EMPTY);


	//adds the player
	if (isTurn) {

		card_template_t mePlayer = display_player_card(player, name + " (Turn) ", life, magic);
		secondRow.push_back(mePlayer);

	}
	else {

		card_template_t mePlayer = display_player_card(player, name, life, magic);
		secondRow.push_back(mePlayer);

	}

	secondRow.push_back(CARD_TEMPLATE_EMPTY);


} 

void View::DrawBoard ()  {

	int maxHeight = 0;

	for (int i = 0; i < 5; i++) {

		if (i >= myBoard.size()) {

			myBoard.push_back(CARD_TEMPLATE_BORDER);

		}
	}


	for (int i = 0; i < 5; i++) { //goes through all border cards

		if (myBoard[i].size() > maxHeight) {

			maxHeight = myBoard[i].size();
		}
	}

	for (int h = 0; h < maxHeight; h++) {

		for (int i = 0; i < 5; i++) { //goes through all border cards

			if (myBoard[i].size() > h) { 

				cout << (myBoard[i])[h];

			}
		}

		cout << "" << endl;
	}

}

void View::DrawSecondRow () {

	int maxHeight = 0;

	for (int i = 0; i < 5; i++) {

		if (i >= secondRow.size()) {

			if (i == 0 || i == 4) {

				secondRow.push_back(CARD_TEMPLATE_BORDER);

			}
			else {

				secondRow.push_back(CARD_TEMPLATE_EMPTY);
			}
		}
	}


	for (int i = 0; i < 5; i++) { //goes through all border cards

		if (secondRow[i].size() > maxHeight) {

			maxHeight = secondRow[i].size();
		}
	}

	for (int h = 0; h < maxHeight; h++) {

		for (int i = 0; i < 5; i++) { //goes through all border cards

			if (secondRow[i].size() > h) { 

				cout << (secondRow[i])[h];

			}
		}

		cout << "" << endl;
	}
}

void View::DrawCenter () {

	for (int i = 0; i < CENTRE_GRAPHIC.size(); i++)
	{
		cout << CENTRE_GRAPHIC[i] << endl;
	}

}

void View::DrawHand() const {


}

void View::DrawRitual () const {



}

void View::DrawInspect () const {


}

void View::DrawError (string error) const{

	if (error != "") {

		cout << error << endl;

	}
}



void View::Draw (string name1, string name2) const {

	cout << "Players playing right now " << name1 << " and " << name2 << endl; 
}

