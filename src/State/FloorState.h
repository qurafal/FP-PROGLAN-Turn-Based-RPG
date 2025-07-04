#pragma once

#include "SecondMenu.h"
#include "../Floor/floor.h"

class FloorState : public State {
private:
    Game *game; 
    Floor floor; 

    friend class BattleState; 
    friend class EventState;
    
    
    sf::Font font;
    sf::Text title;
    
    
    int selectedStep = 0; 
    int selectedBranch = 0;
    int maxVisitedStep = -1; 



    
    public:
    FloorState(Game *game, int floor);

    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

    std::string getName() const override;
};