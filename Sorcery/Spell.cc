#include <iostream>
#include <string>

#include "Spell.h"
#include "Card.h"

using namespace std;

int state;
bool hasTarget = false;
bool selfApply = true;

bool Spell::HaveTarget() const {

	return hasTarget;
}

string Spell::GetType() const {

	return "Spell";
}


int Spell::GetState() const {

	return state;
}

bool Spell::IsSelfTarget() const {

	return selfApply;
}


void Spell::Use (Player &other, int i) {

	if (this->cardName != "Banish"  && i < 0) { //Basic sanity check

		other.SetError("ERROR! YOU CANNOT PLAY THIS SPELL ON A RITUAL");
	}

	if (this->cardName == "Raise Dead") {

		//checks if there are cards in graveyard
		if (other.IsCardInGraveyard() == 1) {

			//checks if there is space on the board
			if (other.CardsInBoard() < 5) {

				other.Rebirth();

			}
			else {
				other.SetError("Error! There is no space on the board");
			}
		}
		else {
			other.SetError("Error! There are no minions in the graveyard");
		}
	}
	else if (this->cardName == "Banish") {

		if (i < 0) { //attacking ritual
			other.DeleteRitual (); 
		}
		else {
			other.DestroyFromBoard (i);
		}
	}
	else if (this->cardName == "Unsummon") { 

		other.Unsummon (i);  
	}
	else if (this->cardName == "Recharge") { 

		//checks if there is a ritual
		if (other.DoesHaveRitual()) {

			other.IncreaseRitualCharges(3);

		}
		else {
			other.SetError("Error!! There is no ritual in place!");
		}

	}
	else if (this->cardName == "Disenchant") {

		other.DisenchantMinion(i);  
	}
	else if (this->cardName == "Blizzard") {

		int n = other.CardsInBoard ();

		for (int i = 0; i < n; i++) {

			other.AcceptAttackCard(i , 2);
		}
	}
	else if (this->cardName == "Custom Card") {

		
	}
}



Spell::Spell (string name, string desc, int cost): Card (name, cost, desc) {

	if (this->cardName == "Raise Dead") {
		selfApply = true;
		hasTarget = false;
	}
	else if (this->cardName == "Banish") {
		hasTarget = true;
	}
	else if (this->cardName == "Unsummon") {
		hasTarget = true;
	}
	else if (this->cardName == "Recharge") {
		selfApply = true;
		hasTarget = false;
	}
	else if (this->cardName == "Disenchant") {
		hasTarget = true;
	}
	else if (this->cardName == "Blizzard") {
		hasTarget = false;
	}
	else if (this->cardName == "Custom Card") {
		
	}

}

