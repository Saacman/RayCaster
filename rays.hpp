#ifndef RAYS_HPP
#define RAYS_HPP

#include <SFML/Graphics.hpp>

class Rays : public sf::Drawable
{
public:
    Rays();
    Rays(int nrays);
    ~Rays();
    void computeRays(sf::Vector2f position, float angle, const int* map);
private:
    virtual void draw(sf::RenderTarget & target, sf:: RenderStates states) const;
    sf::VertexArray m_vertices;
    int norays;
};

#endif