#include "player.hpp"

// Default Constructor
Player::Player() : speed(150.f) {
    body.setRadius(4.f);
    body.setFillColor(sf::Color::Magenta);
    body.setOrigin(body.getRadius(), body.getRadius());
    position.x = 100.f;
    position.y = 200.f;
    body.setPosition(position);
}


Player::~Player() {}
// TODO: remove magic numbers
// Functions
void Player::update(float dTime) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        position.y -= position.y > 4 ? speed * dTime : 0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        position.x -= position.x > 4 ? speed * dTime : 0; 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        position.y += position.y < 508 ? speed * dTime : 0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        position.x += position.x < 508 ? speed * dTime : 0;
    body.setPosition(position);
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(body);
}
// Modifiers
void Player::setPosition(sf::Vector2f pos) {
    position = pos;
}
// Accessors
sf::Vector2f Player::getPosition() {
    return position;
}