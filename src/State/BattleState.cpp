#include "BattleState.h"
#include "FloorState.h"
#include "../Game/game.h"

BattleState::BattleState(Game *game, EnemyGroup* enemies, FloorState *floorState)
    : game(game), enemies(enemies), party(&game->getParty()), floorState(floorState)
{
    // Load font and set up title text
    if (!font.loadFromFile("PixelOperator.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    title.setFont(font);
    title.setString("Battle State");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(100, 100); // Set position as needed
}
void BattleState::handleEvent(sf::RenderWindow &window, sf::Event &event)
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                game->setState(new SecondMenu(game));
                return;
            }

            // --- PLAYER TURN ---
            if (phase == PLAYER_SELECT)
            {
                if (party->size() > 0)
                {

                    if (event.key.code == sf::Keyboard::Up)
                        selectedParty = (selectedParty - 1 + party->size()) % party->size();
                    if (event.key.code == sf::Keyboard::Down)
                        selectedParty = (selectedParty + 1) % party->size();
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (party->getMember(selectedParty)->isAlive())
                        {
                            std::cout << "[LOG] Party member selected: " << selectedParty << std::endl;
                            phase = ACTION_SELECT;
                            std::cout << "[PHASE]: " << phase << std::endl;
                        }
                    }
                }
            }
            else if (phase == ACTION_SELECT)
            {
                if (event.key.code == sf::Keyboard::Up)
                    selectedAction = (selectedAction - 1 + actionList.size()) % actionList.size();
                if (event.key.code == sf::Keyboard::Down)
                    selectedAction = (selectedAction + 1) % actionList.size();
                if (event.key.code == sf::Keyboard::Enter)
                {
                    std::cout << "[LOG] Action selected: " << actionList[selectedAction] << std::endl;
                    phase = TARGET_SELECT;
                    std::cout << "[PHASE]: " << phase << std::endl;
                }
            }
            else if (phase == TARGET_SELECT)
            {
                if (enemies->size() > 0)
                {

                    if (event.key.code == sf::Keyboard::Up)
                        selectedEnemy = (selectedEnemy - 1 + enemies->size()) % enemies->size();
                    if (event.key.code == sf::Keyboard::Down)
                        selectedEnemy = (selectedEnemy + 1) % enemies->size();
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        // Execute attack
                        Character *attacker = party->getMember(selectedParty);
                        Enemy *target = enemies->getEnemy(selectedEnemy);
                        if (attacker && attacker->isAlive() && target && target->isAlive())
                        {
                            std::cout << "[LOG] Executing action: " << actionList[selectedAction] << " on enemy " << selectedEnemy << std::endl;
                            if (selectedAction == 0) // Attack
                            {
                                if (globalAP >= 1)
                                {
                                    attacker->baseAttack(*target, globalAP);
                                    globalAP -= 1;
                                    std::cout << "[LOG] baseAttack executed, AP left: " << globalAP << std::endl;
                                }
                            }
                            else if (selectedAction == 1)
                            {
                                attacker->skill1(*target, globalAP);
                                std::cout << "[LOG] skill1 executed, AP left: " << globalAP << std::endl;
                            }
                            else if (selectedAction == 2)
                            {
                                attacker->skill2(*target, globalAP);
                                std::cout << "[LOG] skill2 executed, AP left: " << globalAP << std::endl;
                            }
                            else if (selectedAction == 3)
                            {
                                attacker->skill3(*target, globalAP);
                                std::cout << "[LOG] skill3 executed, AP left: " << globalAP << std::endl;
                            }
                        }
                        phase = ENEMY_TURN;
                        std::cout << "[PHASE]: " << phase << std::endl;
                    }
                }
            }
        }
    }
}
void BattleState::update()
{
    // Update logic for the battle state
    if (phase == ENEMY_TURN)
    {
        // Each alive enemy attacks a random alive party member
        for (size_t i = 0; i < enemies->size(); ++i)
        {
            Enemy *enemy = enemies->getEnemy(i);
            if (enemy && enemy->isAlive())
            {
                // Find a random alive party member
                std::vector<int> aliveIndices;
                for (size_t j = 0; j < party->size(); ++j)
                    if (party->getMember(j)->isAlive())
                        aliveIndices.push_back(j);
                if (!aliveIndices.empty())
                {
                    int targetIdx = aliveIndices[rand() % aliveIndices.size()];
                    Character *target = party->getMember(targetIdx);
                    // Use enemy's attack1
                    // Randomly choose attack1 or attack2
                    int skill = rand() % 2;
                    if (skill == 0)
                    {
                        enemy->attack1(*target);
                        std::cout << "[LOG] Enemy " << i << " used attack1 on party member " << targetIdx << std::endl;
                    }
                    else
                    {
                        enemy->attack2(*target);
                        std::cout << "[LOG] Enemy " << i << " used attack2 on party member " << targetIdx << std::endl;
                    }
                    std::cout << "[LOG] Enemy " << i << " attacked party member " << targetIdx << std::endl;
                }
            }
        }
        globalAP = 6; // Reset AP for next player turn
        phase = PLAYER_SELECT;
        std::cout << "[PHASE]: " << phase << std::endl;
    }

    // Check if one party is defeated
    if (enemies->allDefeated())
    {
        std::cout << "[LOG] All enemies defeated, returning to FloorState" << std::endl;
        Node *node = floorState->floor.getNode(floorState->selectedStep, floorState->selectedBranch);
        if (node){
            node->setVisited(true);
            floorState->selectedStep++;
            floorState->maxVisitedStep++;
        }
        game->setState(this->floorState);
    }
    if (party->allDefeated())
    {

        std::cout << "All party members defeated! Game Over!" << std::endl;
        game->setState(new MenuState(game)); // Sementara ke menustate
    }
}
void BattleState::render(sf::RenderWindow &window)
{
    window.clear(sf::Color(20, 20, 40));
    window.draw(title);

    // Render AP
    sf::Text apText("AP: " + std::to_string(globalAP), font, 24);
    apText.setPosition(50, 120);
    apText.setFillColor(sf::Color::Cyan);
    window.draw(apText);

    // Render party members
    for (size_t i = 0; i < party->size(); ++i)
    {
        Character *member = party->getMember(i);
        if (member)
        {
            sf::Text memberText(member->getName() + " HP: " + std::to_string(member->getHP()), font, 24);
            memberText.setPosition(50, 200 + i * 30);

            // Highlight selected party member
            if ((phase == PLAYER_SELECT && (int)i == selectedParty) ||
                (phase == TARGET_SELECT && (int)i == selectedParty && phase != ACTION_SELECT))
            {
                memberText.setFillColor(sf::Color::Yellow);
            }
            else
            {
                memberText.setFillColor(member->isAlive() ? sf::Color::White : sf::Color::Red);
            }
            window.draw(memberText);
        }
    }

    // Render enemies
    for (size_t i = 0; i < enemies->size(); ++i)
    {
        Enemy *enemy = enemies->getEnemy(i);
        if (enemy)
        {
            sf::Text enemyText(enemy->getName() + " HP: " + std::to_string(enemy->getHP()), font, 24);
            enemyText.setPosition(400, 200 + i * 30);
            // Highlight selected enemy during TARGET_SELECT
            if (phase == TARGET_SELECT && (int)i == selectedEnemy)
            {
                enemyText.setFillColor(sf::Color::Yellow);
            }
            else
            {
                enemyText.setFillColor(enemy->isAlive() ? sf::Color::White : sf::Color::Red);
            }
            window.draw(enemyText);
        }
    }
    // render action selection
    if (phase == ACTION_SELECT)
    {
        for (size_t i = 0; i < actionList.size(); ++i)
        {
            sf::Text actionText(actionList[i], font, 28);
            actionText.setPosition(50, 400 + i * 40);
            if ((int)i == selectedAction)
            {
                actionText.setFillColor(sf::Color::Yellow); // Highlight selected action
            }
            else
            {
                actionText.setFillColor(sf::Color::White);
            }
            window.draw(actionText);
        }
    }

    window.display();
}