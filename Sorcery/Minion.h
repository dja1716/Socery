#ifndef MINION_H
#define MINION_H


#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Card.h"
#include "Player.h"
#include "Enchantment.h"

using namespace std;

class Minion : public Card {

  int attack;
  int defense;
  int enhancedAttack = 0;
  int enhancedDefense = 0; 
  int startingAttack;
  int startingDefense;

  bool hasActivatedAbility = false;
  bool hasTriggeredAbility = false;
  int abilityCost;
  bool doesHaveTarget = false;

  bool abilityLock = false;
  int extraAbilityCost = 0;


  bool isEnhanced = false;

  bool usedThisTurn = false;
  bool enteredThisTurn = true;


  public:

  vector < shared_ptr <Card> > enchantments;

  int GetAttack() const override;
  int GetDefense() const override;
  bool IsDead () const override;

  string GetType() const override;
  int GetAbilityCost () const override;
  bool HasActivatedAbility () const override ;
  bool HasTriggeredAbility () const override ;
  bool IsNormalMinion () const override ;
  bool EnchantmentStatus () const override;
  bool HaveTarget() const override;

  void ChangeAttackBy(int amount) override;
  void AcceptAttack(int damage) override;

  void EndOfTurn (Player &other) override;
  void MinionEnters (Player &other, int n, bool yourMinion) override;


  void Use (Player &other, int i) override;
  bool WasUsed () const override;
  void MarkAsUsed () override;
  void UnUse () override;

  void AddEnchantment ( shared_ptr <Card> newCard ) override;
  void RemoveTopEnchantment () override;
  void ClearEnchantments () override;

  void SetEnter (bool value) override;
  bool EnteredThisTurn () const override;


  Minion (int attack, int defense, int abilityCost, string name, string desc, int cost);

};

#endif

