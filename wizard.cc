#ifndef WIZARD_CC
#define WIZARD_CC

#include "character.cc"
#include "cell.cc"

class Wizard : public Character {
	// MARK: Members
	// MARK: Member routines	
public:
	// Constructor
	Wizard(Cell *loc)
		: Character(loc, 100, 100, 100, 'W') {

	}
	// Destructor
	~Wizard() {}
	// Virtuals
	void attack() { int x = 0; x++; }
	void move() {}
};
#endif
