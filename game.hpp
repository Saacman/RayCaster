#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

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

private:
    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode videoMode;
    sf::CircleShape player;
    //sf::Vertex player;

};

#endif