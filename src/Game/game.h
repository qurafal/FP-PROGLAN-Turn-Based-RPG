#pragma once

#include "../include/base.h"
#include "../include/others.h"



/* Game Engine anjay*/

class Game {
    private:    
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event ev;
        sf::Music music; 

        Party party; 
        std::unique_ptr<Floor> floor; 
        int currentFloor = 1; 

        //state
        State *state;


        void initWindow();
        void initVariables();
        void initMusic();

public:
// Constructor and Destructor
    Game();
    virtual ~Game();

    
    
    //Functions
    void update();
    void updateEvents();
    void render();
    
    //Simple functions
    const bool isRunning() const;
    Party& getParty() { return party; }
    void setState(State* newState) {
        std::cout << "[DEBUG] Deleting old state: " << (state ? state->getName() : "null") << std::endl;
        delete state; 
        state = newState; 
        std::cout << "[DEBUG] Setting mew state set: " << (state ? state->getName() : "null") << std::endl;
    }
    void tempSetState(State* newState) {
        state = newState; 
    }
    int getCurrentFloor() const {
        return currentFloor;
    }
    void setCurrentFloor(int floorNumber) {
        currentFloor = floorNumber;
    }
};