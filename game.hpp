#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "player.hpp"

class Game
{
public:
    Game();
    Game(int width, int height);
    ~Game();

    // Functions
    void update();
    void render();
    // Accessors
    const bool isRunning() const;
    void getTime();

private:
    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode videoMode;
    sf::RenderStates states;
    sf::Clock clock;
    float dTime;
    Player player;


};

#endif