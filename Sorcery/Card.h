#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>

//#include "Player.h"

using namespace std;

class Player; //forward declaration of the player class

class Card {

	protected:

	string cardName;
	string description;
	int cost = 0;

	public:

	string GetName() const;
	int GetCost() const;	
	string GetDescription () const;

	virtual string GetType() const;

	//For the spell
	virtual bool HaveTarget() const;
	virtual void Use (Player &other, int i) ;
	virtual bool IsSelfTarget() const ;

	//For the minion
	virtual int GetAttack () const ;
	virtual int GetDefense () const ;
	virtual void ChangeAttackBy (int amount) ;
	virtual void AcceptAttack(int damage) ;
	virtual bool WasUsed () const ;
	virtual void MarkAsUsed () ;
  	virtual void UnUse () ;
  	virtual bool EnchantmentStatus () const ;
  	virtual void AddEnchantment ( shared_ptr <Card> newCard ) ;
  	virtual void RemoveTopEnchantment () ;
  	virtual void ClearEnchantments () ;
  	virtual void SetEnter (bool value) ;
  	virtual bool EnteredThisTurn () const ;
  	virtual bool HasActivatedAbility () const ;
  	virtual bool HasTriggeredAbility () const ;
  	virtual int GetAbilityCost () const ;
  	virtual void EndOfTurn (Player &other) ;
  	virtual void MinionEnters (Player &other, int n, bool yourMinion) ;
  	virtual bool IsDead () const ; 
  	virtual bool IsNormalMinion () const ;

	//For the Ritual
	virtual int GetCharges () const;
	virtual void IncreaseCharges (int n) ;
	virtual int GetActivationCost () const;
	virtual int GetAbility () const;
	virtual void StartOfTurn (Player &other) ;

	//For the enchantment
	virtual int GetEnhancement() const;

	Card (string name, int cost, string descrip);

};

#endif


