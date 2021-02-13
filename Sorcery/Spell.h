#ifndef SPELL_H
#define SPELL_H


#include <iostream>
#include <string>

#include "Card.h"
#include "Player.h"

using namespace std;





class Spell : public Card {
  
  int state;
  bool selfApply = true;
  bool hasTarget = false;

  public:

  string GetType() const override;

  bool HaveTarget() const override;
  bool IsSelfTarget() const override;

  int GetState() const;
  void Use (Player &other, int i) override;

  Spell (string name, string desc, int cost); 

};

#endif

