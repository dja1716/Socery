#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cstdlib>


#include "Card.h"
#include "Minion.h"

using namespace std;

class Player {

	string name;
	bool isTestingMode = false;

	string loadFile;
	bool customLoad = false;

	string myError = "";

	int magic = 3;
	int life = 20;
	int cardsInHand;
	int minionSlotsUsed = 0;
	bool hasRitual = false;

	bool isFirstTurn = true;
	bool isTurn;
	bool isPlayer1 = false;


	void MakeCard (string inputLine);


public:
  
	vector < shared_ptr <Card> > deck; 
	vector < shared_ptr <Card> > board; 
	vector < shared_ptr <Card> > graveyard; 
	vector < shared_ptr <Card> > hand; 
	vector < shared_ptr <Card> > ritual; 
	vector < shared_ptr <Card> > backOfDeck; 


  	Player ();
  	Player (string name, bool customLoad);

  	bool IsDead ();
  	void CheckMyMinions ();
  	bool CheckMinion (int i);

  	void MarkAsPlayer1();
	void SetName(string name);
	void SetTestingMode ();
	void SetFileName(string name);
	string GetName() const;

	bool DoesHaveRitual () const;
	void IncreaseRitualCharges (int n) ;


	string GetError () const;
	void ClearError();
	void SetError (string error);

	void SetLoadDeck (bool option);
	void LoadDeck ();
	void DrawCards (int cards);
	bool IsHandFull ();
	bool IsFirstTurn ();
	void SetFirstTurn ();
	bool IsDeckEmpty ();
	void GainMagic();
	void IncreaseMagic ();

	int CardsInBoard () const;
	int CardsInHand () const;
	int IsCardInGraveyard () const;

	void AcceptAttackCard (int i , int damage);

	string GetCardName (int i, int location) const;
	int GetCardCost (int i, int location) const;
	int GetCardAttack (int i, int location) const;
	int GetCardDefense (int i, int location) const;
	string GetCardDescription (int i, int location) const;
	string GetCardType (int i, int location) const;

	int GetMagic () const;
	int GetLife () const;
	void LoseLife (int damage);

	void SendToBack (int i);
	void UnUseMinions ();
	void UnEnterMinions ();
	void MoveToGraveyard (int i) ;
	void Rebirth ();
	void DestroyFromBoard (int i) ;
	void DisenchantMinion (int i) ;
	void Unsummon (int i) ;
	void DeleteRitual (); 
	void AddEnchantment (int i, shared_ptr <Card> newCard) ;
	void DamageMinion (int i, int damage) ;
	void BetterMinion (int i, int amount) ;
	void SummonAirElemental (int n) ;
	void EnhanceAllD (int amount) ;
	bool DidThisMinionEnter (int n) ;
	void SubtractMagic (int cost) ;

	void Attack (int i, Player &other);
	void Attack (int i, int j, Player &other);


	void Play (int i , Player &other);
	void Play (int i, int p, int t, Player &other);

	void Use (int i, Player &other);
	void Use (int i, int p, int t, Player &other);

	void Discard (int i); 

	void StartOfTurn (bool yourTurn) ;
	void MinionEnters (Player &other, bool yourTurn) ;
	void EndOfTurn (bool yourTurn) ;


};

#endif

