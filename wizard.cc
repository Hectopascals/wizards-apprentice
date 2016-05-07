#ifndef WIZARD_CC
#define WIZARD_CC

#include "character.cc"
#include "cell.cc"

class Wizard : public Character {
	// MARK: Members
	// MARK: Member routines
	// Constructor
	Wizard(Cell *loc)
		: Character(loc, 100, 100, 100, 'W') {

	}
	// Destructor
	~Wizard() {}
	// Virtuals
	void attack() {}
	void move() {}
};
#endif
