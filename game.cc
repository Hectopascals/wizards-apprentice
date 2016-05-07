#ifndef GAME_CC
#define GAME_CC
// hello worldzz
#include "cell.cc"
#include "wizard.cc"
//#include <vector>
//using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <math.h>

class Game {
	// MARK: Members
	// grid
	const unsigned int rows;
	const unsigned int cols;
	Cell **grid;
	// calculate cell energy
	int energy(unsigned int r, unsigned int c) {
		unsigned int dr = (rows / 2) - r;
		unsigned int dc = (cols / 2) - c;
		unsigned int dist = dr * dr + dc * dc;
		unsigned int max = rows * rows + cols * cols; // max (radius) = 60 * 60 + 15 * 15 = 3825
		int e = 0;
		if (dist == 0) {
			e = 9;
		} else {
			e = sqrt(max) / (sqrt(dist) + 9); 
		}
		return pow(e - 1, 2);
	}

	// MARK: Member routines
public:
	// Constructor
	Game(unsigned int rows, unsigned int cols) : rows(rows), cols(cols) {
		grid = new Cell*[rows];
		for (unsigned int r = 0; r < rows; r++) {
			grid[r] = new Cell[cols];
			for (unsigned int c = 0; c < cols; c++) {
				grid[r][c].setCoords(r, c);
				grid[r][c].setEnergy(energy(r, c));
			}
		}
		// generate 3 wizards
		for (int i = 0; i < 3; i++) {
			Wizard *wiz = new Wizard(grid[i * 7][i * 3]);
		}
		// generate 9 enemies
	}
	// Destructor
	~Game() {
		for (unsigned int r = 0; r < rows; r++) {
			delete [] grid[r];
		}
		delete [] grid;
	}
	// print floor/game
	void printGame() {
		for (unsigned int r = 0; r < rows; r++) {
			for (unsigned int c = 0; c < cols; c++) {
				cout << grid[r][c].occupierDisplay();
			}
			cout << endl;
		}
	}
};
#endif
