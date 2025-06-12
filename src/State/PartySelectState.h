#pragma once
#include "MenuState.h"

class PartySelectState : public State {
private:
    Game *game; // Pointer to the game instance

    sf::Font font;
    sf::Text title;
    int selectedOption = 0;
    std::string characters[4] = {"Arthesa", "Ahmed", "Hamilla", "Perkia"};
public:
    PartySelectState(Game *game);


    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;

    void update() override;

    void render(sf::RenderWindow &window) override;

    std::string getName() const override;
};
