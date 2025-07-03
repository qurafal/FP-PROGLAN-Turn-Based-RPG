#include "FloorState.h"
#include "BattleState.h"
#include "../Game/game.h"

FloorState::FloorState(Game *game, int floor)
    : game(game), floor(game->getCurrentFloor())
{

    // Load font and set up title text
    if (!font.loadFromFile("OldEnglishGothicPixelRegular.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    title.setFont(font);
    title.setString("Exploration 22 - Floor " + std::to_string(game->getCurrentFloor()));
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(100, 100); // Set position as needed
}

void FloorState::handleEvent(sf::RenderWindow &window, sf::Event &event)
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed)
        {

            if (event.key.code == sf::Keyboard::Right)
            {
                if (selectedStep < static_cast<int>(floor.getSteps().size()) - 1 &&
                    selectedStep < maxVisitedStep + 1)
                    selectedStep++;
                selectedBranch = 0;
            }
            // Up/down for branch selection
            if (event.key.code == sf::Keyboard::Up)
            {
                auto &branchNodes = floor.getSteps()[selectedStep];
                int branchCount = floor.getSteps()[selectedStep].size();
                if (branchCount > 1 && selectedBranch > 0 &&
                    !branchNodes[0]->isVisited() && !branchNodes[1]->isVisited())
                    selectedBranch--;
            }
            if (event.key.code == sf::Keyboard::Down)
            {
                auto &branchNodes = floor.getSteps()[selectedStep];
                int branchCount = floor.getSteps()[selectedStep].size();
                if (branchCount > 1 && selectedBranch < branchCount - 1 &&
                    !branchNodes[0]->isVisited() && !branchNodes[1]->isVisited())
                    selectedBranch++;
            }

            if (event.key.code == sf::Keyboard::Enter)
            {
                if (selectedStep <= maxVisitedStep + 1)
                {
                    // Mark as visited
                    Node *node = floor.getNode(selectedStep, 0);
                    std::cout << "[VISIT] " << node->getName() << std::endl;

                    auto &branchNodes = floor.getSteps()[selectedStep];
                    bool isBoss = branchNodes[0]->getType() == BOSS;

                    if (branchNodes.size() > 1)
                    {
                        // If either node is already visited, do nothing
                        if (branchNodes[0]->isVisited() || branchNodes[1]->isVisited())
                        {

                            return;
                        }
                        // Mark both as visited
                        branchNodes[0]->setVisited(true);
                        branchNodes[1]->setVisited(true);
                    }
                    else
                    {
                        Node *node = floor.getNode(selectedStep, selectedBranch);
                        if (node && !node->isVisited())
                        {
                            node->setVisited(true);
                        }
                    }
                    switch (branchNodes[selectedBranch]->getType())
                    {
                    case BATTLE:
                    {

                        Node *node = floor.getNode(selectedStep, selectedBranch);
                        BattleNode *battleNode = dynamic_cast<BattleNode *>(node);
                        if (battleNode)
                        {
                            game->tempSetState(new BattleState(game, &battleNode->getEnemies(), this));
                            return;
                        }
                        break;
                    }
                    case EVENT:
                        // std::cout << "[EVENT] " << branchNodes[0]->getName() << std::endl;
                        // branchNodes[0]->setVisited(true);
                        break;
                    case SHOP:
                        // std::cout << "[SHOP] " << branchNodes[0]->getName() << std::endl;
                        // game->setState(new ShopState(game, branchNodes[0]->getName()));
                        break;
                    case BOSS:
                        // std::cout << "[BOSS] " << branchNodes[0]->getName() << std::endl;
                        // game->setState(new BattleState(game, branchNodes[0]->getName()));
                        break;

                    default:
                        std::cout << "[UNKNOWN] " << branchNodes[0]->getName() << std::endl;
                        break;
                    }

                    if (selectedStep > maxVisitedStep)
                        maxVisitedStep = selectedStep;
                    selectedStep++;
                    selectedBranch = 0;
                    if (isBoss && branchNodes[0]->isVisited())
                    {
                        if (game->getCurrentFloor() < 5)
                        {
                            int nextFloor = game->getCurrentFloor() + 1;
                            std::cout << "[FLOOR] Deep down to floor " << nextFloor << std::endl;
                            game->setCurrentFloor(nextFloor);
                            game->setState(new FloorState(game, game->getCurrentFloor()));
                            return;
                        }
                        else
                        {
                            
                            game->setState(new MenuState(game));
                            return;
                        }
                    }
                }
            }
        }
        // if (event.key.code == sf::Keyboard::Escape)
        // {
        //     game->tempSetState(new SecondMenu(game, this));
        //     return;
        // }
    }
    
}

void FloorState::update()
{
    
}

void FloorState::render(sf::RenderWindow &window)
{
    window.clear(sf::Color(20, 20, 40));
    window.draw(title);

    // Draw steps horizontally
    int baseX = 80, baseY = 200, stepGap = 120;
    for (size_t step = 0; step < floor.getSteps().size(); ++step)
    {
        const auto &branchNodes = floor.getSteps()[step];
        bool branchVisited = (branchNodes.size() > 1) && (branchNodes[0]->isVisited() || branchNodes[1]->isVisited());
        for (size_t branch = 0; branch < floor.getSteps()[step].size(); ++branch)
        {
            Node *node = floor.getNode(step, branch);
            sf::Text nodeText(node->getName(), font, 28);
            nodeText.setPosition(baseX + step * stepGap, baseY + branch * 40);

            if (static_cast<int>(step) == selectedStep && static_cast<int>(branch) == selectedBranch && !branchVisited)
                nodeText.setFillColor(sf::Color::Yellow); // currently selected
            else if (branchVisited || node->isVisited())
                nodeText.setFillColor(sf::Color(60, 60, 60)); // already visited (branch or single)
            else if (static_cast<int>(step) > maxVisitedStep + 1)
                nodeText.setFillColor(sf::Color(100, 100, 100)); // locked/unvisited
            else
                nodeText.setFillColor(sf::Color::White); // available but not selected
            window.draw(nodeText);
        }
    }

    // Optionally, show info about the selected node
    Node *selectedNode = floor.getNode(selectedStep, 0);
    if (selectedNode)
    {
        sf::Text descText(selectedNode->getDescription(), font, 20);
        descText.setPosition(80, baseY + 120);
        descText.setFillColor(sf::Color(180, 180, 180));
        window.draw(descText);
    }

    window.display();
}

std::string FloorState::getName() const
{
    return "FloorState";
}