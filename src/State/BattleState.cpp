#include "BattleState.h"
#include "FloorState.h"
#include "../Game/game.h"

BattleState::BattleState(Game *game, EnemyGroup *enemies, FloorState *floorState)
    : game(game), enemies(enemies), party(&game->getParty()), floorState(floorState)
{
    
    if (!font.loadFromFile("PixelOperator.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    //Texture-texture
    if (!backgroundTexture.loadFromFile("src/Assets/Img/BattleState/BattleBackground.png"))
    {
        std::cerr << "Failed to load battle background" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(.6f, .6f);

    std::string characterPaths[4] = {
        "src/Assets/Img/BattleState/Arthesa/Idle.png",
        "src/Assets/Img/BattleState/Ahmed/Idle.png",
        "src/Assets/Img/BattleState/Perkia/Idle.png",
        "src/Assets/Img/BattleState/Hamilla/Idle.png"};

    for (int i = 0; i < 4; ++i)
    {
        if (!characterTexture[i].loadFromFile(characterPaths[i]))
        {
            std::cerr << "Failed to load character: " << characterPaths[i] << std::endl;
        }
        characterSprites[i].setTexture(characterTexture[i]);
    }

    for (size_t i = 0; i < enemies->size() && i < 4; ++i)
    {
        Enemy *enemy = enemies->getEnemy(i);
        if (enemy)
        {
            std::string enemyPath = "src/Assets/Img/Enemies/" + enemy->getName() + "/Idle.png";
            if (!enemyTexture[i].loadFromFile(enemyPath))
            {
                std::cerr << "Failed to load enemy: " << enemyPath << std::endl;
            }
            enemySprites[i].setTexture(enemyTexture[i]);
        }
    }

    title.setFont(font);
    title.setString("Battle State");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(100, 100); 
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
            // if (event.key.code == sf::Keyboard::Escape)
            // {
            //     game->setState(new SecondMenu(game, this->floorState));
            //     return;
            // }

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
                if (globalAP <= 0 || event.key.code == sf::Keyboard::F)
                {

                    phase = ENEMY_TURN;
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
                if (event.key.code == sf::Keyboard::Escape)
                {
                    phase = PLAYER_SELECT;
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
                        // Execute action
                        Character *attacker = party->getMember(selectedParty);
                        Enemy *target = enemies->getEnemy(selectedEnemy);
                        if (attacker && attacker->isAlive() && target && target->isAlive())
                        {
                            std::cout << "[LOG] Executing action: " << actionList[selectedAction] << " on enemy " << selectedEnemy << std::endl;
                            if (selectedAction == 0) 
                            {
                                if (globalAP >= 1)
                                {
                                    int APCost = attacker->baseAttack(*target, globalAP);
                                    globalAP -= APCost;
                                    std::cout << "[LOG] baseAttack executed, AP left: " << globalAP << std::endl;
                                }
                            }
                            else if (selectedAction == 1)
                            {
                                int APCost = attacker->skill1(*target, globalAP);
                                globalAP -= APCost;

                                std::cout << "[LOG] skill1 executed, AP left: " << globalAP << std::endl;
                            }
                            else if (selectedAction == 2)
                            {
                                int APCost = attacker->skill2(*target, globalAP);
                                globalAP -= APCost;

                                std::cout << "[LOG] skill2 executed, AP left: " << globalAP << std::endl;
                            }
                            else if (selectedAction == 3)
                            {
                                int APCost = attacker->skill3(*target, globalAP);
                                globalAP -= APCost;

                                std::cout << "[LOG] skill3 executed, AP left: " << globalAP << std::endl;
                            }
                        }

                        if (globalAP <= 0 || event.key.code == sf::Keyboard::F)
                        {

                            phase = ENEMY_TURN;
                        }
                        phase = PLAYER_SELECT;
                        std::cout << "[PHASE]: " << phase << std::endl;
                    }
                }
            }
        }
    }
}
void BattleState::update()
{
    if (animationClock.getElapsedTime().asSeconds() >= animationSpeed)
    {
        currentFrame = (currentFrame + 1) % maxFrames;
        animationClock.restart();
    }
    if (phase == ENEMY_TURN)
    {
        // Musuh yang hidup akan nyerang party
        for (size_t i = 0; i < enemies->size(); ++i)
        {
            Enemy *enemy = enemies->getEnemy(i);
            if (enemy && enemy->isAlive())
            {
                
                std::vector<int> aliveIndices;
                for (size_t j = 0; j < party->size(); ++j)
                    if (party->getMember(j)->isAlive())
                        aliveIndices.push_back(j);
                if (!aliveIndices.empty())
                {
                    int targetIdx = aliveIndices[rand() % aliveIndices.size()];
                    Character *target = party->getMember(targetIdx);
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
        globalAP = 6; // Reset AP 
        phase = PLAYER_SELECT;
        std::cout << "[PHASE]: " << phase << std::endl;
    }

    if (enemies->allDefeated())
    {
        std::cout << "[LOG] All enemies defeated, returning to FloorState" << std::endl;

        if (floorState)
        {

            Node *node = floorState->floor.getNode(floorState->selectedStep, floorState->selectedBranch);
            if (node)
            {
                node->setVisited(true);
                floorState->selectedStep++;
                floorState->maxVisitedStep++;
            }
            game->setState(floorState);
        }
        return;
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
    window.draw(backgroundSprite);
    window.draw(title);

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
            // DRAW TULISAN NYA
            sf::Text memberText(member->getName() + " HP: " + std::to_string(member->getHP()), font, 20);
            memberText.setPosition(25 + i * 10, 320 + i * 80);

            if ((phase == PLAYER_SELECT && (int)i == selectedParty) ||
                (phase == TARGET_SELECT && (int)i == selectedParty && phase != ACTION_SELECT))
            {
                memberText.setFillColor(sf::Color::Yellow);
            }
            else
            {
                memberText.setFillColor(member->isAlive() ? sf::Color::White : sf::Color::Red);
            }
            // GAMBAR SPRITE CHARACTER
            characterSprites[i].setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            characterSprites[i].setPosition(40 + i * 20, 230 + i * 50);
            characterSprites[i].setScale(1.5f + i * 0.2f, 1.5f + i * 0.2f);
            if (member->getName() == "Arthesa")
                window.draw(characterSprites[0]);
            if (member->getName() == "Ahmed")
                window.draw(characterSprites[1]);
            if (member->getName() == "Perkia")
                window.draw(characterSprites[2]);
            if (member->getName() == "Hamilla")
                window.draw(characterSprites[3]);
            window.draw(memberText);
        }
    }
    //Render musuh
    for (size_t i = 0; i < enemies->size(); ++i)
    {
        Enemy *enemy = enemies->getEnemy(i);
        if (enemy)
        {
            sf::Text enemyText(enemy->getName() + " HP: " + std::to_string(enemy->getHP()), font, 20);
            enemyText.setPosition(580, 320 + i * 80);
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
        enemySprites[i].setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
        enemySprites[i].setPosition(420 - i * 20, 230 + i * 50);
        enemySprites[i].setScale(1.5f + i * 0.2f, 1.5f + i * 0.2f);
        window.draw(enemySprites[i]);
    }
    // render action selection
    if (phase == ACTION_SELECT)
    {
        Character *selectedCharacter = party->getMember(selectedParty);
        if (selectedCharacter)
        {

            for (size_t i = 0; i < actionList.size(); ++i)
            {
                int apCost = 0;

                // DAPETIN AP COST
                if (Arthesa *arthesa = dynamic_cast<Arthesa *>(selectedCharacter))
                {
                    apCost = arthesa->getAPCost(i);
                }
                else if (Perkia *perkia = dynamic_cast<Perkia *>(selectedCharacter))
                {
                    apCost = perkia->getAPCost(i);
                }
                else if (Ahmed *ahmed = dynamic_cast<Ahmed *>(selectedCharacter))
                {
                    apCost = ahmed->getAPCost(i);
                }
                else if (Hamilla *hamilla = dynamic_cast<Hamilla *>(selectedCharacter))
                {
                    apCost = hamilla->getAPCost(i);
                }
                // TEXT ACTION
                sf::Text actionText(actionList[i] + "(" + std::to_string(apCost) + ")", font, 28);
                actionText.setPosition(330, 300 + i * 40);
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
    }

    window.display();
}