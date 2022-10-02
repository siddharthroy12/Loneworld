#ifndef GAME_HPP
#define GAME_HPP
#include "./screens/Screen.hpp"
#include <memory>
#include "../libs/raylib/src/raylib.h"

struct Asset {
    Font font;
};

struct UI {
    bool mouseOnClickable = false;
};

struct Settings {
    unsigned int renderDistance = 4;
};

class Game {
    public:
        Game();
        Asset asset;
        UI ui;
        void changeCurrentScreen(std::shared_ptr<Screen> newScreen);
        Settings settings;
        void loop();
        ~Game();
    private:
        std::shared_ptr<Screen> currentScreen;
        std::shared_ptr<Screen> nextScreen;
        bool screenNeedsToChange = false;
};

#endif
