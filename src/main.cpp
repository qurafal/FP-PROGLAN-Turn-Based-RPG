#include "include/main.h"
#include <SFML/Graphics.hpp>
//CONSIDER DELETING MAKEFILE-related files
#include "Battle/party.h"
#include "Battle/enemy_group.h"
#include "Battle/battle_manager.h"
#include "Entity/character.h"
#include "Entity/enemies.h"
#include "State/MainMenuState.h"
#include "State/gameState.h"

int main() {

        sf::RenderWindow window(sf::VideoMode(800, 600), "Exploration 22");
    StateManager manager;
    manager.setState(std::make_unique<MainMenuState>(&manager));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (manager.getState())
                manager.getState()->handleEvent(window, event);
        }
        if (manager.getState())
            manager.getState()->update(window);

        window.clear();
        if (manager.getState())
            manager.getState()->render(window);
        window.display();
    }
    // // Create party
    // Party party;
    // party.addMember(std::make_unique<Arthesa>());

    // // Create enemy group
    // EnemyGroup enemyGroup;
    // enemyGroup.addEnemy(std::make_unique<Goblin>());

    // // Create battle manager
    // BattleManager battleManager(std::move(party), std::move(enemyGroup));

    // std::cout << "Battle Start!\n";
    // while (!battleManager.isBattleOver()) {
    //     std::cout << "\nParty AP: " << battleManager.getAP() << "\n";

    //     // Show party status
    //     std::cout << "Party:\n";
    //     for (size_t i = 0; i < battleManager.getParty().size(); ++i) {
    //         Character* ch = battleManager.getParty().getMember(i);
    //         std::cout << "  [" << i << "] " << ch->getName() << " HP: " << ch->getHP() << "/" << ch->getMaxHP() << "\n";
    //     }

    //     // Show enemy status
    //     std::cout << "Enemies:\n";
    //     for (size_t i = 0; i < battleManager.getEnemyGroup().size(); ++i) {
    //         Enemy* en = battleManager.getEnemyGroup().getEnemy(i);
    //         std::cout << "  [" << i << "] " << en->getName() << " HP: " << en->getHP() << "/" << en->getMaxHP() << "\n";
    //     }

    //     // Example: Arthesa attacks Goblin with baseAttack if enough AP
    //     Character* player = battleManager.getParty().getMember(0);
    //     Enemy* enemy = battleManager.getEnemyGroup().getEnemy(0);

    //     if (battleManager.useAP(1)) {
    //         std::cout << player->getName() << " attacks " << enemy->getName() << "!\n";
    //         player->baseAttack(*enemy, 1);
    //     } else {
    //         std::cout << "Not enough AP!\n";
    //     }

    //     // Enemy attacks back if alive
    //     if (enemy->isAlive()) {
    //         std::cout << enemy->getName() << " attacks " << player->getName() << "!\n";
    //         enemy->attack1(*player);
    //     }

    //     // Reset AP for next turn (for demo, usually after all actions)
    //     battleManager.resetAP();
    // }

    // if (battleManager.isPlayerVictory()) {
    //     std::cout << "\nYou win!\n";
    // } else {
    //     std::cout << "\nYou lose!\n";
    // }


    // sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Text Example");

    // // Load font
    // sf::Font font;
    // if (!font.loadFromFile("PixelOperator.ttf")) {
    //     return -1; // Font loading failed
    // }

    // // Create text
    // sf::Text text;
    // text.setFont(font);
    // text.setString("Hello, SFML!");
    // text.setCharacterSize(48); // in pixels
    // text.setFillColor(sf::Color::White);
    // text.setPosition(200, 250); // x, y coordinates

    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //         if (event.type == sf::Event::Closed)
    //             window.close();

    //     window.clear(sf::Color::Black);
    //     window.draw(text);
    //     window.display();
    // }

    return 0;
}

   



