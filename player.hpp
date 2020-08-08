#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "rays.hpp"

class Player : public sf::Drawable
{
public:
    Player();
    ~Player();

    // Functions
    void update(float dTime);
    // Accessors
    sf::Vector2f getPosition();
    // Modifiers
    void setPosition(sf::Vector2f pos);
    
    const int* map;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::CircleShape body;
    sf::Vector2f position;
    sf::Vector3f angularPos; // dX, dY, dAlpha
    sf::VertexArray direction;
    float angle;
    float speed;
    float angularvel;
    Rays rays;
};



#endif