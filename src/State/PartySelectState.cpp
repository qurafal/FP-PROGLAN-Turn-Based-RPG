#include "PartySelectState.h"
#include "SecondMenu.h"
#include "../Game/game.h"

PartySelectState::PartySelectState(Game *game)
: game(game)
{
    // Load font and set up title text
    if (!font.loadFromFile("PixelOperator.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    title.setFont(font);
    title.setString("Pilih karakter untuk party (max 3):");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(30, 20); // Set position as needed
}
void PartySelectState::handleEvent(sf::RenderWindow &window, sf::Event &event) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            std::cout << "[CLOSE]" << std::endl;
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                std::cout << "[INPUT] UP" << std::endl;
                selectedOption = (selectedOption - 1 + 4) % 4;
            } else if (event.key.code == sf::Keyboard::Down) {
                std::cout << "[INPUT] DOWN" << std::endl;
                selectedOption = (selectedOption + 1) % 4;
            } else if (event.key.code == sf::Keyboard::Enter) {
                std::cout << "[INPUT] TRIGGER" << std::endl;
                std::string selectedName = characters[selectedOption];
                int idx = game->getParty().findMemberByName(selectedName);
                if (idx != -1) {
                    // Remove from party if already present
                    game->getParty().removeMemberByName(selectedName);
                } else if (game->getParty().size() < 3) {
                    switch (selectedOption) {
                        case 0: game->getParty().addMember(std::make_unique<Arthesa>()); break;
                        case 1: game->getParty().addMember(std::make_unique<Ahmed>()); break;
                        case 2: game->getParty().addMember(std::make_unique<Hamilla>()); break;
                        case 3: game->getParty().addMember(std::make_unique<Perkia>()); break;
                    }
                }
            
                
            } else if (event.key.code == sf::Keyboard::Escape && game->getParty().size() > 0) {
                // Exit party selection
                game->setState(new SecondMenu(game));
            }
        }
    }
}

void PartySelectState::update(Game& game) {
    // Update logic for the party selection state
}
void PartySelectState::render(sf::RenderWindow &window) {
    window.clear(sf::Color(30, 30, 30)); // Clear the window with a dark color

    // Draw title
    window.draw(title);

    // Draw character options
    for (size_t i = 0; i < 4; ++i) {
        sf::Text text(characters[i], font, 32);
        text.setPosition(60, 70 + i * 40);
        if (game->getParty().getMember(i)) {
            text.setFillColor(sf::Color(100, 100, 100)); // Already picked, gray
        } else {
            text.setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
        }
        window.draw(text);
    }

    // Draw current party members
    sf::Text partyTitle("Party:", font, 24);
    partyTitle.setPosition(350, 70);
    window.draw(partyTitle);

    for (size_t i = 0; i < 4; ++i) {
        sf::Text text(characters[i], font, 32);
        text.setPosition(60, 70 + i * 40);
        int idx = game->getParty().findMemberByName(characters[i]);
        if (idx != -1) {
            // In party: red if selected, gray otherwise
            text.setFillColor(i == selectedOption ? sf::Color::Red : sf::Color(100, 100, 100));
        } else {
            // Not in party: yellow if selected, white otherwise
            text.setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
        }
        window.draw(text);
    }

    for (size_t i = 0; i < game->getParty().size(); ++i) {
        Character* member = game->getParty().getMember(i);
        if (member) {
            sf::Text memberText(member->getName(), font, 24);
            memberText.setPosition(350, 110 + i * 30);
            window.draw(memberText);
        }
    }

    
}