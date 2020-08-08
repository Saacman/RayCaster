#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable
{
public:
    TileMap();
    ~TileMap();
    bool load(sf::Vector2u tileSize, const int* tiles, int width, int height);
private:
    sf::VertexArray m_vertices;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif