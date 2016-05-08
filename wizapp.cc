/*
	Ethan Han
	Henry Hoang
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
#include "classes.cc"
#include <stdlib.h>

class Game {
	// MARK: Members
	// grid
	const unsigned int rows;
	const unsigned int cols;
	vector< vector<Cell *> > grid;
	// characters
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
			e = (max / dist + 4) / 8; 
		}
		return e;
	}
	// set a cell's neighbours
	void generateNeighbours(Cell *cell, int r, int c) {
	    cell->addNeighbour(grid[r - 1][c - 1], 0);
	    cell->addNeighbour(grid[r - 1][c], 1);
	    cell->addNeighbour(grid[r - 1][c + 1], 2);
	    cell->addNeighbour(grid[r][c - 1], 3);
	    cell->addNeighbour(grid[r][c + 1], 4);
	    cell->addNeighbour(grid[r + 1][c - 1], 5);
	    cell->addNeighbour(grid[r + 1][c], 6);
	    cell->addNeighbour(grid[r + 1][c + 1], 7);
	}

	// MARK: Member routines
public:
	// Constructor
	Game(unsigned int rows, unsigned int cols) : rows(rows), cols(cols) {
		grid.resize(rows);
		for (unsigned int r = 0; r < rows; r++) {
			grid[r].resize(cols);
			for (unsigned int c = 0; c < cols; c++) {
				if (r == 10 && c == 5) {
					grid[r][c] = new Cell(r, c, 'v');
				} else if (r == 0 || r == rows - 1) {
					grid[r][c] = new Cell(r, c, '-');
				} else if (c == 0 || c == cols - 1) {
					grid[r][c] = new Cell(r, c, '|');
				} else {
					grid[r][c] = new Cell(r, c, energy(r, c));
				}
			}
		}
		// set neighbours
		for (unsigned int r = 1; r < rows - 1; r++) {
			for (unsigned int c = 1; c < cols - 1; c++) {
				generateNeighbours(grid[r][c], r, c);
			}
		}
		
		int rowCoords[] = {9, 5, 1, 5};
		int colCoords[] = {5, 1, 5, 9};
		// player wizard
		player = new Wizard(grid[rowCoords[0]][colCoords[0]], true);
		grid[rowCoords[0]][colCoords[0]]->setContent(player);

		// generate 3 wizards
		for (int i = 1; i < 4; i++) {
			Wizard *wiz = new Wizard(grid[rowCoords[i]][colCoords[i]], false);
			grid[rowCoords[i]][colCoords[i]]->setContent(wiz);
			monsters.push_back(wiz);
		}
		// generate 9 enemies
		for (int i = 0; i < 9; i++) {
			while (true) {
				unsigned int rr = rand() % 8 + 1;
				unsigned int rc = rand() % 8 + 1;
				if (grid[rr][rc]->hasContent() == false) {
					Minotaur *mino = new Minotaur(grid[rr][rc]);
					grid[rr][rc]->setContent(mino);
					monsters.push_back(mino);
					break;
				}
			}
		}
	}
	// Destructor
	~Game() {
		for (unsigned int r = 0; r < rows; r++) {
			for (unsigned int c = 0; c < cols; c++) {
				delete grid[r][c];
			}
		}
		int size = monsters.size();
		for (int i = 0; i < size; i++) {
			delete monsters[i];
		}
		delete player;
	}
	void executeTurn(string action) {
		if (action == "gather") {
			player->gather();
		} else {
			player->move(action);
		}
		int size = monsters.size();
		for (int i = 0; i < size; i++) {
			monsters[i]->tick();
			if (gameLost()) {
				return;
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
		cout << "You have " << player->energy() << " energy." << endl;
		cout << "You have " << player->gethp() << " health." << endl;
	}
	// check if game is lost (player dead)
	bool gameLost() {
		return player->gethp() <= 0;
	}
};

int main() {
	cout << "Wizard's Apprentice 1.0.0" << endl;
	unsigned int r = 11;
	unsigned int c = 11;
	Game *game = new Game(r, c);
	game->printGame();

	string action;
	while (true) {
		cout << "What will you do?" << endl;
		cin >> action;
		game->executeTurn(action);
		game->printGame();

		if (game->gameLost()) {
			cout << "You have died." << endl;
			break;
		}
	}
}
