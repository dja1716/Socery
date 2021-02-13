#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

#include "View.h"
#include "Game.h"
#include "Player.h"

using namespace std;

class Controller {



	public:

	void Draw (const Game &meGame, View &meView);

};



#endif

