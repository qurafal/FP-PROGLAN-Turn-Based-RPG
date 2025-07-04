#pragma once

#include "state.h"
#include "../Battle/party.h"
#include "../Battle/enemy_group.h"

class Game;
class FloorState;

class BattleState : public State
{
private:
    Game *game;
    Party *party; // Pointer biar stat nya tetep konsisten
    EnemyGroup *enemies;

    FloorState *floorState; // Pointer biar gak kerandom lagi floornya

    sf::Font font;
    sf::Text title;

    // BATTLE system variables
    enum Phase
    {
        PLAYER_SELECT,
        ACTION_SELECT,
        TARGET_SELECT,
        ENEMY_TURN,
        RESOLVE,
        END
    };
    Phase phase = PLAYER_SELECT;

    int selectedParty = 0;
    int selectedEnemy = 0;
    bool playerActionChosen = false;
    // bool attackChosen = true; 

    std::vector<std::string> actionList = {"Attack", "Skill 1", "Skill 2", "Skill 3"};
    int selectedAction = 0;

    int globalAP = 6; 

    int turn = 0;

    /*ANIMATION*/

    // Background and UI sprites
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Character sprites
    sf::Texture characterTexture[4];
    sf::Sprite characterSprites[4]; // For up to 4 char

    // Enemy sprites
    sf::Texture enemyTexture[3];
    sf::Sprite enemySprites[3]; // For up to 3 enemies

    // Effect sprites
    sf::Texture attackEffectTexture;

    // Animation variables
    sf::Clock animationClock;
    float animationSpeed = 0.2f; // time per frame
    int currentFrame = 1;
    int frameWidth = 180;  
    int frameHeight = 180; 
    int maxFrames = 11;

public:
    BattleState(Game *game, EnemyGroup *enemies, FloorState *floorState);
    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update() override;
    void render(sf::RenderWindow &window) override;

    std::string getName() const override
    {
        return "BattleState";
    }
};