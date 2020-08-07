#include <iostream>
#include "game.hpp"
#define W 1024
#define H 512
int main()
{
    // Init game object
    Game game(W, H);

    // run the program as long as the game keeps running
    while (game.isRunning())
    {
        // Update
        game.update();
        // Render
        game.render();
        
    }

    return 0;
}