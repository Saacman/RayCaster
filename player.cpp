#include <math.h>
#include "player.hpp"
#define PI 3.1415926536

// Default Constructor
Player::Player() : position(100.f, 200.f), angle(0.0), speed(120.f), angularvel(11.f), rays(1) {
    body.setRadius(4.f);
    body.setFillColor(sf::Color::Magenta);
    body.setOrigin(body.getRadius(), body.getRadius());
    body.setPosition(position);
    // From here it could be a new class
    direction.setPrimitiveType(sf::Lines);
    direction.resize(2);
    direction[0].position = position;
    direction[1].position = position + sf::Vector2f(25.f * cos(angle), 25.f * sin(angle));
    direction[0].color = sf::Color::Green;
    direction[1].color = sf::Color::Green;
}


Player::~Player() {
}
// TODO: remove magic numbers
// Functions
void Player::update(float dTime) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        position.x += speed * dTime * cos(angle);
        position.y += speed * dTime * sin(angle);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        angle -= angularvel * dTime;
        if(angle < 0) angle += 2 * PI;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        position.x -= speed * dTime * cos(angle);
        position.y -= speed * dTime * sin(angle);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        angle += angularvel * dTime;
        if(angle > 2 * PI) angle -= 2 * PI;
    }
    // A method that takes the position and angular position to upate the direction
    direction[0].position = position;
    direction[1].position = position + sf::Vector2f(25.f * cos(angle), 25.f * sin(angle));
    rays.computeRays(position, angle, map);
    body.setPosition(position);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rays);
    target.draw(direction);
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