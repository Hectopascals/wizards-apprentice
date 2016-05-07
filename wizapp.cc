/*
	Ethan Han
	Henry Hoang
	Shelumiel Mordido
	TOJAM 2016
*/

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include "game.cc"
//#include "character.cc"

int main() {
	cout << "Wizard's Apprentice 1.0.0" << endl;
	Game *game = new Game(30, 30);
	game->printGame();
}
