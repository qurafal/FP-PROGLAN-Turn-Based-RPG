#pragma once
#include "gameState.h"

class StateManager; // Forward declaration

class MainMenuState : public GameState {
public:
    MainMenuState(StateManager* manager);

    void handleEvent(sf::RenderWindow& window, sf::Event& event) override;
    void update(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager* manager;
    std::vector<std::string> menuItems = {"Start", "Setting", "Exit"};
    int selected = 0;
    sf::Font font;
};


class SubMenuState : public GameState {
public:
    SubMenuState(StateManager* manager);

    void handleEvent(sf::RenderWindow& window, sf::Event& event) override;
    void update(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager* manager;
    std::vector<std::string> subMenuItems = {"SubOption1", "SubOption2", "Back"};
    int selected = 0;
    sf::Font font;
};

class StateManager {
public:
    void setState(std::unique_ptr<GameState> newState) {
        state = std::move(newState);
    }
    GameState* getState() { return state.get(); }
private:
    std::unique_ptr<GameState> state;
};
