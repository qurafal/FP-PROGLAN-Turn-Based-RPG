#include "PartySelectState.h"
#include "SecondMenu.h"
#include "../Game/game.h"

PartySelectState::PartySelectState(Game *game)
    : game(game)
{
    // Load font and set up title text
    if (!font.loadFromFile("PixelOperator.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    title.setFont(font);
    title.setString("Who will sacrifice themselves?");
    title.setCharacterSize(32);
    title.setFillColor(sf::Color::Black);
    title.setPosition(50, 50); // Set position as needed

    background.loadFromFile("src/Assets/Img/PartySelectState/PartySelectBackground.png");
    backgroundSprite.setTexture(background);

    highlightText.loadFromFile("src/Assets/Img/PartySelectState/highlightText.png");
    highlightTextSprite.setTexture(highlightText);

    selectedBox.loadFromFile("src/Assets/Img/PartySelectState/selectedBox.png");
    selectedBoxSprite.setTexture(selectedBox);
}
void PartySelectState::handleEvent(sf::RenderWindow &window, sf::Event &event)
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            std::cout << "[CLOSE]" << std::endl;
            window.close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                std::cout << "[INPUT] UP" << std::endl;
                selectedOption = (selectedOption - 1 + 4) % 4;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                std::cout << "[INPUT] DOWN" << std::endl;
                selectedOption = (selectedOption + 1) % 4;
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {
                std::cout << "[INPUT] TRIGGER" << std::endl;
                std::string selectedName = characters[selectedOption];
                int idx = game->getParty().findMemberByName(selectedName);
                if (idx != -1)
                {
                    // Remove from party if already present
                    game->getParty().removeMemberByName(selectedName);
                }
                else if (game->getParty().size() < 3)
                {
                    switch (selectedOption)
                    {
                    case 0:
                        game->getParty().addMember(std::make_unique<Arthesa>());
                        break;
                    case 1:
                        game->getParty().addMember(std::make_unique<Ahmed>());
                        break;
                    case 2:
                        game->getParty().addMember(std::make_unique<Hamilla>());
                        break;
                    case 3:
                        game->getParty().addMember(std::make_unique<Perkia>());
                        break;
                    }
                }
            }
            else if (event.key.code == sf::Keyboard::Escape && game->getParty().size() > 0)
            {
                // Exit party selection
                game->setState(new SecondMenu(game));
            }
        }
    }
}
void PartySelectState::update()
{
    // No specific update logic needed for this state
    // All updates are handled in handleEvent
}
void PartySelectState::render(sf::RenderWindow &window)
{
    window.clear(sf::Color(30, 30, 30)); // Clear the window with a dark color
    backgroundSprite.setScale(4.2,3.1);
    window.draw(backgroundSprite);       // Draw background

    // Draw title
    window.draw(title);

    // Draw highlight behind the selected character name (optional, use highlightTextSprite if you want)
    highlightTextSprite.setScale(0.95f, 0.95f); 
    highlightTextSprite.setPosition(31, 125 + selectedOption * 40 - 4); // Adjust as needed
    window.draw(highlightTextSprite);


    // Draw selection box for the currently selected character
    selectedBoxSprite.setScale(3, 3); // Adjust scale as needed
    selectedBoxSprite.setPosition(210, 20); // Adjust as needed
    window.draw(selectedBoxSprite);

    // Draw character options with correct color
    for (size_t i = 0; i < 4; ++i)
    {
        sf::Text text(characters[i], font, 32);
        text.setPosition(80, 120 + i * 40);
        int idx = game->getParty().findMemberByName(characters[i]);
        if (idx != -1)
        {
            // In party: red if selected, gray otherwise
            text.setFillColor(i == selectedOption ? sf::Color::Red : sf::Color(100, 100, 100));
        }
        else
        {
            // Not in party: yellow if selected, white otherwise
            text.setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
        }
        window.draw(text);
    }

    // // Draw current party members
    // sf::Text partyTitle("Party:", font, 24);
    // partyTitle.setPosition(350, 70);
    // window.draw(partyTitle);

    for (size_t i = 0; i < game->getParty().size(); ++i)
    {
        Character *member = game->getParty().getMember(i);
        if (member)
        {
            sf::Text memberText(member->getName(), font, 24);
            memberText.setFillColor(sf::Color::Black);
            memberText.setPosition(390, 150 + i * 30);
            window.draw(memberText);
        }
    }
}

// Other Functions
std::string PartySelectState::getName() const
{
    return "PartySelectState";
}