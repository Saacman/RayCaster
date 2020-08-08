#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

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

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::CircleShape body;
    sf::Vector2f position;
    float speed;
    

};



#endif