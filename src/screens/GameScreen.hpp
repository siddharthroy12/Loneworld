#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include "Screen.hpp"

class GameScreen : public Screen {
    public:
        GameScreen();
        void loop(Game *context);
        ~GameScreen();
};

#endif
