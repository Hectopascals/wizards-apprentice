#ifndef CELL_CC
#define CELL_CC

#include "character.cc"

class Character;

class Cell {
	// MARK: Members
	// cell info
	unsigned int row;
	unsigned int col;
	// energy--power per second
	int energy;
	// display--visual
	char char_display;
	// Character that is standing on the cell
	Character *content;
	// MARK: Member routines
public:
	// Constructor
	Cell() {}
	// Destructor
	~Cell() {}
	char display() { // Getter
		return content == 0 ? char_display : content->display();
	}
	void setEnergy(int e) { // Setter
		energy = e;
		char_display = '0' + energy;
	}
	void setCoords(unsigned int r, unsigned int c) {  // Setter
		row = r;
		col = c;
	}
};
#endif
