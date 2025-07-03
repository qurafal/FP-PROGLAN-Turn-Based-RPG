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

    FloorState *floorState; // Pointer to the floor state for returning after battle

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
    bool attackChosen = true; // true = attack, false = skill (expand as needed)

    std::vector<std::string> actionList = {"Attack", "Skill 1", "Skill 2", "Skill 3"};
    int selectedAction = 0;

    int globalAP = 6; // Global Action Points for the turn

    int turn = 0;

    /*ANIMATION*/

    // Background and UI sprites
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Character sprites
    sf::Texture characterTexture[4];
    sf::Sprite characterSprites[4]; // For up to 4 party members

    // Enemy sprites
    sf::Texture enemyTexture[3];
    sf::Sprite enemySprites[3]; // For up to 3 enemies

    // Effect sprites
    sf::Texture attackEffectTexture;
    sf::Texture damageEffectTexture;
    sf::Texture healEffectTexture;
    sf::Sprite effectSprite;

    // Animation variables
    sf::Clock animationClock;
    float animationTime = 0.0f;
    bool isAnimating = false;
    enum AnimationType
    {
        NONE,
        ATTACK_ANIMATION,
        DAMAGE_ANIMATION,
        HEAL_ANIMATION,
        ENEMY_ATTACK_ANIMATION
    };
    AnimationType currentAnimationType = NONE;
    int animationTargetParty = -1;
    int animationTargetEnemy = -1;

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