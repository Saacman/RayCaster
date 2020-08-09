#include "game.hpp"

// Default Constructor
Game::Game() : window(nullptr){ }

// Constructor
Game::Game(int width, int height) : Game() {
    
    settings.antialiasingLevel = 8;
    videoMode.width = width;
    videoMode.height = height;
    window = new sf::RenderWindow(videoMode, "RayCaster", sf::Style::Default, settings);

    // Corregir el constructor del jugador
    dTime = clock.restart().asSeconds();

    level = new int[8 * 8]{
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 1, 1, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 1, 1, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1
    };
    map.load(sf::Vector2u(64,64), level, 8, 8);
    player.map = level;
}

Game::~Game() {
    delete window;
    delete level;
}
//Functions
void Game::update()
{
    // Poll Events :: Might move to another function?
    while (window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window->close();
    }
    player.update(dTime);
}

void Game::render() {
    window->clear(sf::Color(0 ,0 , 0, 255));//sf::Color(220, 220, 220, 255));
    
    // Draw Game Objects
    window->draw(map);
    window->draw(player);
    window->display();
}

// Accessors
const bool Game::isRunning() const {
    return window->isOpen();
}

void Game::getTime() {
    dTime = clock.restart().asSeconds();
}