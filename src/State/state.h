#pragma once
#include "../include/base.h"

class Game; //forward declaration

class State{
public:
    virtual ~State() = default;

    // Pure virtual functions to be implemented by derived states
    virtual void handleEvent(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void update(Game& game) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    // Optional: You can add a method to check if the state is active
    virtual bool isActive() const { return true; }
    // Optional: You can add a method to get the name of the state
    virtual std::string getName() const = 0;
};

