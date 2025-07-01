#include "MenuState.h"
#include "SecondMenu.h"
#include "../Game/game.h"

class SecondMenu; // Forward declaration


MenuState::MenuState(Game *game)
: game(game)
{
    
    if (!texture.loadFromFile("src/Assets/Img/MainMenu/MainMenu.png"))
    {
        throw std::runtime_error("Failed to load background texture");
    }
    backgroundSprite.setTexture(texture);
    
    // Load font and set up title text
    if (!font.loadFromFile("PixelOperator.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    title.setFont(font);
    title.setString("Exploration 22");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(100, 100); // Set position as needed
}

void MenuState::handleEvent(sf::RenderWindow &window, sf::Event &event)
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
                selectedOption = (selectedOption - 1 + 2) % 2;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                std::cout << "[INPUT] DOWN" << std::endl;
                selectedOption = (selectedOption + 1) % 2;
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {
                std::cout << "[INPUT] TRIGGER" << std::endl;
                switch (selectedOption)
                {
                case 0:
                    std::cout << "[SELECT] Begin Exploration" << std::endl;
                    game->setState(new SecondMenu(game)); // Assuming you have a SecondMenu state
                    return;
                    break;
                case 1:
                    std::cout << "[SELECT] Exit" << std::endl;
                    window.close();
                    return;
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void MenuState::update()
{
}

void MenuState::render(sf::RenderWindow &window)
{
    backgroundSprite.setPosition(0, -200); 
    backgroundSprite.setScale(1.0f, 1.0f);
    window.draw(backgroundSprite); 
    window.draw(title);

    for (int i = 0; i < 2; ++i)
    {
        sf::Text optionText;
        optionText.setFont(font);
        optionText.setString(options[i]);
        optionText.setCharacterSize(30);
        optionText.setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
        optionText.setPosition(100, 200 + i * 50); // Adjust position as needed
        window.draw(optionText);
    }
}