#ifndef CHARACTER_CC
#define CHARACTER_CC

#include "cell.cc"

class Cell;

class Character {
	// MARK: Members
	int hp;
	int att;
	int def;
	char char_display;
	Cell *location;
	// MARK: Member routines
public:
	// Constructor
	Character(Cell *loc, int hp, int att, int def, int d)
		: location(loc), hp(hp), att(att), def(def), char_display(d) {

	}
	// Destructor
	~Character() {}

	char display() { // Getter
		return char_display;
	}
	void setLocation(Cell *location) { // Setter
		this->location = location == 0 ? 0 : location;
	}
	Cell * getLocation() { // Getter
		return location;
	}

	// Virtuals
	virtual void attack() = 0;
	virtual void move() = 0;
};
#endif
