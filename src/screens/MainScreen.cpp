#include "MainScreen.hpp"
#include "../ui/button.hpp"
#include "../helper.hpp"
#include "GameScreen.hpp"
#include <memory>

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 50

MainScreen::MainScreen() {
    std::cout << "Main Screen enter" << std::endl;
}

void MainScreen::loop(Game *context) {
    // Get the center of screen
    Vector2 centerOfScreen;
    centerOfScreen.x = getWindowWidth() / 2.0;
    centerOfScreen.y = getWindowHeight() / 2.0;

    // Draw UI

    // Title
    Vector2 titleTextSize = MeasureTextEx(context->asset.font, PROJECT_NAME, 40, 0);
    Vector2 titlePosition;
    titlePosition.x = centerOfScreen.x - (titleTextSize.x/2.0);
    titlePosition.y = 100;
    DrawTextEx(context->asset.font, PROJECT_NAME, titlePosition, 40, 0, BLACK);


    // Start button
    Vector2 buttonPosition;
    buttonPosition.x = centerOfScreen.x - (BUTTON_WIDTH/2.0);
    buttonPosition.y = 250;

    Vector2 buttonSize;
    buttonSize.x = BUTTON_WIDTH;
    buttonSize.y = BUTTON_HEIGHT;

    if (button(context, "Start", buttonPosition, buttonSize)) {
        std::cout << "Start Clicked" << std::endl;
        context->changeCurrentScreen(std::shared_ptr<Screen>(new GameScreen()));
    }
}

MainScreen::~MainScreen() {
    std::cout << "Main Screen leaves" << std::endl;
}
