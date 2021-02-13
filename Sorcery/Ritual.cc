#include <iostream>
#include <string>

#include "Ritual.h"
#include "Player.h"
#include "Card.h"

using namespace std;


int ability;
int activationCost;
int numCharges;

string Ritual::GetType() const {

	return "Ritual";
}

void Ritual::StartOfTurn (Player &other) {

	if (numCharges >= activationCost) {

		if (cardName == "Dark Ritual") {
			other.IncreaseMagic();
		}

		numCharges -= activationCost;
	}
}

void Ritual::MinionEnters (Player &other, int n, bool yourMinion) {

	if (numCharges >= activationCost) {

		if (cardName == "Standstill") {

			//Doesnt matter whoses minion it is
			other.DestroyFromBoard(n);

		}
		else if (cardName == "Aura of Power") {

			if (yourMinion) {

				other.DamageMinion(n, -1);
				other.BetterMinion (n, 1); 
			}
		}

		numCharges -= activationCost;
	}
}

int Ritual::GetCharges () const {

	return this->numCharges;
}

void Ritual::IncreaseCharges (int n) {
	numCharges += n;
}


int Ritual::GetActivationCost () const {

	return this->activationCost;
}

int Ritual::GetAbility () const {

	return this->ability;
}


void Ritual::Use (Player &other, int i) {


}



Ritual::Ritual (int numCharges, int activationCost, int ability ,
	string name, string desc, int cost): Card (name, cost, desc) , 
numCharges{numCharges} , ability{ability} , activationCost{activationCost} {



}

