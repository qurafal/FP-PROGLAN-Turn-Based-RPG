#pragma once
#include "MenuState.h"

class FloorState; // Forward declaration

class SecondMenu : public State
{
private:
    Game *game; 
    FloorState *floorState; // Biar bisa balik ke FloorState


    sf::Font font;
    sf::Text title;
    int selectedOption = 0;
    std::string options[3] = {"Enter Node", "Party Select", "Back"};

    sf::Texture texture;
    sf::Sprite backgroundSprite;

public:
    SecondMenu(Game *game, FloorState *floorState = nullptr);

    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;

    void update() override
    {
        
    }

    void render(sf::RenderWindow &window) override;

    std::string getName() const override
    {
        return "SecondMenu";
    }
};