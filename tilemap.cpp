#include "tilemap.hpp"

TileMap::TileMap() {}

bool TileMap::load(sf::Vector2u tileSize, const int* tiles, int width, int height) {
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4); // 4 verteces per Quad

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++) {

            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // Set the position of each quad's points
            quad[0].position = sf::Vector2f(i * tileSize.x       +1, j * tileSize.y        +1);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x -1, j * tileSize.y        +1);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x -1, (j + 1) * tileSize.y  -1);
            quad[3].position = sf::Vector2f(i * tileSize.x       +1, (j + 1) * tileSize.y  -1);
            
            // Set the color of each Quad's points
            sf::Color color = tiles[i + j * width] ? sf::Color::Black : sf::Color::White;
            quad[0].color = color;
            quad[1].color = color;
            quad[2].color = color;
            quad[3].color = color;
        }
    }
    return true;
}
TileMap::~TileMap() {}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
        // draw the vertex array
        target.draw(m_vertices, states);
    }