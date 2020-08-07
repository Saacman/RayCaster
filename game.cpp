#include "game.hpp"

// Default Constructor
Game::Game() : window(nullptr) { }

// Constructor
Game::Game(int width, int height) : Game() {
    videoMode.width = width;
    videoMode.height = height;
    window = new sf::RenderWindow(videoMode, "RayCaster");

    // Corregir el constructor del jugador
    dTime = clock.restart().asSeconds();
}

Game::~Game() {
    delete window;
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
    window->clear(sf::Color(220, 220, 220, 255));

    // Draw Game Objects
    
    player.draw(*window, states);
    window->display();
}

// Accessors
const bool Game::isRunning() const {
    return window->isOpen();
}

void Game::getTime() {
    dTime = clock.restart().asSeconds();
}