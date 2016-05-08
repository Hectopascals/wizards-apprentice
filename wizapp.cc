/*
	Ethan Han
	Henry Hoang
	Shelumiel Mordido
	TOJAM 2016
*/

#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
#include <math.h>
#include "cell.cc"
#include "characters.cc"

using std::string;

class Game {
	// MARK: Members
	// grid
	const unsigned int rows;
	const unsigned int cols;
	vector< vector<Cell *> > grid;
	// characters
	vector<Wizard *> wizards;
	vector<Character *> monsters;
	Wizard * player;
	// calculate cell energy
	int energy(unsigned int r, unsigned int c) {
		unsigned int dr = (rows / 2) - r;
		unsigned int dc = (cols / 2) - c;
		unsigned int dist = dr * dr + dc * dc;
		unsigned int max = (rows / 2) * (rows / 2) + (cols / 2) * (cols / 2); // max (radius) = 8 * 8 + 8 * 8 = 128
		int e = 0;
		if (dist == 0) {
			e = 9;
		} else {
			e = (max / dist) / 3; 
		}
		return e;
	}

	// MARK: Member routines
public:
	// Constructor
	Game(unsigned int rows, unsigned int cols) : rows(rows), cols(cols) {
		grid.resize(rows);
		for (unsigned int r = 0; r < rows; r++) {
			grid[r].resize(cols);
			for (unsigned int c = 0; c < cols; c++) {
				grid[r][c] = new Cell(r, c, energy(r, c));
			}
		}
		
		int rowCoords[] = {8, 4, 0, 4};
		int colCoords[] = {4, 0, 4, 8};
		// player wizard
		player = new Wizard(grid[rowCoords[0]][colCoords[0]]);
		grid[rowCoords[0]][colCoords[0]]->setContent(player);
		wizards.push_back(player);
		// generate 3 wizards
		for (int i = 1; i < 4; i++) {
			Wizard *wiz = new Wizard(grid[rowCoords[i]][colCoords[i]]);
			grid[rowCoords[i]][colCoords[i]]->setContent(wiz);
			wizards.push_back(wiz);
		}
		// generate 9 enemies
		/*for (int i = 0; i < 9; i++) {
			Minotaur *mino = new Minotaur(grid[4][i]);
			grid[4][i]->setContent(mino);
			monsters.push_back(mino);
		}*/
	}
	// Destructor
	~Game() {
		for (unsigned int r = 0; r < rows; r++) {
			for (unsigned int c = 0; c < cols; c++) {
				delete grid[r][c];
			}
		}
	}
	// print floor/game
	void printGame() {
		for (unsigned int r = 0; r < rows; r++) {
			for (unsigned int c = 0; c < cols; c++) {
				cout << grid[r][c]->occupierDisplay();
			}
			cout << endl;
		}
	}
};

int main() {
	cout << "Wizard's Apprentice 1.0.0" << endl;
	Game *game = new Game(9, 9);
	game->printGame();

	// parse turns
	/*string turn;
	while (true) {
		cin >> turn;

	}*/
}
