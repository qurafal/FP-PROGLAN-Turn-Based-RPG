#include "EventState.h"
#include "FloorState.h"
#include "../Game/game.h"
#include <iostream>

EventState::EventState(Game *game, FloorState *floorState)
    : game(game), party(&game->getParty()), floorState(floorState), selectedChoice(0), showingResult(false), gen(rd())
{
    
    if (!font.loadFromFile("PixelOperator.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
    }


    titleText.setFont(font);
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(50, 50);

    descriptionText.setFont(font);
    descriptionText.setCharacterSize(20);
    descriptionText.setFillColor(sf::Color::White);
    descriptionText.setPosition(50, 150);

    for (int i = 0; i < 3; ++i)
    {
        choiceTexts[i].setFont(font);
        choiceTexts[i].setCharacterSize(18);
        choiceTexts[i].setPosition(50, 350 + i * 40);
    }

    // init scenario 
    initializeScenarios();
    selectRandomScenario();
}

//TEMPLATE scenario
void EventState::initializeScenarios()
{
    // Scenario 1: Mysterious Merchant
    EventScenario merchant;
    merchant.title = "Mysterious Merchant";
    merchant.description = "A hooded figure approaches your party with various wares.\n'Welcome, travelers! I have items that might interest you...'";
    merchant.backgroundPath = "src/Assets/Img/Events/merchant_background.png";

    Choice merchantChoice1 = {"Buy a strength potion (Increase ATK)", "The merchant smiles and hands you a glowing red potion.", true, 1, 5, -1};
    Choice merchantChoice2 = {"Buy a protection charm (Increase DEF)", "You receive a shimmering amulet that feels warm to the touch.", true, 2, 3, -1};
    Choice merchantChoice3 = {"Politely decline and move on", "The merchant nods understandingly. 'Perhaps another time, traveler.'", false, 0, 0, -1};

    merchant.choices = {merchantChoice1, merchantChoice2, merchantChoice3};
    scenarios.push_back(merchant);

    // Scenario 2: Ancient Shrine
    EventScenario shrine;
    shrine.title = "Ancient Shrine";
    shrine.description = "You discover an ancient shrine glowing with mystical energy.\nThe air hums with magical power...";
    shrine.backgroundPath = "src/Assets/Img/Events/shrine_background.png";

    Choice shrineChoice1 = {"Pray at the shrine (Increase HP)", "A warm light envelops your party, healing and strengthening you.", true, 0, 10, -1};
    Choice shrineChoice2 = {"Study the magical runes (Increase MAG)", "Ancient knowledge flows into your mind, enhancing your magical abilities.", true, 3, 4, -1};
    Choice shrineChoice3 = {"Leave the shrine untouched", "You decide not to disturb the ancient site and continue on your journey.", false, 0, 0, -1};

    shrine.choices = {shrineChoice1, shrineChoice2, shrineChoice3};
    scenarios.push_back(shrine);

    // Scenario 3: Wounded Traveler
    EventScenario traveler;
    traveler.title = "Wounded Traveler";
    traveler.description = "You encounter a injured traveler on the path.\n'Please... help me...' they whisper weakly.";
    traveler.backgroundPath = "src/Assets/Img/Events/traveler_background.png";

    Choice travelerChoice1 = {"Help heal the traveler", "The grateful traveler teaches you a defensive technique.", true, 4, 3, -1};
    Choice travelerChoice2 = {"Share your supplies", "The traveler recovers and shares survival wisdom with your party.", true, 0, 5, -1};
    Choice travelerChoice3 = {"Keep walking", "You decide not to get involved and continue on your path.", false, 0, 0, -1};

    traveler.choices = {travelerChoice1, travelerChoice2, travelerChoice3};
    scenarios.push_back(traveler);

    // Scenario 4: Crystal Cave
    EventScenario cave;
    cave.title = "Glowing Crystal Cave";
    cave.description = "You find a cave filled with glowing crystals.\nThe crystals pulse with various colored lights...";
    cave.backgroundPath = "src/Assets/Img/Events/cave_background.png";

    Choice caveChoice1 = {"Touch the red crystal", "Fire energy courses through you, increasing your attack power!", true, 1, 7, 0};        // Only first character
    Choice caveChoice2 = {"Touch the blue crystal", "Ice energy flows through you, strengthening your magical resistance!", true, 4, 6, 0}; // Only first character
    Choice caveChoice3 = {"Leave the crystals alone", "You decide the crystals might be dangerous and leave them untouched.", false, 0, 0, -1};

    cave.choices = {caveChoice1, caveChoice2, caveChoice3};
    scenarios.push_back(cave);

    // Scenario 5: Training Ground
    EventScenario training;
    training.title = "Abandoned Training Ground";
    training.description = "You discover an old training ground with practice dummies and weapons.\nThe equipment looks well-maintained despite being abandoned...";
    training.backgroundPath = "src/Assets/Img/Events/training_background.png";

    Choice trainingChoice1 = {"Practice combat techniques", "Your party hones their fighting skills together.", true, 1, 3, -1};
    Choice trainingChoice2 = {"Practice defensive maneuvers", "You learn better ways to protect yourself in battle.", true, 2, 4, -1};
    Choice trainingChoice3 = {"Just rest here", "You take a peaceful break but don't gain any new skills.", false, 0, 0, -1};

    training.choices = {trainingChoice1, trainingChoice2, trainingChoice3};
    scenarios.push_back(training);
}

void EventState::selectRandomScenario()
{
    std::uniform_int_distribution<> dis(0, scenarios.size() - 1);
    currentScenario = dis(gen);

    // Load background untuk scenario ini
    if (!backgroundTexture.loadFromFile(scenarios[currentScenario].backgroundPath))
    {
        std::cerr << "Failed to load event background: " << scenarios[currentScenario].backgroundPath << std::endl;
        // Load default background
        if (!backgroundTexture.loadFromFile("src/Assets/Img/Events/default_background.png"))
        {
            std::cerr << "Failed to load default event background" << std::endl;
        }
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(0.43f, 0.43f);
    backgroundSprite.setPosition(-50, -140);

    // 
    titleText.setString(scenarios[currentScenario].title);
    descriptionText.setString(scenarios[currentScenario].description);

    
    for (size_t i = 0; i < scenarios[currentScenario].choices.size() && i < 3; ++i)
    {
        choiceTexts[i].setString(std::to_string(i + 1) + ". " + scenarios[currentScenario].choices[i].text);
        choiceTexts[i].setFillColor(sf::Color::White);
    }

    
    for (size_t i = scenarios[currentScenario].choices.size(); i < 3; ++i)
    {
        choiceTexts[i].setString("");
    }
}

void EventState::executeChoice(const Choice &choice)
{
    resultText = choice.result;

    if (choice.isUpgrade)
    {
        applyUpgrade(choice.targetCharacter, choice.upgradeType, choice.upgradeAmount);

        
        std::string upgradeNames[] = {"HP", "ATK", "DEF", "MAG", "RES"};
        resultText += "\n\n[UPGRADE] ";

        if (choice.targetCharacter == -1)
        {
            resultText += "All party members gained +" + std::to_string(choice.upgradeAmount) + " " + upgradeNames[choice.upgradeType] + "!";
        }
        else
        {
            Character *character = party->getMember(choice.targetCharacter);
            if (character)
            {
                resultText += character->getName() + " gained +" + std::to_string(choice.upgradeAmount) + " " + upgradeNames[choice.upgradeType] + "!";
            }
        }
    }

    showingResult = true;
}

void EventState::applyUpgrade(int charIndex, int upgradeType, int amount)
{
    if (charIndex == -1) // Apply ke semua
    {
        for (size_t i = 0; i < party->size(); ++i)
        {
            Character *character = party->getMember(i);
            if (character)
            {
                switch (upgradeType)
                {
                case 0: // HP
                    character->setHP(character->getHP() + amount);
                    character->setMaxHP(character->getMaxHP() + amount);
                    break;
                case 1: // ATK
                    character->setATK(character->getATK() + amount);
                    break;
                case 2: // DEF
                    character->setDEF(character->getDEF() + amount);
                    break;
                case 3: // MAG
                    character->setINT(character->getINT() + amount);
                    break;
                case 4: // RES
                    character->setRES(character->getRES() + amount);
                    break;
                }
            }
        }
    }
    else if (charIndex >= 0 && charIndex < static_cast<int>(party->size())) 
    {
        Character *character = party->getMember(charIndex);
        if (character)
        {
            switch (upgradeType)
            {
            case 0: // HP
                character->setHP(character->getHP() + amount);
                character->setMaxHP(character->getMaxHP() + amount);
                break;
            case 1: // ATK
                character->setATK(character->getATK() + amount);
                break;
            case 2: // DEF
                character->setDEF(character->getDEF() + amount);
                break;
            case 3: // MAG atau INT
                character->setINT(character->getINT() + amount);
                break;
            case 4: // RES
                character->setRES(character->getRES() + amount);
                break;
            }
        }
    }
}

void EventState::handleEvent(sf::RenderWindow &window, sf::Event &event)
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (!showingResult)
            {
                
                if (event.key.code == sf::Keyboard::Up)
                {
                    selectedChoice = (selectedChoice - 1 + scenarios[currentScenario].choices.size()) % scenarios[currentScenario].choices.size();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    selectedChoice = (selectedChoice + 1) % scenarios[currentScenario].choices.size();
                }
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    executeChoice(scenarios[currentScenario].choices[selectedChoice]);
                }
            }
            else
            {
                //Selesai
                if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space)
                {

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
            }
        }
    }
}

void EventState::update()
{
}

void EventState::render(sf::RenderWindow &window)
{
    window.clear(sf::Color(20, 20, 40));

    
    window.draw(backgroundSprite);

    if (!showingResult)
    {
        
        window.draw(titleText);
        window.draw(descriptionText);

        
        for (size_t i = 0; i < scenarios[currentScenario].choices.size() && i < 3; ++i)
        {
            if (static_cast<int>(i) == selectedChoice)
            {
                choiceTexts[i].setFillColor(sf::Color::Yellow);
            }
            else
            {
                choiceTexts[i].setFillColor(sf::Color::White);
            }
            window.draw(choiceTexts[i]);
        }

        
        sf::Text instructionText("Use UP/DOWN to select, ENTER to choose", font, 16);
        instructionText.setFillColor(sf::Color::White);
        instructionText.setPosition(50, 500);
        window.draw(instructionText);
    }
    else
    {
        
        sf::Text resultDisplay(resultText, font, 20);
        resultDisplay.setFillColor(sf::Color::White);
        resultDisplay.setPosition(50, 200);
        window.draw(resultDisplay);

        sf::Text continueText("Press ENTER or SPACE to continue...", font, 18);
        continueText.setFillColor(sf::Color::Yellow);
        continueText.setPosition(50, 450);
        window.draw(continueText);
    }

    window.display();
}
