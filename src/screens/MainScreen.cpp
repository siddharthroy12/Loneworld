#include "MainScreen.hpp"
#include "../../libs/raylib/src/raylib.h"
#include "iostream"

MainScreen::MainScreen() {
}

void MainScreen::loop(Game *context) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Main Screen", 0, 0, 25, BLACK);
    EndDrawing();
}

MainScreen::~MainScreen() {
}
