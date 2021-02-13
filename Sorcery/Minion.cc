#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Card.h"
#include "Minion.h"
#include "Player.h"
#include "Enchantment.h"

using namespace std;

int attack;
int defense;
int enhancedAttack = 0;
int enhancedDefense = 0; 
int startingAttack;
int startingDefense;

bool isEnhanced = false;

bool hasActivatedAbility = false;
bool hasTriggeredAbility = false;
bool doesHaveTarget = false;

int abilityCost;

bool abilityLock = false;
int extraAbilityCost = 0;

bool usedThisTurn = false;
bool enteredThisTurn = true;

vector < shared_ptr <Card> > enchantments; 

bool Minion::IsNormalMinion () const {

	if (hasTriggeredAbility == false && hasActivatedAbility == false) {

		return true;
	}

	return false;
}

bool Minion::IsDead () const {

	if (defense <= 0) {

		return true;
	}

	return false;
}

int Minion::GetAbilityCost () const {

	return abilityCost + extraAbilityCost;
}

bool Minion::HaveTarget() const {

	return doesHaveTarget;
}

bool Minion::HasActivatedAbility () const {

	return hasActivatedAbility;
}

bool Minion::HasTriggeredAbility () const {
	
	return hasTriggeredAbility;
}

void Minion::SetEnter (bool value) {

	enteredThisTurn = value;
}

bool Minion::EnteredThisTurn () const {
	return enteredThisTurn;
}


void Minion::MinionEnters (Player &other, int n, bool yourMinion) {

	if (cardName == "Fire Elemental" && yourMinion == false) {

		other.DamageMinion(n, 1); 

	}
}

void Minion::EndOfTurn (Player &other) {

	if (cardName == "Potion Seller") {

		other.EnhanceAllD(1);
	}
}

void Minion::Use (Player &other, int i) { 

	if (abilityLock == false) {

		if (cardName == "Novice Pyromancer" ) {
			
			//deals one damage to minion i
			other.DamageMinion(i, 1);
			usedThisTurn = true;

			//subtract magic cost
			other.SubtractMagic( GetAbilityCost() );
		} 
		else if (cardName == "Apprentice Summoner") {
			
			other.SummonAirElemental(1);
			usedThisTurn = true;

			//subtract magic cost
			other.SubtractMagic( GetAbilityCost() );

		}
		else if (cardName == "Master Summoner") {

			other.SummonAirElemental(3);
			usedThisTurn = true;

			//subtract magic cost
			other.SubtractMagic( GetAbilityCost() );
		}
	}
	else {
		other.SetError("ERROR! THIS MINION HAS AN ABILITY LOCK PLACED ON IT");
	}

} 

void Minion::AddEnchantment ( shared_ptr <Card> newCard ) {

	int newPos;

	enchantments.push_back(newCard);

	newPos = enchantments.size() - 1;

	if (enchantments[newPos]->GetName() == "Giant Strength") {
		enhancedDefense += 2;
		enhancedAttack += 2;

	}
	else if (enchantments[newPos]->GetName() == "Magic Fatigue") {
		
		if (HasActivatedAbility ()) {
			extraAbilityCost += 2;

		}
	}
	else if (enchantments[newPos]->GetName() == "Silence") {
		abilityLock = true;

	}

	isEnhanced = true;

}

void Minion::RemoveTopEnchantment () {

	int pos; 
	pos = enchantments.size() - 1; 


	if (enchantments[pos]->GetName() == "Giant Strength") {
		enhancedDefense -= 2;
		enhancedAttack -= 2;
	}
	else if (enchantments[pos]->GetName() == "Magic Fatigue") {
		extraAbilityCost -= 2;
	}
	else if (enchantments[pos]->GetName() == "Silence") {
		
		abilityLock = false;

		for (int i = 0; i < pos; i++) { //ignores the top

			if (enchantments[i]->GetName() == "Silence") {

				abilityLock = true;
				break;
			}
		}
	}
						

	enchantments.erase(enchantments.begin() + pos ); //erases it from existance

	if (enchantments.size() == 0) {

		isEnhanced = false;
	}

}

void Minion::ClearEnchantments () {

	int size = enchantments.size();

	attack = startingAttack;
	defense = startingDefense;

	enhancedDefense = 0;
	enhancedAttack = 0;
	abilityLock = false;
	extraAbilityCost = 0;


	isEnhanced = false;


	for (int i = 0; i < size; i++) {

		enchantments.erase(enchantments.begin() + 0); 
	}
}


bool Minion::EnchantmentStatus () const {
	return isEnhanced;
}


bool Minion::WasUsed () const {

	return usedThisTurn;
}

void Minion::MarkAsUsed () {
	
	usedThisTurn = true;
} 

void Minion::UnUse () {
	
	usedThisTurn = false;
}




int Minion::GetAttack() const {

	if (isEnhanced) {
		return enhancedAttack + attack;
	}

  return attack;
}

int Minion::GetDefense() const {

	if (isEnhanced) {
		return enhancedDefense + defense;
	}

  return defense;
}


string Minion::GetType() const {

	return "Minion";
}


void Minion::ChangeAttackBy(int amount) {
  attack += amount;
}

void Minion::AcceptAttack(int damage) {
  defense -= damage;
}



Minion::Minion (int attack, int defense, int abilityCost,string name, string desc, 
	int cost): Card (name, cost, desc) , attack{attack} , defense{defense} , abilityCost{abilityCost}
{
	startingDefense = defense;
	startingAttack = attack;

	if (cardName == "Novice Pyromancer" ) {
		hasActivatedAbility = true;
		doesHaveTarget = true;
	} 
	else if (cardName == "Apprentice Summoner" || cardName == "Master Summoner") {
		hasActivatedAbility = true;
	}
	else if (cardName == "Fire Elemental" || cardName == "Potion Seller") {
		hasTriggeredAbility = true;
	}


}
