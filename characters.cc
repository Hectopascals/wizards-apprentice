#ifndef CHARACTER_CC
#define CHARACTER_CC

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
	void attack() {}
	void move() {}
};

class Minotaur : public Character {
public:
	// Constructor
	Minotaur(Cell *loc)
		: Character(loc, 150, 60, 50, 'M') {

	}
	// Destructor
	~Minotaur() {}
	// Virtuals
	void attack() {}
	void move() {}
};

#endif
