#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using std::cout;
using std::endl;
using std::cerr;


int main() {
	std::ifstream openfile("layout.txt");
	sf::Texture tileTexture;
	sf::Sprite tiles;

	sf::Vector2i map[20][20];
	sf::Vector2i loadCounter = sf::Vector2i(0, 0);

	if (openfile.is_open()) {
		// get tile picture file name
		std::string tileLoc;
		openfile >> tileLoc;
		tileTexture.loadFromFile(tileLoc);
		tiles.setTexture(tileTexture);

		while(!openfile.eof()) {
			//cout << loadCounter.x << " " << loadCounter.y << endl;
			std::string str;
			openfile >> str;
			char x = str[0];
			char y = str[2]; // read the number after comma
			if (!isdigit(x) || !isdigit(y)) { // if any not a number, dont draw any tile
				// load map coord with this vector, will increment loadcounter
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
			} else {
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');
			}
			if (openfile.peek() == '\n') { // if newline, reset x, increment y by 1
				loadCounter.x = 0;
				loadCounter.y++;
			} else { // keep going cus not newline
				loadCounter.x++;
			}
		}
		loadCounter.x = loadCounter.y;
	}

	sf::RenderWindow Window(sf::VideoMode(650, 650, 50), "Loading maps");
	while (Window.isOpen()) {
		sf::Event event;
		while(Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                Window.close();
		}
		//Window.clear(sf::Color(0, 240, 255));
		Window.clear(sf::Color::White);

		for (int i = 0; i < loadCounter.x; i++) {
			for (int j = 0; j < loadCounter.y; j++) {
				if (map[i][j].x != -1 && map[i][j].y != -1) {
					tiles.setPosition(i * 50, j * 50); // cus each tile is 32 pixels (w & h)
					tiles.setTextureRect(sf::IntRect(map[i][j].x * 50, map[i][j].y * 50, 50, 50)); //wxh 32
					Window.draw(tiles);
				}
			}
		}
		Window.display();
	}

}
