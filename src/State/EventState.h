#pragma once
#include <random>
#include "state.h"
#include "../Battle/party.h"

class Game;       // Forward declaration
class FloorState; // Forward declaration

class EventState : public State
{
private:
    Game *game;             
    Party *party;           
    FloorState *floorState; 

    sf::Font font;
    sf::Text title;

    // Event-specific variables
    sf::Text titleText;
    sf::Text descriptionText; 
    sf::Text choiceTexts[3];

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Event System
    struct Choice
    {
        std::string text;
        std::string result;
        bool isUpgrade;
        int upgradeType; // 0=HP, 1=ATK, 2=DEF, 3=MAG, 4=RES
        int upgradeAmount;
        int targetCharacter; // -1 = all party, 0-3 = specific character
    };

    struct EventScenario
    {
        std::string title;
        std::string description;
        std::vector<Choice> choices;
        std::string backgroundPath;
    };

    std::vector<EventScenario> scenarios;
    int currentScenario;
    int selectedChoice;
    bool showingResult;
    std::string resultText;

    // RNG
    std::random_device rd;
    std::mt19937 gen;

    void initializeScenarios();
    void selectRandomScenario();
    void executeChoice(const Choice &choice);
    void applyUpgrade(int charIndex, int upgradeType, int amount);

public:
    EventState(Game *game, FloorState *floorState);

    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

    std::string getName() const override
    {
        return "EventState";
    }
};