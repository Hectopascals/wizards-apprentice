#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i) {
            for (unsigned int j = 0; j < height; ++j) {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
        }
        return true;
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};


int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(540, 540), "Wizard's Apprentice");
    window.setPosition(sf::Vector2i(700, 200));

    // define the level with an array of tile indices
    const int level[] = {
        0, 1, 2, 3, 0, 0, 1, 1, 1,
        1, 1, 2, 1, 3, 0, 1, 2, 3,
        0, 0, 3, 2, 1, 2, 2, 1, 3,
        0, 0, 2, 1, 1, 0, 0, 1, 1,
        2, 2, 2, 2, 2, 1, 1, 3, 0,
        0, 2, 1, 3, 3, 3, 0, 0, 1,
        0, 1, 0, 0, 1, 2, 1, 3, 2,
        2, 1, 1, 0, 0, 3, 3, 3, 0,
        3, 2, 1, 0, 0, 1, 2, 1, 1 };

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("./Images/grass.png", sf::Vector2u(60, 60), level, 9, 9))
        return -1;

    // run the main loop
    while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Clicked closed window
            if (event.type == sf::Event::Closed)
                window.close();

            // Just to check for width/height resized
            if (event.type == sf::Event::Resized) {
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;
            }

            // Key Press
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    std::cout << "ESC was pressed" << std::endl;
                    window.close();
                    // 1 if pressed with ESC, else 0
                    //std::cout << "ctrl:" << event.key.control << std::endl;
                } else if (event.key.code == sf::Keyboard::Left) {
                    std::cout << "Left was pressed" << endl;
                } else if (event.key.code == sf::Keyboard::Right) {
                    std::cout << "Right was pressed" << endl;
                } else if (event.key.code == sf::Keyboard::Up) {
                    std::cout << "Up was pressed" << endl;
                } else if (event.key.code == sf::Keyboard::Down) {
                    std::cout << "Down was pressed" << endl;
                } else if (event.key.code == sf::Keyboard::Q) {
                    std::cout << "Q was pressed" << endl;
                }
            }

        }

        // draw the map
        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}
