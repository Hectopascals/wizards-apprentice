#include <string>
using std::string;

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
	// Neighbour cells
	Cell *neighbours[8];
	// MARK: Member routines
	public:
		// Constructor
		Cell(unsigned int r, unsigned int c, int e) 
			: row(r), col(c), energy(e) {
			content = 0;
			char_display = '0' + energy;
		}
		Cell(unsigned int r, unsigned int c, char d)
			: row(r), col(c) {
			energy = 0;
			content = 0;
			char_display = d;
		}
		// Destructor
		~Cell() {}

		char display() { // Getter
			return char_display;
		}
		char occupierDisplay();
		void setEnergy(int e) { // Setter
			energy = e;
			char_display = '0' + energy;
		}
		int getEnergy() {
			return energy;
		}
		void setCoords(unsigned int r, unsigned int c) {  // Setter
			row = r;
			col = c;
		}
		void setContent(Character *c) { // Setter
			content = c;
		}
		Character * getContent() { // Getter
			return content;
		}
		bool hasContent() { // Flag Getter
			return content == 0 ? false : true;
		}
		void addNeighbour(Cell *n, int index) { // Setter/Added
			neighbours[index] = n;
		}
		Cell * getNeighbour(int index) { // Getter
			return neighbours[index];
		}
		Cell * getNeighbour(string dir) { // Getter
			int d = (dir == "nw") ? 0 : -1;
			d = (dir == "no") ? 1 : d;
			d = (dir == "ne") ? 2 : d;
			d = (dir == "we") ? 3 : d;
			d = (dir == "ea") ? 4 : d;
			d = (dir == "sw") ? 5 : d;
			d = (dir == "so") ? 6 : d;
			d = (dir == "se") ? 7 : d;
			return getNeighbour(d);
		}
		bool isWall() {
			return char_display == '|' || char_display == '-';
		}
};

class Character {
	// MARK: Members
	protected:
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
		string getDirection(int d) {
			if (d == 0) {
				return "nw";
			} else if (d == 1) {
				return "no";
			} else if (d == 2) {
				return "ne";
			} else if (d == 3) {
				return "we";
			} else if (d == 4) {
				return "ea";
			} else if (d == 5) {
				return "sw";
			} else if (d == 6) {
				return "so";
			} else if (d == 7) {
				return "se";
			}
			return "nothing";
		}
		// Virtuals
		virtual void tick() = 0;
		virtual void attack(string dir) = 0;
		virtual void move(string dir) = 0;
};

class Wizard : public Character {
	// MARK: Members
	int energyGained;
	// MARK: Member routines	
	public:
		// Constructor
		Wizard(Cell *loc, bool isPlayer)
			: Character(loc, 100, 100, 100, 'W') {
			energyGained = 0;
			if (isPlayer) char_display = 'P';
		}
		// Destructor
		~Wizard() {}
		void gather() { // Setter
			energyGained += location->getEnergy();
		}
		// Virtuals
		void tick() {
			cout << "Wizard ticking." << endl;
			
		}
		void attack(string dir) {}
		void move(string dir) {
			if (location->getNeighbour(dir)->hasContent() ||
					location->getNeighbour(dir)->isWall()) {
				cout << "Cannot move there." << endl;
			} else {
				Cell * newLocation = location->getNeighbour(dir);
				newLocation->setContent(this);
				location->setContent(0);
				location = newLocation;
			}
		}
		int energy() {
			return energyGained;
		}
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
		void tick() {
			for (int i = 0; i < 8; i++) {
				Cell *n = location->getNeighbour(i);
				if (n->isWall() || !n->hasContent()) {
					continue;
				}
				if (n->getContent()->display() == 'P') {
					attack(getDirection(i));
					return;
				}
			}
			int d;
			Cell *n;
			while (true) {
				d = rand() % 8; // 0-7
				cout << d << endl;
				n = location->getNeighbour(d);
				if (n->hasContent() || n->isWall()) {
					continue;
				} else {
					break;
				}
			}
			move(getDirection(d));
		}
		void attack(string dir) {
			cout << "Minotaur attacking." << endl;
		}
		void move(string dir) {
			cout << "Minotaur moving." << endl;
			cout << dir << endl;
			Cell * newLocation = location->getNeighbour(dir);
			newLocation->setContent(this);
			location->setContent(0);
			location = newLocation;
		}
};

char Cell::occupierDisplay() { // Getter
	return content == 0 ? char_display : content->display();
}
