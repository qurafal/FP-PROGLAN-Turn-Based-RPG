#include "include/base.h"
#include <SFML/Graphics.hpp>
#include "include/others.h"
#include "Game/game.h"



int main() {
    //Init Game
    Game game;


    while (game.isRunning()) {
        //Update
        game.update();

        //Render
        game.render();








        // sf::Event event;
        // while (window.pollEvent(event)) {
        //     if (manager.getState())
        //         manager.getState()->handleEvent(window, event);
        // }
        // if (manager.getState())
        //     manager.getState()->update(window);

        // window.clear();
        // if (manager.getState())
        //     manager.getState()->render(window);
        // window.display();
    }
    // // Create party
   

    return 0;
}

   



