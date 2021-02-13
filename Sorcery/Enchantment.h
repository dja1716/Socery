#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H


#include <iostream>
#include <string>

#include "Card.h"

using namespace std;

class Enchantment : public Card {

	int enhancement;
	int plusAttack;
	int plusDefense;
	bool plusQualities = false;

	public: 

	int GetEnhancement() const override;

	string GetType() const override;

	int GetAttack () const override;
	int GetDefense () const override;


	Enchantment (string name, string desc, int cost, int enhancement);

};


#endif


