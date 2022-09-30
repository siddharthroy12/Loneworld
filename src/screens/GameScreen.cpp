#include "GameScreen.hpp"

GameScreen::GameScreen() {
    std::cout << "Game Screen enter" << std::endl;
}

void GameScreen::loop(Game *context) {
    this->world.update();
    this->world.render();
}

GameScreen::~GameScreen() {
    std::cout << "Game Screen leaves" << std::endl;
}
