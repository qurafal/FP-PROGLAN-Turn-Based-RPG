#pragma once
#include "../include/base.h"

class GameState {
public:
    virtual ~GameState() = default;
    virtual void handleEvent(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void update(sf::RenderWindow& window) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    
};