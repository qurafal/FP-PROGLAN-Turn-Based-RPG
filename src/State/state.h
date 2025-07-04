#pragma once

#include "../include/base.h"

class Game; //forward declaration

class State{
public:
    virtual ~State() = default;

   
    virtual void handleEvent(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    
    virtual bool isActive() const { return true; }
    
    virtual std::string getName() const { return "Abstract"; }
};

