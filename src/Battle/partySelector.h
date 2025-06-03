#pragma once
#include "party.h"
Party partySelector(sf::RenderWindow& window) {
    sf::Font font;
    font.loadFromFile("PixelOperator.ttf"); 

    std::vector<std::string> characterNames = {"Arthesa", "Ahmed", "Perkia", "Hamilla"};
    std::vector<bool> picked(characterNames.size(), false);
    int selected = 0;
    Party party;
    bool done = false;

    while (window.isOpen() && !done) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    selected = (selected + characterNames.size() - 1) % characterNames.size();
                if (event.key.code == sf::Keyboard::Down)
                    selected = (selected + 1) % characterNames.size();
                if (event.key.code == sf::Keyboard::Enter && party.size() < 3 && !picked[selected]) {
                    switch (selected) {
                        case 0: party.addMember(std::make_unique<Arthesa>()); break;
                        case 1: party.addMember(std::make_unique<Ahmed>()); break;
                        case 2: party.addMember(std::make_unique<Perkia>()); break;
                        case 3: party.addMember(std::make_unique<Hamilla>()); break;
                    }
                    picked[selected] = true;
                }
                if (event.key.code == sf::Keyboard::Escape && party.size() > 0) {
                    done = true;
                }
            }
        }

        window.clear(sf::Color(30,30,30));

        // Judul
        sf::Text title("Pilih karakter untuk party (max 3):", font, 24);
        title.setPosition(30, 20);
        window.draw(title);

        // Daftar karakter
        for (size_t i = 0; i < characterNames.size(); ++i) {
            sf::Text text(characterNames[i], font, 32);
            text.setPosition(60, 70 + i * 40);
            if (picked[i])
                text.setFillColor(sf::Color(100,100,100)); // Sudah dipilih, abu-abu
            else
                text.setFillColor(i == selected ? sf::Color::Yellow : sf::Color::White);
            window.draw(text);
        }

        // Party saat ini
        sf::Text partyTitle("Party:", font, 24);
        partyTitle.setPosition(350, 70);
        window.draw(partyTitle);

        for (size_t i = 0; i < party.size(); ++i) {
            Character* ch = party.getMember(i);
            sf::Text text(ch->getName(), font, 28);
            text.setPosition(370, 110 + i * 35);
            text.setFillColor(sf::Color::Cyan);
            window.draw(text);
        }

        // Info
        sf::Text info("Enter = Tambah, Up/Down = Pilih, ESC = Selesai (min 1)", font, 16);
        info.setPosition(30, 450);
        window.draw(info);

        window.display();
    }
    return party;
}