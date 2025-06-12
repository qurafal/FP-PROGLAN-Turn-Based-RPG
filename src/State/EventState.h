#pragma once

#include "state.h"
#include "../Battle/party.h"

class Game; // Forward declaration
class FloorState; // Forward declaration

class EventState : public State {
private:
    Game *game; // Pointer to the game instance
    Party *party; // Pointer to the party instance
    FloorState *floorState; // Pointer to the floor state for returning after event

    sf::Font font;
    sf::Text title;

    // Event-specific variables
    std::string eventDescription; // Description of the event
    std::vector<std::string> choices; // Choices available in the event
    int selectedChoice = 0; // Index of the currently selected choice


    std::vector<std::string> eventPages;
    int currentPage = 0; // Current page of the event description' 
    
    std::vector<std::string> eventResults; 
    int resultIndex = 0; 

public:
    EventState(Game *game, FloorState *floorState);

    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

    std::string getName() const override {
        return "EventState";
    }
};