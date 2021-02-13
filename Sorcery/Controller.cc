#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

#include "Controller.h"
#include "View.h"
#include "Game.h"
#include "Player.h"


using namespace std;



void Controller::Draw (const Game &meGame, View &meView) {

	int mode = meGame.mode;
	bool player1Turn = meGame.player1Turn;

	//Clears the screen before drawing new stuff
	system("clear");
	meView.Clear(); 




	int n = 0;
	int top = 0;

	if ( ((mode == 1 || mode == 2) && player1Turn) || (player1Turn == false)) { 

		if (mode == 1 || (player1Turn == false) ) { //board

			n = meGame.players[0].board.size();

			for (int i = 0; i < n; i++) {

				if (meGame.players[0].board[i]->HasTriggeredAbility () ) {

					meView.LoadBoardCard( meGame.players[0].board[i]->GetName(),
						meGame.players[0].board[i]->GetCost(), 
						"", meGame.players[0].board[i]->GetDescription(),
						meGame.players[0].board[i]->GetAttack(), 
						meGame.players[0].board[i]->GetDefense(), 
						meGame.players[0].board[i]->GetAbilityCost(), 
						meGame.players[0].board[i]->GetCharges(), 
						meGame.players[0].board[i]->GetActivationCost (), 2);
				}
				else if (meGame.players[0].board[i]->HasActivatedAbility () ) {

					meView.LoadBoardCard( meGame.players[0].board[i]->GetName(),
						meGame.players[0].board[i]->GetCost(), 
						"", meGame.players[0].board[i]->GetDescription(),
						meGame.players[0].board[i]->GetAttack(), 
						meGame.players[0].board[i]->GetDefense(), 
						meGame.players[0].board[i]->GetAbilityCost(), 
						meGame.players[0].board[i]->GetCharges(), 
						meGame.players[0].board[i]->GetActivationCost (), 3);
				}
				else if (meGame.players[0].board[i]->IsNormalMinion () ) {

					meView.LoadBoardCard( meGame.players[0].board[i]->GetName(),
						meGame.players[0].board[i]->GetCost(), 
						"", meGame.players[0].board[i]->GetDescription(),
						meGame.players[0].board[i]->GetAttack(), 
						meGame.players[0].board[i]->GetDefense(), 
						meGame.players[0].board[i]->GetAbilityCost(), 
						meGame.players[0].board[i]->GetCharges(), 
						meGame.players[0].board[i]->GetActivationCost (), 1);
				}

			}
		}
		else if (mode == 2) {

			n = meGame.players[0].hand.size();

			for (int i = 0; i < n; i++) {

				if (meGame.players[0].hand[i]->HasTriggeredAbility () ) {

					meView.LoadBoardCard( meGame.players[0].hand[i]->GetName(),
						meGame.players[0].hand[i]->GetCost(), 
						"", meGame.players[0].hand[i]->GetDescription(),
						meGame.players[0].hand[i]->GetAttack(), 
						meGame.players[0].hand[i]->GetDefense(), 
						meGame.players[0].hand[i]->GetAbilityCost(), 
						meGame.players[0].hand[i]->GetCharges(), 
						meGame.players[0].hand[i]->GetActivationCost (), 2);
				}
				else if (meGame.players[0].hand[i]->HasActivatedAbility () ) {

					meView.LoadBoardCard( meGame.players[0].hand[i]->GetName(),
						meGame.players[0].hand[i]->GetCost(), 
						"", meGame.players[0].hand[i]->GetDescription(),
						meGame.players[0].hand[i]->GetAttack(), 
						meGame.players[0].hand[i]->GetDefense(), 
						meGame.players[0].hand[i]->GetAbilityCost(), 
						meGame.players[0].hand[i]->GetCharges(), 
						meGame.players[0].hand[i]->GetActivationCost (), 3);
				}
				else if (meGame.players[0].hand[i]->IsNormalMinion () ) {

					meView.LoadBoardCard( meGame.players[0].hand[i]->GetName(),
						meGame.players[0].hand[i]->GetCost(), 
						"", meGame.players[0].hand[i]->GetDescription(),
						meGame.players[0].hand[i]->GetAttack(), 
						meGame.players[0].hand[i]->GetDefense(), 
						meGame.players[0].hand[i]->GetAbilityCost(), 
						meGame.players[0].hand[i]->GetCharges(), 
						meGame.players[0].hand[i]->GetActivationCost (), 1);
				}
				else if (meGame.players[0].hand[i]->GetType() == "Spell") {

					meView.LoadBoardCard( meGame.players[0].hand[i]->GetName(),
						meGame.players[0].hand[i]->GetCost(), 
						"", meGame.players[0].hand[i]->GetDescription(),
						meGame.players[0].hand[i]->GetAttack(), 
						meGame.players[0].hand[i]->GetDefense(), 
						meGame.players[0].hand[i]->GetAbilityCost(), 
						meGame.players[0].hand[i]->GetCharges(), 
						meGame.players[0].hand[i]->GetActivationCost (), 5);
				}
				else if (meGame.players[0].hand[i]->GetType() == "Ritual") {

					meView.LoadBoardCard( meGame.players[0].hand[i]->GetName(),
						meGame.players[0].hand[i]->GetCost(), 
						"", meGame.players[0].hand[i]->GetDescription(),
						meGame.players[0].hand[i]->GetAttack(), 
						meGame.players[0].hand[i]->GetDefense(), 
						meGame.players[0].hand[i]->GetAbilityCost(), 
						meGame.players[0].hand[i]->GetCharges(), 
						meGame.players[0].hand[i]->GetActivationCost (), 4);
				}
				else if (meGame.players[0].hand[i]->GetName() == "Giant Strength") {

					meView.LoadBoardCard( meGame.players[0].hand[i]->GetName(),
						meGame.players[0].hand[i]->GetCost(), 
						"", meGame.players[0].hand[i]->GetDescription(),
						meGame.players[0].hand[i]->GetAttack(), 
						meGame.players[0].hand[i]->GetDefense(), 
						meGame.players[0].hand[i]->GetAbilityCost(), 
						meGame.players[0].hand[i]->GetCharges(), 
						meGame.players[0].hand[i]->GetActivationCost (), 6);
				}
				else if (meGame.players[0].hand[i]->GetType() == "Enchantment") {

					meView.LoadBoardCard( meGame.players[0].hand[i]->GetName(),
						meGame.players[0].hand[i]->GetCost(), 
						"", meGame.players[0].hand[i]->GetDescription(),
						meGame.players[0].hand[i]->GetAttack(), 
						meGame.players[0].hand[i]->GetDefense(), 
						meGame.players[0].hand[i]->GetAbilityCost(), 
						meGame.players[0].hand[i]->GetCharges(), 
						meGame.players[0].hand[i]->GetActivationCost (), 7);
				}
			}
		}

		if (meGame.players[0].DoesHaveRitual()) {

			//Load the ritual
			meView.LoadRitual(meGame.players[0].ritual[0]->GetName(),
						meGame.players[0].ritual[0]->GetCost(),
						meGame.players[0].ritual[0]->GetActivationCost (), 
						meGame.players[0].ritual[0]->GetDescription(), 
						meGame.players[0].ritual[0]->GetCharges());

		}

		meView.LoadPlayer (meGame.GetPlayer1Name(), player1Turn, 
				meGame.players[0].GetMagic(), meGame.players[0].GetLife(), 1);


		top = meGame.players[0].graveyard.size() - 1;

		if (top >= 0) {

			if (meGame.players[0].graveyard[top]->HasTriggeredAbility () ) { //triggered minion

				meView.LoadGraveyard( meGame.players[0].graveyard[top]->GetName(),
					meGame.players[0].graveyard[top]->GetCost(), 
					"", meGame.players[0].graveyard[top]->GetDescription(),
					meGame.players[0].graveyard[top]->GetAttack(), 
					meGame.players[0].graveyard[top]->GetDefense(), 
					meGame.players[0].graveyard[top]->GetAbilityCost(), 
					meGame.players[0].graveyard[top]->GetCharges(), 
					meGame.players[0].graveyard[top]->GetActivationCost (), 2);
			}
			else if (meGame.players[0].graveyard[top]->HasActivatedAbility () ) { //activated minion

				meView.LoadGraveyard( meGame.players[0].graveyard[top]->GetName(),
					meGame.players[0].graveyard[top]->GetCost(), 
					"", meGame.players[0].graveyard[top]->GetDescription(),
					meGame.players[0].graveyard[top]->GetAttack(), 
					meGame.players[0].graveyard[top]->GetDefense(), 
					meGame.players[0].graveyard[top]->GetAbilityCost(), 
					meGame.players[0].graveyard[top]->GetCharges(), 
					meGame.players[0].graveyard[top]->GetActivationCost (), 3);
			}
			else if (meGame.players[0].graveyard[top]->IsNormalMinion () ) { //normal minion

				meView.LoadGraveyard( meGame.players[0].graveyard[top]->GetName(),
					meGame.players[0].graveyard[top]->GetCost(), 
					"", meGame.players[0].graveyard[top]->GetDescription(),
					meGame.players[0].graveyard[top]->GetAttack(), 
					meGame.players[0].graveyard[top]->GetDefense(), 
					meGame.players[0].graveyard[top]->GetAbilityCost(), 
					meGame.players[0].graveyard[top]->GetCharges(), 
					meGame.players[0].graveyard[top]->GetActivationCost (), 1);
			}
		}


		meView.DrawSecondRow();
		meView.DrawBoard();

	}





	meView.DrawCenter () ;





	meView.Clear(); 




	if ( ((mode == 1 || mode == 2) && player1Turn == false) || (player1Turn == true)) { 

		if ( (mode == 1) || (player1Turn == true)  ) { //board

			n = meGame.players[1].board.size();

			for (int i = 0; i < n; i++) {

				if (meGame.players[1].board[i]->HasTriggeredAbility () ) {

					meView.LoadBoardCard( meGame.players[1].board[i]->GetName(),
						meGame.players[1].board[i]->GetCost(), 
						"", meGame.players[1].board[i]->GetDescription(),
						meGame.players[1].board[i]->GetAttack(), 
						meGame.players[1].board[i]->GetDefense(), 
						meGame.players[1].board[i]->GetAbilityCost(), 
						meGame.players[1].board[i]->GetCharges(), 
						meGame.players[1].board[i]->GetActivationCost (), 2);
				}
				else if (meGame.players[1].board[i]->HasActivatedAbility () ) {

					meView.LoadBoardCard( meGame.players[1].board[i]->GetName(),
						meGame.players[1].board[i]->GetCost(), 
						"", meGame.players[1].board[i]->GetDescription(),
						meGame.players[1].board[i]->GetAttack(), 
						meGame.players[1].board[i]->GetDefense(), 
						meGame.players[1].board[i]->GetAbilityCost(), 
						meGame.players[1].board[i]->GetCharges(), 
						meGame.players[1].board[i]->GetActivationCost (), 3);
				}
				else if (meGame.players[1].board[i]->IsNormalMinion () ) {

					meView.LoadBoardCard( meGame.players[1].board[i]->GetName(),
						meGame.players[1].board[i]->GetCost(), 
						"", meGame.players[1].board[i]->GetDescription(),
						meGame.players[1].board[i]->GetAttack(), 
						meGame.players[1].board[i]->GetDefense(), 
						meGame.players[1].board[i]->GetAbilityCost(), 
						meGame.players[1].board[i]->GetCharges(), 
						meGame.players[1].board[i]->GetActivationCost (), 1);
				}

			}
		}
		else if (mode == 2) { //displays hand

			n = meGame.players[1].hand.size();

			for (int i = 0; i < n; i++) {

				if (meGame.players[1].hand[i]->HasTriggeredAbility () ) {

					meView.LoadBoardCard( meGame.players[1].hand[i]->GetName(),
						meGame.players[1].hand[i]->GetCost(), 
						"", meGame.players[1].hand[i]->GetDescription(),
						meGame.players[1].hand[i]->GetAttack(), 
						meGame.players[1].hand[i]->GetDefense(), 
						meGame.players[1].hand[i]->GetAbilityCost(), 
						meGame.players[1].hand[i]->GetCharges(), 
						meGame.players[1].hand[i]->GetActivationCost (), 2);
				}
				else if (meGame.players[1].hand[i]->HasActivatedAbility () ) {

					meView.LoadBoardCard( meGame.players[1].hand[i]->GetName(),
						meGame.players[1].hand[i]->GetCost(), 
						"", meGame.players[1].hand[i]->GetDescription(),
						meGame.players[1].hand[i]->GetAttack(), 
						meGame.players[1].hand[i]->GetDefense(), 
						meGame.players[1].hand[i]->GetAbilityCost(), 
						meGame.players[1].hand[i]->GetCharges(), 
						meGame.players[1].hand[i]->GetActivationCost (), 3);
				}
				else if (meGame.players[1].hand[i]->IsNormalMinion () ) {

					meView.LoadBoardCard( meGame.players[1].hand[i]->GetName(),
						meGame.players[1].hand[i]->GetCost(), 
						"", meGame.players[1].hand[i]->GetDescription(),
						meGame.players[1].hand[i]->GetAttack(), 
						meGame.players[1].hand[i]->GetDefense(), 
						meGame.players[1].hand[i]->GetAbilityCost(), 
						meGame.players[1].hand[i]->GetCharges(), 
						meGame.players[1].hand[i]->GetActivationCost (), 1);
				}
				else if (meGame.players[1].hand[i]->GetType() == "Spell") {

					meView.LoadBoardCard( meGame.players[1].hand[i]->GetName(),
						meGame.players[1].hand[i]->GetCost(), 
						"", meGame.players[1].hand[i]->GetDescription(),
						meGame.players[1].hand[i]->GetAttack(), 
						meGame.players[1].hand[i]->GetDefense(), 
						meGame.players[1].hand[i]->GetAbilityCost(), 
						meGame.players[1].hand[i]->GetCharges(), 
						meGame.players[1].hand[i]->GetActivationCost (), 5);
				}
				else if (meGame.players[1].hand[i]->GetType() == "Ritual") {

					meView.LoadBoardCard( meGame.players[1].hand[i]->GetName(),
						meGame.players[1].hand[i]->GetCost(), 
						"", meGame.players[1].hand[i]->GetDescription(),
						meGame.players[1].hand[i]->GetAttack(), 
						meGame.players[1].hand[i]->GetDefense(), 
						meGame.players[1].hand[i]->GetAbilityCost(), 
						meGame.players[1].hand[i]->GetCharges(), 
						meGame.players[1].hand[i]->GetActivationCost (), 4);
				}
				else if (meGame.players[1].hand[i]->GetName() == "Giant Strength") {

					meView.LoadBoardCard( meGame.players[1].hand[i]->GetName(),
						meGame.players[1].hand[i]->GetCost(), 
						"", meGame.players[1].hand[i]->GetDescription(),
						meGame.players[1].hand[i]->GetAttack(), 
						meGame.players[1].hand[i]->GetDefense(), 
						meGame.players[1].hand[i]->GetAbilityCost(), 
						meGame.players[1].hand[i]->GetCharges(), 
						meGame.players[1].hand[i]->GetActivationCost (), 6);
				}
				else if (meGame.players[1].hand[i]->GetType() == "Enchantment") {

					meView.LoadBoardCard( meGame.players[1].hand[i]->GetName(),
						meGame.players[1].hand[i]->GetCost(), 
						"", meGame.players[1].hand[i]->GetDescription(),
						meGame.players[1].hand[i]->GetAttack(), 
						meGame.players[1].hand[i]->GetDefense(), 
						meGame.players[1].hand[i]->GetAbilityCost(), 
						meGame.players[1].hand[i]->GetCharges(), 
						meGame.players[1].hand[i]->GetActivationCost (), 7);
				}
			}
		}

		if (meGame.players[1].DoesHaveRitual()) {

			//Load the ritual
			meView.LoadRitual(meGame.players[1].ritual[0]->GetName(),
						meGame.players[1].ritual[0]->GetCost(),
						meGame.players[1].ritual[0]->GetActivationCost (), 
						meGame.players[1].ritual[0]->GetDescription(), 
						meGame.players[1].ritual[0]->GetCharges());

		}

		meView.LoadPlayer (meGame.GetPlayer2Name(), !player1Turn, 
				meGame.players[1].GetMagic(), meGame.players[1].GetLife(), 1);


		top = meGame.players[1].graveyard.size() - 1;

		if (top >= 0) {

			if (meGame.players[1].graveyard[top]->HasTriggeredAbility () ) {

				meView.LoadGraveyard( meGame.players[1].graveyard[top]->GetName(),
					meGame.players[1].graveyard[top]->GetCost(), 
					"", meGame.players[1].graveyard[top]->GetDescription(),
					meGame.players[1].graveyard[top]->GetAttack(), 
					meGame.players[1].graveyard[top]->GetDefense(), 
					meGame.players[1].graveyard[top]->GetAbilityCost(), 
					meGame.players[1].graveyard[top]->GetCharges(), 
					meGame.players[1].graveyard[top]->GetActivationCost (), 2);
			}
			else if (meGame.players[1].graveyard[top]->HasActivatedAbility () ) {

				meView.LoadGraveyard( meGame.players[1].graveyard[top]->GetName(),
					meGame.players[1].graveyard[top]->GetCost(), 
					"", meGame.players[1].graveyard[top]->GetDescription(),
					meGame.players[1].graveyard[top]->GetAttack(), 
					meGame.players[1].graveyard[top]->GetDefense(), 
					meGame.players[1].graveyard[top]->GetAbilityCost(), 
					meGame.players[1].graveyard[top]->GetCharges(), 
					meGame.players[1].graveyard[top]->GetActivationCost (), 3);
			}
			else if (meGame.players[1].graveyard[top]->IsNormalMinion () ) {

				meView.LoadGraveyard( meGame.players[1].graveyard[top]->GetName(),
					meGame.players[1].graveyard[top]->GetCost(), 
					"", meGame.players[1].graveyard[top]->GetDescription(),
					meGame.players[1].graveyard[top]->GetAttack(), 
					meGame.players[1].graveyard[top]->GetDefense(), 
					meGame.players[1].graveyard[top]->GetAbilityCost(), 
					meGame.players[1].graveyard[top]->GetCharges(), 
					meGame.players[1].graveyard[top]->GetActivationCost (), 1);
			}
		}


		meView.DrawBoard();
		meView.DrawSecondRow();

	}





	meView.DrawError(meGame.players[0].GetError());
	meView.DrawError(meGame.players[1].GetError());

}

