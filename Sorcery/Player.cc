#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cstdlib>

#include "Player.h"

#include "Card.h"

#include "Minion.h"
#include "Spell.h"
#include "Ritual.h"
#include "Enchantment.h"

using namespace std;

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


vector < shared_ptr <Card> > deck; 
vector < shared_ptr <Card> > board; 
vector < shared_ptr <Card> > graveyard; 
vector < shared_ptr <Card> > hand; 
vector < shared_ptr <Card> > ritual; 
vector < shared_ptr <Card> > backOfDeck; 

bool Player::IsDead () {

	if (life <= 0) {
		return true;
	} 

	return false;
}

bool Player::CheckMinion (int i) {

	if (board[i]->IsDead()) {

		DestroyFromBoard(i); //moves it to the graveyard

		return true;
	}

	return false;
}

void Player::CheckMyMinions () {

	int b = board.size();

	for (int i = 0; i < b; i++) {

		if ( CheckMinion(i) ) { //if the minion dies

			i--;
			b--;
		}
	}
}

void Player::MarkAsPlayer1() {
	this->isPlayer1 = true;
}

void Player::ClearError() {
	this->myError = "";
}

string Player::GetError () const {
	return myError;
}

void Player::SetError (string error) {
	this->myError = error;
}

void Player::SetTestingMode () {
	this->isTestingMode = true;
}

void Player::SetName(string name) {

  this->name = name; 

}

string Player::GetName() const {

	return name;
}

void Player::SetLoadDeck (bool option) {

	this->customLoad = option;
}

void Player::SetFileName(string name) {

	this->loadFile = name;
}

int Player::GetMagic () const {
	return magic;
}

void Player::IncreaseMagic () {
	magic++;
}

int Player::GetLife () const {
	return life;
}

int Player::CardsInBoard () const {
	return board.size();
}

int Player::CardsInHand () const {
	return hand.size();
}

int Player::IsCardInGraveyard () const {

	if (graveyard.size() >= 1) {
		return 1;
	}

	return 0;
}

bool Player::DoesHaveRitual () const {

	return hasRitual;
}

void Player::IncreaseRitualCharges (int n) {

	if (ritual.size() != 0) {

		ritual[0]->IncreaseCharges(n);
	}
	else {
		myError = "THERE IS NOT RITUAL FOR THIS PLAYER! ";
	}
}

void Player::AcceptAttackCard (int i , int damage) {

	board[i]->AcceptAttack(damage);
}

string Player::GetCardName (int i, int location) const {

	if (location == 0) { //board

		return board[i]->GetName(); 
	}
	else if (location == 1) { //hand

		return hand[i]->GetName();
	}
	else if (location == 2)  {

		return graveyard[graveyard.size() - 1]->GetName();
	}
	else {
		return ritual[0]->GetName();
	}
}

string Player::GetCardType (int i, int location) const {

	if (location == 0) { //board

		return board[i]->GetType(); 
	}
	else if (location == 1) { //hand

		return hand[i]->GetType();
	}
	else if (location == 2) {

		return graveyard[graveyard.size() - 1]->GetType();
	}
	else {
		return ritual[0]->GetType();
	}
}

int Player::GetCardCost (int i, int location) const {

	if (location == 0) { //board

		return board[i]->GetCost(); 
	}
	else if (location == 1) { //hand
		
		return hand[i]->GetCost();
	}
	else if (location == 2) {

		return graveyard[graveyard.size() - 1]->GetCost();
	}
	else {
		return ritual[0]->GetCost();
	}

}

int Player::GetCardAttack (int i, int location) const {

	if (location == 0) { //board

		return board[i]->GetAttack(); 
	}
	else if (location == 1) { //hand
		
		return hand[i]->GetAttack();
	}
	else if (location == 2) {

		return graveyard[graveyard.size() - 1]->GetAttack();
	}
	else {
		return ritual[0]->GetAttack();
	}
}

int Player::GetCardDefense (int i, int location) const {

	if (location == 0) { //board

		return board[i]->GetDefense(); 
	}
	else if (location == 1) { //hand
		
		return hand[i]->GetDefense();
	}
	else if (location == 2) {

		return graveyard[graveyard.size() - 1]->GetDefense();
	}
	else {
		return ritual[0]->GetDefense();
	}
}

string Player::GetCardDescription (int i, int location) const {

	if (location == 0) { //board

		return board[i]->GetDescription(); 
	}
	else if (location == 1) { //hand
		
		return hand[i]->GetDescription();
	}
	else if (location == 2) {

		return graveyard[graveyard.size() - 1]->GetDescription();
	}
	else {
		return ritual[0]->GetDescription();
	}
}



void Player::MakeCard (string inputLine) {

	if (inputLine == "Air Elemental") { 
		
		Minion tempCard1 (1,1,0,"Air Elemental", "", 0);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Minion> (tempCard1));
		deck.push_back(foo);

	}
	else if (inputLine == "Earth Elemental") {
		
		Minion tempCard1 (4,4,0,"Earth Elemental", "", 0);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Minion> (tempCard1));
		deck.push_back(foo);

	}
	else if (inputLine == "Fire Elemental") {

		Minion tempCard1 (2,2,0,"Fire Elemental", 
			"Whenever an opponent's minion enters play, deal one damage to it", 2);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Minion> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Potion Seller") {
		
		Minion tempCard1 (1,3,0,"Potion Seller", 
			"At the end of your turn, all your minions gain +0/+1", 2);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Minion> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Novice Pyromancer") {
		
		Minion tempCard1 (0,1,1,"Novice Pyromancer", 
			"Deal 1 damage to target minion", 1);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Minion> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Apprentice Summoner") {
		
		Minion tempCard1 (1,1,1,"Apprentice Summoner", 
			"Summon a 1/1 air elemental", 1);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Minion> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Master Summoner") {
		
		Minion tempCard1 (2,3,2,"Master Summoner", 
			"Summon up to three 1/1 air elemental", 3);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Minion> (tempCard1));
		deck.push_back(foo);
	}
	else if (inputLine == "Banish") {
		
		Spell tempCard1 ("Banish", "Destroy target minion or ritual", 2);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Spell> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Unsummon") {
		
		Spell tempCard1 ("Unsummon", 
			"Put target minion on the bottom of it owner's deck", 1);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Spell> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Recharge") {
		
		Spell tempCard1 ("Recharge", 
			"Your ritual gains 3 charges", 1);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Spell> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Disenchant") {
		
		Spell tempCard1 ("Disenchant", 
			"Destroy the top enchantment on target minion", 1);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Spell> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Raise Dead") {
		
		Spell tempCard1 ("Raise Dead", 
			"Resurrect the top minion in your graveyard", 1);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Spell> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Blizzard") {
		
		Spell tempCard1 ("Blizzard", 
			"Deal 2 damage to all minions", 3);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Spell> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Giant Strength") {

		Enchantment tempCard1 ("Giant Strength", 
			"", 1, 0);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Enchantment> (tempCard1));
		deck.push_back(foo);

	}
	else if (inputLine == "Magic Fatigue") {
		
		Enchantment tempCard1 ("Magic Fatigue", 
			"Enchanted minion's activated ability costs 2 more", 0, 1);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Enchantment> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Silence") {
		
		Enchantment tempCard1 ("Silence", 
			"Enchanted minion cannot use abilities", 1, 2);
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Enchantment> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Dark Ritual") {
	
		Ritual tempCard1 (5,1,0,"Dark Ritual",
			"At the start of your turn, gain 1 magic", 0); 
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Ritual> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Aura of Power") {
		
		Ritual tempCard1 (4,1,1,"Aura of Power",
			"Whenever a minion enter a player under your control, it gains +1/+1", 1); 
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Ritual> (tempCard1));
		deck.push_back(foo);
		
	}
	else if (inputLine == "Standstill") {
		
		Ritual tempCard1 (4,2,2,"Standstill",
			"Whenever a minion enter a play, destroy it", 3); 
		shared_ptr<Card> foo;
		foo = dynamic_pointer_cast<Card> (make_shared<Ritual> (tempCard1));
		deck.push_back(foo);
		
	}	
}


bool Player::IsHandFull () {

	int size = hand.size();

	if (size >= 5) {
		return true;
	}

	return false;
}

bool Player::IsFirstTurn () {
	return isFirstTurn;
}


bool Player::IsDeckEmpty () {

	int size = deck.size() + backOfDeck.size();

	if (size > 0) {
		return false;
	}

	return true;
}

void Player::GainMagic() {
	magic++;
}

void Player::SetFirstTurn () {
	isFirstTurn = false;
}

void Player::LoseLife (int damage) {

	this->life -= damage;
}

void Player::LoadDeck () {

	if (!customLoad) { loadFile = "default.deck"; }

	string input;
	ifstream infile (loadFile);

	cout << "I am loading the deck with the file " << loadFile << endl;

	while (getline(infile,input)) {

		//generate the deck line by line
		MakeCard(input);

	}
}


void Player::DrawCards (int cards) {

	//Get the size of the deck
	int sizeOfDeck;
	int randInt;

	//loop four times
	for (int i = 0; i < cards; i++)
	{
		if (deck.size() == 0) {

			if (backOfDeck.size() == 0) {

				myError = "THERE ARE NO CARDS LEFT FOR YOU TO DRAW FROM!!!";
			}
			else {

				//Swap this value from the deck -> hand
				shared_ptr<Card> poo;
				poo = dynamic_pointer_cast<Card> (backOfDeck[0]); // <- card you want to swap
				hand.push_back(poo);  // <- adds it to the hand
				backOfDeck.erase(backOfDeck.begin() + 0);  // <- deletes the position of it in deck

			}
		}
		else {
			//Get the size of the deck
			sizeOfDeck = deck.size();

			//Pick a random integer from the deck
			if (isTestingMode) {

				randInt = 0; //non randomized drawing
			}			
			else {

				randInt = rand() % sizeOfDeck;     
			}

			//Swap this value from the deck -> hand
			shared_ptr<Card> poo;
			poo = dynamic_pointer_cast<Card> (deck[randInt]); // <- card you want to swap
			hand.push_back(poo);  // <- adds it to the hand
			deck.erase(deck.begin() + randInt);  // <- deletes the position of it in deck

		}
	}
}

void Player::SendToBack (int i) {

	shared_ptr<Card> poo;
	board[i]->ClearEnchantments();
	poo = dynamic_pointer_cast<Card> (board[i]); // <- card you want to swap
	backOfDeck.push_back(poo);  // <- adds it to the hand
	board.erase(board.begin() + i);  // <- deletes the position of it in deck

}


void Player::UnUseMinions () {

	int size = board.size();

	for (int i = 0; i < size; i++) {

		board[i]->UnUse();
	}
}

void Player::UnEnterMinions () {

	int size = board.size();

	for (int i = 0; i < size; i++) {

		board[i]->SetEnter(false);
	}
}


void Player::MoveToGraveyard (int i) {

	//Swap this value from the deck -> hand
	shared_ptr<Card> poo;
	poo = dynamic_pointer_cast<Card> (board[i]); // <- card you want to swap
	graveyard.push_back(poo);  // <- adds it to the hand
	board.erase(board.begin() + i);  // <- deletes the position of it in deck
}

void Player::Rebirth () {

	//Swap this value from the deck -> hand
	int i = graveyard.size() - 1;
	shared_ptr<Card> poo;
	poo = dynamic_pointer_cast<Card> (graveyard[i]); // <- card you want to swap
	board.push_back(poo);  // <- adds it to the board
	graveyard.erase(graveyard.begin() + i);  // <- deletes the position of it in graveyard
}


void Player::DestroyFromBoard (int i) {

	if (board[i]->GetType() == "Minion") {

		//Swap this value from the deck -> hand
		board[i]->ClearEnchantments ();  
		shared_ptr<Card> poo;
		poo = dynamic_pointer_cast<Card> (board[i]); // <- card you want to swap
		graveyard.push_back(poo);  // <- adds it to the hand
		board.erase(board.begin() + i);  // <- deletes the position of it in deck

	}
	else { //if it is a ritual

		board.erase(board.begin() + i);  // <- deletes the position of it in deck
	}
}

void Player::DisenchantMinion (int i) {

	if (board[i]->GetType() == "Minion") { //checks if it is in fact a minion {

		if (board[i]->EnchantmentStatus()) { //checks if the minion is infact enchanted {

			board[i]->RemoveTopEnchantment (); 
		}
		else {

			myError = "ERROR!! THIS MINION IS NOT ENCHANTED";
		}
	}
	else {
		myError = "ERROR! THIS IS NOT A MINION";
	}
}

void Player::Unsummon (int i) { 

	if (board[i]->GetType() == "Minion") { //checks if it is in fact a minion {

		//does the swap
		SendToBack (i);

	}
	else {
		myError = "ERROR! THIS IS NOT A MINION";
	}
}


void Player::DeleteRitual () {

	ritual.erase(ritual.begin() + 0);
	hasRitual = false;
}


void Player::AddEnchantment (int i, shared_ptr <Card> newCard) {

	board[i]->AddEnchantment(newCard);
}

void Player::DamageMinion (int i, int damage) {

	board[i]->AcceptAttack(damage);
}

void Player::BetterMinion (int i, int amount) {

	board[i]->ChangeAttackBy(amount);
}

void Player::SummonAirElemental (int n) {

	if (board.size() < 5) { //if there is space for the elemental

		int spaces = 5 - board.size();

		for (int i = 0; i < n; i ++) {

			if (spaces == 0) { //ensures there is space
				break;
			}

			Minion tempCard1 (1,1,0,"Air Elemental", "", 0);
			shared_ptr<Card> foo;
			foo = dynamic_pointer_cast<Card> (make_shared<Minion> (tempCard1));
			board.push_back(foo);
			spaces--;

		}
	}
	else {
		myError = "ERROR!! THERE IS NO SPACE ON THE BOARD FOR THE AIR Elemental!!!";
	}

}

void Player::EnhanceAllD (int amount) {

	int n = board.size();

	for (int i = 0; i < n; i++) {

		board[i]->AcceptAttack(-amount);
	}
}












void Player::Attack (int i, Player &other) {

	//First checks if i is even a valid minion call
	if ( (i > 0) && (i <= board.size() )) {

		//Checks that it is in fact a minion
		if (board[i -1]->GetType() == "Minion") {

			//if the minion was not used already this turn 
			if (board[i - 1]->WasUsed() == false) {

				//Subtracts the cost


				//Attacks the other player
				other.LoseLife( board[i - 1]->GetAttack() );

				//Marks the minion as used
				board[i-1]->MarkAsUsed();

			}
			else {

				myError = "ERROR!! THIS MINION WAS ALREAYD USED THIS TURN ";
			}
		}
	}
	else {

		myError = "ERROR!! THERE IS NO MINION IN THAT POSITION!! ";
	}
}



void Player::Attack (int i, int j, Player &other) { 

	//First checks if i is even a valid minion call on our board
	if ( (i > 0) && (i <= board.size() )) { 

		if ( (j > 0) && (j <= other.CardsInBoard())) {  //checks if the card exists on the other board

			if ( (other.GetCardType( j - 1 , 0 ) == "Minion")  &&
					board[ i - 1]->GetType() == "Minion") { 		//checks if both cards is a minion 

				//if the minion was not used already this turn 
				if (board[i - 1]->WasUsed() == false) { 

					//Attack begins
					board[i - 1]->AcceptAttack ( other.GetCardAttack( (j - 1) ,0)  );
					other.AcceptAttackCard( (j - 1) , board[ i - 1 ]->GetAttack() );

					//Marks the minion as used
					board[i-1]->MarkAsUsed();

				}
				else {

					myError = "ERROR!! THIS MINION WAS ALREAYD USED THIS TURN ";
				}
			}
			else {

				myError =  "ERROR!! THAT IS NOT A MINION!!!";
			}
		}
		else {
			myError = "ERROR!! THERE IS NO MINION IN THAT POSITION!! ";
		}
	}
	else {

		myError = "ERROR!! THERE IS NO MINION IN THAT POSITION!! ";
	}

}


void Player::SubtractMagic (int cost) {

	magic -= cost;

	if (isTestingMode && (magic < 0))  {

		magic = 0;
	}
}

void Player::Play (int i, Player &other) {

	int size = hand.size();
	string type;

	//First checks if i is even a valid card in the hand
	if ( (i > 0) && (i <= size)) { 

		type = hand[i-1]->GetType();

		if ( (magic >= hand[i-1]->GetCost()) ||  isTestingMode) { //checks for enough magic or testing mode

			if (type == "Minion") {

				if (minionSlotsUsed < 5) {

					//Charges the cost
					SubtractMagic(hand[i -1]->GetCost());

					//Moves the minion from the hand to the board
					shared_ptr<Card> poo;
					poo = dynamic_pointer_cast<Card> (hand[i - 1]); 
					hand[i - 1]->SetEnter(true);
					board.push_back(poo);  
					hand.erase(hand.begin() + (i - 1) );  
					minionSlotsUsed++;

				}
				else {
					myError = "ERROR!! YOU CANNOT HAVE THIS MANY MINIONS!!";
				}
			}
			else if (type == "Ritual") {

				//Charges the cost
				SubtractMagic(hand[i - 1]->GetCost());

				//checks if there is currently a ritual on board
				if (DoesHaveRitual ()) {

					DeleteRitual();

				}

				//adds this ritual on the board
				shared_ptr<Card> poo;
				poo = dynamic_pointer_cast<Card> (hand[i - 1]); 
				ritual.push_back(poo);  
				hand.erase(hand.begin() + (i - 1) );  

				hasRitual = true;

			}
			else if (type == "Spell") {

				//Make sure that it is a no target spell
				if (hand[i -1]->HaveTarget() == false) {

					if (hand[i -1]->GetName() == "Blizzard") { //Checks if it is blizzard which is special condition

						hand[i - 1]->Use(*this, 0);
						hand[i - 1]->Use(other, 0);

					}
					else if (hand[i - 1]->IsSelfTarget()) {

						hand[i - 1]->Use(*this, 0);
					}
					else {

						hand[i -1]->Use(other, 0); 
					}

					if (myError == "" && other.GetError() == "") { //if no error occured you can delete this spell
						hand.erase(hand.begin() + (i - 1) );

						//subtract its cost too
						SubtractMagic(hand[i -1]->GetCost());
					}

				}
				else {
					myError = "ERROR!! THIS CARD HAS A TARGET!! USE OTHER COMMAND!";
				}
			}
			else {
				myError = "ERROR!! YOU CANNOT PLAY THIS TYPE OF CARD IN THAT WAY!!";
			}	

		}
		else {
			myError = "ERROR!! YOU DO NOT HAVE ENOUGH MAGIC TO PLAY THIS CARD";
		}

	}
	else {

		myError = "ERROR!! THERE IS NO CARD IN THAT POSITION!! ";
	}
}




void Player::Play (int i, int p, int t, Player &other) { 

	int size = hand.size();
	string type;
	int thisPlayer;
	int otherPlayer;


	if (isPlayer1) {
		thisPlayer = 1;
		otherPlayer = 2;
	}
	else {
		thisPlayer = 2;
		otherPlayer = 1;
	}


	//First checks if i is even a valid card in the hand
	if ( (i > 0) && (i <= size)) { 

		type = hand[i-1]->GetType();

		//checks if player number is valid
		if ( p == 1 || p == 2) { 

			if ( ( (p == otherPlayer) && ( t > other.CardsInBoard()) )  || (t == -69 && (p == otherPlayer && other.DoesHaveRitual() == false ))  ) {

				myError = "ERROR!! THERE IS NO CARD IN THAT POSITION!! ";
			}
			else {

				if ( ( (p == thisPlayer) && ( t > CardsInBoard() ) ) || (t == -69 && (p == thisPlayer && DoesHaveRitual() == false))) {

					myError = "ERROR!! THERE IS NO CARD IN THAT POSITION!! ";
				} 
				else {

					if ( (magic >= hand[i-1]->GetCost()) ||  isTestingMode) { //checks for enough magic or testing mode

						if (type == "Enchantment") { 

							//Can only work on minions
							if (t == -69) {

								myError = "ERROR!! ENCHANTMENTS CAN ONLY BE PLACED ON MINIONS";
							}
							else {

								if (p == thisPlayer) {

									//subtract its cost too
									SubtractMagic(hand[i -1]->GetCost());

									shared_ptr<Card> poo;
									poo = dynamic_pointer_cast<Card> (hand[i - 1]); 
									board[t - 1]->AddEnchantment (poo); 
									hand.erase(hand.begin() + (i - 1) );  
									
								}
								else {

									//subtract its cost too
									SubtractMagic(hand[i -1]->GetCost());

									shared_ptr<Card> poo;
									poo = dynamic_pointer_cast<Card> (hand[i - 1]); 
									other.AddEnchantment (t - 1,poo); 
									hand.erase(hand.begin() + (i - 1) );  
								}
							}

						}
						else if (type == "Spell") {

							if (hand[i - 1]->HaveTarget() == true) {

								if (p == thisPlayer) {

									hand[i - 1]->Use(*this, (t - 1) );

								}
								else {

									hand[i - 1]->Use(other, (t - 1) );
								}


								if (myError == "" && other.GetError() == "") { //if no error occured you can delete this spell
									
									//subtract its cost too
									SubtractMagic(hand[i -1]->GetCost());

									hand.erase(hand.begin() + (i - 1) );
								}

							}
							else {
								myError = "ERROR!! THIS CARD DOESN'T HAVE A TARGET!! USE OTHER COMMAND!";
							}

						}
						else {
							myError = "ERROR!! YOU CANNOT PLAY THIS TYPE OF CARD IN THAT WAY!!";
						}
					}
					else {

						myError = "ERROR!! YOU DO NOT HAVE ENOUGH MAGIC TO PLAY THIS CARD";
					}
				}
			}
		}
		else {
			myError = "ERROR!! THAT IS NOT A VALID PLAYER SELECTION";
		}
	}
	else {
		myError = "ERROR!! THERE IS NO CARD IN THAT POSITION!! ";
	}
}






void Player::Use (int i, Player &other) {

	int size = board.size();
	string type;

	//First checks if i is even a valid card in the hand
	if ( (i > 0) && (i <= size)) { 

		type = board[i-1]->GetType();

		if ( (magic >= board[i - 1]->GetAbilityCost()) ||  isTestingMode) { //checks for enough magic or testing mode

			if (type == "Minion") {

				if (board[i - 1]->HasActivatedAbility ()) {

					if (board[i - 1]->HaveTarget() == false) {

						if (board[i - 1]->WasUsed() == false) {

							//Ensures there is space for the elemental
							if (board.size() < 5) {

								board[i - 1]->Use(*this, 0);
							}
							else {
								myError = "ERROR!! THERE IS NO SPACE ON THE BOARD!!";
							}

						}
						else {
							myError = "ERROR!! THIS MINION WAS ALREAYD USED THIS TURN!";
						}
					}
					else {
						myError = "ERROR!! THIS ABILITY NEEDS A TARGET";
					}
				}
				else {
					myError = "ERROR!! THIS MINION DOESNT HAVE AN ACTIVATED ABILTY";
				}

			}
			else {
				myError = "ERROR!! YOU CANNOT PLAY THIS TYPE OF CARD IN THAT WAY!!";
			}	
		}
		else {
			myError = "ERROR!! YOU DO NOT HAVE ENOUGH MAGIC TO USE THIS CARD";
		}
	}
	else {

		myError = "ERROR!! THERE IS NO CARD IN THAT POSITION!! ";
	}
}





void Player::Use (int i, int p, int t, Player &other) { 

	int size = board.size();
	string type;
	int thisPlayer;
	int otherPlayer;


	if (isPlayer1) {
		thisPlayer = 1;
		otherPlayer = 2;
	}
	else {
		thisPlayer = 2;
		otherPlayer = 1;
	}


	//First checks if i is even a valid card in the board
	if ( (i > 0) && (i <= size)) { 

		type = board[i-1]->GetType();

		//checks if player number is valid
		if ( p == 1 || p == 2) { 

			if ( ( (p == otherPlayer) && ( t > other.CardsInBoard()) )  || (t == -69 &&  other.DoesHaveRitual() == false)  ) {

				myError = "ERROR!! THERE IS NO CARD IN THAT POSITION!! ";
			}
			else {

				if ( ( (p == thisPlayer) && ( t > CardsInBoard() ) ) || (t == -69 && DoesHaveRitual() == false) ) {

					myError = "ERROR!! THERE IS NO CARD IN THAT POSITION!! ";
				} 
				else {

					if ( (magic >= board[i - 1]->GetAbilityCost()) ||  isTestingMode) { //checks for enough magic or testing mode

						if (type == "Minion") { 

							if (board[i - 1]->HasActivatedAbility () ) {

								if (board[i - 1]->HaveTarget()) {

									if (board[i - 1]->WasUsed() == false) {

										if (p == thisPlayer) {

											board[i - 1]->Use(*this, (t - 1) );

										}
										else {

											board[i - 1]->Use(other, (t - 1) );
										}
									}
									else {

										myError = "ERROR!! THIS MINION WAS ALREADY USED THIS TURN";
									}	

								}
								else {
									myError = "ERROR!! THIS ABILITY DOESNT HAVE A TARGET";
								}

							}
							else {
								myError = "ERROR!! THIS MINION DOESNT HAVE AN ACTIVATED ABILTY";
							}

						}
						else {
							myError = "ERROR!! YOU CANNOT PLAY THIS TYPE OF CARD IN THAT WAY!!";
						}
					}
					else {
						myError = "ERROR!! YOU DO NOT HAVE ENOUGH MAGIC TO USE THIS CARD";
					}
				}
			}
		}
		else {
			myError = "ERROR!! THAT IS NOT A VALID PLAYER SELECTION";
		}
	}
	else {
		myError = "ERROR!! THERE IS NO CARD IN THAT POSITION!! ";
	}
}


















void Player::Discard (int i) {

	if ( (i > 0) &&  (i <= hand.size()) ) {

		hand.erase(hand.begin() + (i - 1) ); 
	}
	else {
		myError = "ERROR!!! NOT A VALID CARD!!";
	}
}








void Player::StartOfTurn (bool yourTurn) {

	if (DoesHaveRitual () && yourTurn) {

		ritual[0]->StartOfTurn(*this);
	}
}

bool Player::DidThisMinionEnter (int n) {
	return board[n]->EnteredThisTurn ();
}

void Player::MinionEnters (Player &other, bool yourTurn) {

	int n = board.size();
	int x = other.CardsInBoard();
	bool didMinionDie = false;

	if (yourTurn) { //look through your own rituals and minions that do effects on your own minions

		for (int i = 0; i < n; i++) {  //goes through every card on your board

			if (board[i]->EnteredThisTurn()) { //checks if the minion entered this turn

				for (int h = 0; h < n; h++) {  //Goes through all minions on your board

					if (board[h]->HasTriggeredAbility ())  { //if a minion on the board has a triggered ability

						board[h]->MinionEnters(*this, i, true); 

						//checks if the minion is still alive
						didMinionDie = CheckMinion(i);

						//if dead, break out of this and decrement i by 1
						if (didMinionDie) {

							i -= 1;
							break;
						}
					}
				}

				if (didMinionDie == false) { //checks if the minion that we wanted died

					//Checks if there is a ritual
					if (DoesHaveRitual()) {

						ritual[0]->MinionEnters(*this, i, true);

					}

					//checks if the minion is still alive
					didMinionDie = CheckMinion(i);

					//if dead, break out of this and decrement i by 1
					if (didMinionDie) {

						i -= 1;
						break;
					}
				}
				else {

					break;
				}
			}
		}
	}
	else {

		for (int i = 0; i < x; i++) { //goes through the other players board
			
			if (other.DidThisMinionEnter(i) ) { //checks if the other players minion at position i entered this turn

				//goes through all of your minions
				for (int h = 0; h < n; h++) {

					if (board[h]->HasTriggeredAbility () )  { //if a minion on the board has a triggered ability

						board[h]->MinionEnters(other, i, false); 

						//checks if the minion is still alive
						didMinionDie = other.CheckMinion(i);

						//if dead, break out of this and decrement i by 1
						if (didMinionDie) {

							i -= 1;
							break;
						}
					}
				}


				if (didMinionDie == false) { //checks if the minion that we wanted died

					//Checks if there is a ritual
					if (DoesHaveRitual ()) {

						ritual[0]->MinionEnters(other, i, false);

					}

					//checks if the minion is still alive
					didMinionDie = other.CheckMinion(i);

					//if dead, break out of this and decrement i by 1
					if (didMinionDie) {

						i -= 1;
						break;
					}
				}
				else {

					break;
				}
			}
		} 
	}
}



void Player::EndOfTurn (bool yourTurn) {

	int b = board.size();

	for (int i = 0; i < b; i++) { //goes through the board

		if (board[i]->HasTriggeredAbility()) { //if it has a triggered ability

			board[i]->EndOfTurn(*this);

		}
	}
}




Player::Player () {

   /* initialize random seed: */
  srand (time(NULL));

}

Player::Player (string name, bool customLoad): name{name} , customLoad{customLoad} {

   /* initialize random seed: */
  srand (time(NULL));

}






