#ifndef GAME_HPP
#define GAME_HPP
#include "./screens/Screen.hpp"
#include <memory>

class Game {
    public:
        Game();
        void changeCurrentScreen(std::unique_ptr<Screen> newScreen);
        void loop();
        ~Game();
    private:
        std::unique_ptr<Screen> currentScreen;
        std::unique_ptr<Screen> nextScreen;
        bool screenNeedsToChange = false;
};

#endif
