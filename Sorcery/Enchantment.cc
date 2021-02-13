#include <iostream>
#include <string>

#include "Enchantment.h"
#include "Card.h"

using namespace std;

int enhancement;
int plusAttack;
int plusDefense;
bool plusQualities = false;

int Enchantment::GetEnhancement () const {

	return this->enhancement;
}

string Enchantment::GetType () const {

	return "Enchantment";
}

int Enchantment::GetAttack () const { 

	if (cardName == "Giant Strength")
	{
		return 2;
	}

	return 0;
}

int Enchantment::GetDefense () const { 

	if (cardName == "Giant Strength")
	{
		return 2;
	}

	return 0;

 } 


Enchantment::Enchantment (string name, string desc, int cost, 
	int enhancement): Card (name, cost, desc) , enhancement{enhancement} {

}

