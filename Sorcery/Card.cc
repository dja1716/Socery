#include <iostream>
#include <string>

#include "Card.h"
#include <memory>
#include <vector>
//#include "Player.h"


using namespace std;

string cardName;
string description;
string type; 

int cost = 0;


//General card qualities
string Card::GetName() const{
  return this->cardName;
}

int Card::GetCost() const{
  return this->cost;
}

string Card::GetDescription() const {
  return this->description;
}

string Card::GetType() const {
	return "Card";
}


//For the spell
bool Card::HaveTarget() const { return false; }  //this is for minion as well
void Card::Use (Player &other, int i) { } ; //this is for minion as well
bool Card::IsSelfTarget() const { return false; }


//For the minion
int Card::GetAttack () const { return -1; }
int Card::GetDefense () const { return -1; } 
void Card::ChangeAttackBy (int amount) { }
void Card::AcceptAttack (int damage) { } 
bool Card::WasUsed () const { return false; }
void Card::MarkAsUsed () { };
void Card::UnUse () { };
bool Card::EnchantmentStatus () const { return false; } ;
void Card::AddEnchantment ( shared_ptr <Card> newCard ) { };
void Card::RemoveTopEnchantment () { };
void Card:: ClearEnchantments () { };
void Card::SetEnter (bool value) { } ;
bool Card::EnteredThisTurn () const { return false; } ;
bool Card::HasActivatedAbility () const { return false; } ;
bool Card::HasTriggeredAbility () const { return false; } ;
int Card::GetAbilityCost () const { return 0; };
void Card::EndOfTurn (Player &other) { } ;
void Card::MinionEnters (Player &other, int n, bool yourMinion) { } ; //for minion and ritual
bool Card::IsDead () const { return false; } ;
bool Card::IsNormalMinion () const { return false; } ;

//For Ritual cards
int Card::GetCharges () const { return -1; }
int Card::GetActivationCost () const { return -1; };
int Card::GetAbility () const { return -1; };
void Card::StartOfTurn (Player &other) {  } ;
void Card::IncreaseCharges (int n) { } ;



//For the enchantment
int Card::GetEnhancement() const { return -1; }





Card::Card (string name, int cost, string descrip): cardName{name} , cost{cost}, description{descrip} {



}
