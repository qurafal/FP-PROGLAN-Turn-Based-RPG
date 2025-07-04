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
    }
    
   

    return 0;
}

   



