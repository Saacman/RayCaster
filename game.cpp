#include "game.hpp"

// Default Constructor
Game::Game() : window(nullptr) { }

// Constructor
Game::Game(int width, int height) : Game() {
    videoMode.width = width;
    videoMode.height = height;
    window = new sf::RenderWindow(videoMode, "RayCaster");

    player.setRadius(4.f);
    player.setFillColor(sf::Color::Yellow);
    player.setPosition(sf::Vector2f(100.f, 100.f));

    //player = sf::Vertex(sf::Vector2f(10.f, 50.f), sf::Color::Black);
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
    
}
void Game::render() {
    window->clear(sf::Color(220, 220, 220, 255));

    // Draw Game Objects
    //window->draw(&player, 1, sf::Points);
    window->draw(player);
    window->display();
}

// Accessors
const bool Game::isRunning() const {
    return window->isOpen();
}