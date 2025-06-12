#pragma once
#include "state.h"

class Game; // Forward declaration

class MenuState : public State
{
private:
    Game *game;

    sf::Font font;
    sf::Text title;
    int selectedOption = 0;
    std::string options[2] = {"Begin Exploration", "Exit"};
    

public:
    MenuState(Game *game);

    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;

    void update() override;

    void render(sf::RenderWindow &window) override;

    std::string getName() const override
    {
        return "MenuState";
    }
};