#include "game.h"


void Game::initVariables() {
    this->window = nullptr;
    this->state = new MenuState(this);
    currentFloor = 1; 
    this->floor = std::make_unique<Floor>(1); 

}
void Game::initWindow() {
    this->videoMode.width = 800;
    this->videoMode.height = 600;

    this->window = new sf::RenderWindow(this->videoMode, "Exploration 22", sf::Style::Titlebar | sf::Style::Close);
}
void Game::initMusic() {
    if (!this->music.openFromFile("src/Assets/Music/Main Theme - Horsemen Approach .wav")) {
        std::cerr << "Error loading music file!" << std::endl;
    }
    this->music.setLoop(true);
    this->music.play();
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initMusic();
    
}

Game::~Game()
{
    delete this->window;
}


const bool Game::isRunning() const
{
    return this->window->isOpen();
    
}

//Funcs

void Game::updateEvents()
{
    sf::Event event;

    state->handleEvent(*this->window, event);
    state->update();
        
}
void Game::update()
{
    this->updateEvents();

}
void Game::render()
{
    this->window->clear(); 
    state->render(*this->window);
    this->window->display();
}
