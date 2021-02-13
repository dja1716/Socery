#ifndef RITUAL_H
#define RITUAL_H

#include <iostream>
#include <string>

#include "Card.h"
#include "Player.h"

using namespace std;

class Player;

class Ritual : public Card {
  
  int ability;
  int activationCost;
  int numCharges;

  public:

  string GetType() const override;

  int GetCharges () const override;
  void IncreaseCharges (int n) override;
  int GetActivationCost () const override;
  int GetAbility () const override;

  void Use(Player &other, int i) override;
  void StartOfTurn (Player &other) override;
  void MinionEnters (Player &other, int n, bool yourMinion) override;

  Ritual (int numCharges, int activationCost, int ability ,string name, string desc, int cost);

};

#endif
