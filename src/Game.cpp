#include "Game.hpp"
#include "screens/MainScreen.hpp"
#include <memory>

Game::Game() {
    this->currentScreen = std::unique_ptr<Screen>(new MainScreen());
}

void Game::loop() {
    this->currentScreen->loop(this);
    if (this->screenNeedsToChange) {
        this->currentScreen = std::move(this->nextScreen);
        this->screenNeedsToChange = false;
    }
}

void Game::changeCurrentScreen(std::unique_ptr<Screen> newScreen) {
    this->screenNeedsToChange = true;
    this->nextScreen = std::move(newScreen);
}

Game::~Game() {
}
