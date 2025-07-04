#include "PartySelectState.h"
#include "SecondMenu.h"
#include "../Game/game.h"

PartySelectState::PartySelectState(Game *game)
    : game(game)
{
    
    if (!font.loadFromFile("PixelOperator.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    title.setFont(font);
    title.setString("Who will sacrifice themselves?");
    title.setCharacterSize(32);
    title.setFillColor(sf::Color::Black);
    title.setPosition(50, 50); 

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
                game->setState(new SecondMenu(game, nullptr));
            }
        }
    }
}
void PartySelectState::update()
{
}
void PartySelectState::render(sf::RenderWindow &window)
{
    window.clear(sf::Color(30, 30, 30)); 
    backgroundSprite.setScale(4.2,3.1);
    window.draw(backgroundSprite);

    
    window.draw(title);

    // highlight nama
    highlightTextSprite.setScale(0.95f, 0.95f); 
    highlightTextSprite.setPosition(31, 125 + selectedOption * 40 - 4); 
    window.draw(highlightTextSprite);


    
    selectedBoxSprite.setScale(3, 3); 
    selectedBoxSprite.setPosition(210, 20); 
    window.draw(selectedBoxSprite);

    
    for (size_t i = 0; i < 4; ++i)
    {
        sf::Text text(characters[i], font, 32);
        text.setPosition(80, 120 + i * 40);
        int idx = game->getParty().findMemberByName(characters[i]);
        if (idx != -1)
        {
            //merah udah dipilih
            text.setFillColor(i == selectedOption ? sf::Color::Red : sf::Color(100, 100, 100));
        }
        else
        {
            //kuning lagi di "hover"
            text.setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
        }
        window.draw(text);
    }
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

std::string PartySelectState::getName() const
{
    return "PartySelectState";
}