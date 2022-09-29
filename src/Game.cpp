#include "Game.hpp"
#include "screens/MainScreen.hpp"
#include <memory>

Game::Game() {
    // Load Assets
    this->asset.font = LoadFontEx("assets/fonts/Monocraft.ttf", 40, nullptr, 0);

    // Set starting screen
    this->currentScreen = std::unique_ptr<Screen>(new MainScreen());
}

void Game::loop() {
    if (this->ui.mouseOnClickable) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    this->ui.mouseOnClickable = false;

    // Begin Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Run the current screen loop
    this->currentScreen->loop(this);
    EndDrawing();

    // Handle the change of screen
    if (this->screenNeedsToChange) {
        this->currentScreen.reset();
        this->currentScreen = this->nextScreen;
        this->screenNeedsToChange = false;
    }
}

void Game::changeCurrentScreen(std::shared_ptr<Screen> newScreen) {
    this->screenNeedsToChange = true;
    this->nextScreen = newScreen;
}

Game::~Game() {
}
