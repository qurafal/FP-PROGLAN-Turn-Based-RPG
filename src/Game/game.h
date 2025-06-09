#pragma once

#include "../include/base.h"
#include "../include/others.h"



/* Game Engine anjay*/

class Game {
    private:    
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event ev;

        Party party; 
        std::unique_ptr<Floor> floor; 
        int currentFloor = 1; 

        //state
        State *state;


        void initWindow();
        void initVariables();

public:
// Constructor and Destructor
    Game();
    virtual ~Game();

    //Accessors idk what that means
    const bool isRunning() const;

    //Functions
    void update();
    void updateEvents();
    void render();
  
    //Simple functions
    Party& getParty() { return party; }
    void setState(State* newState) {
        std::cout << "[DEBUG] Deleting old state: " << (state ? state->getName() : "null") << std::endl;
        delete state; 
        state = newState; 
        std::cout << "[DEBUG] Setting mew state set: " << (state ? state->getName() : "null") << std::endl;
    }
    int getCurrentFloor() const {
        return currentFloor;
    }
    void setCurrentFloor(int floorNumber) {
        currentFloor = floorNumber;
    }
};