#include "GameScreen.hpp"
#include <memory>

GameScreen::GameScreen(Game* context) : Screen(context) {
    std::cout << "Game Screen enter" << std::endl;
    this->world = std::unique_ptr<World>(new World(context));
}

void GameScreen::loop() {
    this->world->update();
    this->world->render();
}

GameScreen::~GameScreen() {
    std::cout << "Game Screen leaves" << std::endl;
}
