#include "MainMenuState.h"
#include "../Battle/partySelector.h"

MainMenuState::MainMenuState(StateManager *manager) : manager(manager)
{
    font.loadFromFile("PixelOperator.ttf");
}

void MainMenuState::handleEvent(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
            selected = (selected + menuItems.size() - 1) % menuItems.size();
        if (event.key.code == sf::Keyboard::Down)
            selected = (selected + 1) % menuItems.size();
        if (event.key.code == sf::Keyboard::Enter)
        {
            switch (selected)
            {
            case 0: // Start
                manager->setState(std::make_unique<SubMenuState>(manager));
                break;
            case 1: // Setting
                manager->setState(std::make_unique<SubMenuState>(manager));
                break;
            case 2: // Exit
                window.close();
                break;
            }
        }
    }
}
void MainMenuState::update(sf::RenderWindow &) {}
void MainMenuState::render(sf::RenderWindow &window)
{
    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        sf::Text text(menuItems[i], font, 40);
        text.setPosition(300, 200 + i * 60);
        text.setFillColor(i == selected ? sf::Color::Yellow : sf::Color::White);
        window.draw(text);
    }
}

SubMenuState::SubMenuState(StateManager *manager) : manager(manager)
{
    font.loadFromFile("PixelOperator.ttf");
}

void SubMenuState::update(sf::RenderWindow &) {}
void SubMenuState::render(sf::RenderWindow &window)
{
    for (size_t i = 0; i < subMenuItems.size(); ++i)
    {
        sf::Text text(subMenuItems[i], font, 40);
        text.setPosition(300, 200 + i * 60);
        text.setFillColor(i == selected ? sf::Color::Cyan : sf::Color::White);
        window.draw(text);
    }
}
void SubMenuState::handleEvent(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
            selected = (selected + subMenuItems.size() - 1) % subMenuItems.size();
        if (event.key.code == sf::Keyboard::Down)
            selected = (selected + 1) % subMenuItems.size();
        if (event.key.code == sf::Keyboard::Enter)
        {
            switch (selected)
            {
            case 0: // SubOption1 Party Selection
            {
                Party party = partySelector(window);
                break;
            }

            case 2: // Back
            {
                manager->setState(std::make_unique<MainMenuState>(manager));
                break;
            }
            }
        }
    }
}