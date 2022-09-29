#include "GameScreen.hpp"

GameScreen::GameScreen() {
    std::cout << "Game Screen enter" << std::endl;
}

void GameScreen::loop(Game *context) {
    DrawText("GameScreen", 0, 0, 0, BLACK);
}

GameScreen::~GameScreen() {
    std::cout << "Game Screen leaves" << std::endl;
}
