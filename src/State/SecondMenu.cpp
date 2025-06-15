#include "SecondMenu.h"
#include "../Game/game.h"
#include "PartySelectState.h"

SecondMenu::SecondMenu(Game *game)
    : game(game)
{
    // Load font and set up title text
    if (!font.loadFromFile("PixelOperator.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    title.setFont(font);
    title.setString("Now Exploring");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(100, 100); // Set position as needed
}

void SecondMenu::handleEvent(sf::RenderWindow &window, sf::Event &event)
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
                selectedOption = (selectedOption - 1 + 3) % 3;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                std::cout << "[INPUT] DOWN" << std::endl;
                selectedOption = (selectedOption + 1) % 3;
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {
                std::cout << "[INPUT] TRIGGER" << std::endl;
                switch (selectedOption)
                {
                case 0:
                    if (game->getParty().getMembers().empty())
                    {
                        std::cout << "[SELECT] No party members, cannot select party" << std::endl;
                        return;
                        break;
                    }
                    std::cout << "[SELECT] Enter Node" << std::endl;
                    game->setState(new FloorState(game, game->getCurrentFloor()));
                    return;
                    break;
                case 1:

                    std::cout << "[SELECT] Party Select" << std::endl;
                    game->setState(new PartySelectState(game));
                    return;
                    break;
                case 2:
                    std::cout << "[SELECT] Back to Menu" << std::endl;
                    game->setState(new MenuState(game));
                    return;
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void SecondMenu::render(sf::RenderWindow &window)
{

    window.draw(title);

    for (int i = 0; i < 3; ++i)
    {
        sf::Text optionText;
        optionText.setFont(font);
        optionText.setString(options[i]);
        optionText.setCharacterSize(30);
        optionText.setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
        optionText.setPosition(100, 200 + i * 50);
        window.draw(optionText);
    }
}