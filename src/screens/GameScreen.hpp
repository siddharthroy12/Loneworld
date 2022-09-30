#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include "../world/World.hpp"
#include "Screen.hpp"

class GameScreen : public Screen {
    public:
        GameScreen();
        void loop(Game *context);
        ~GameScreen();
    private:
        World world;
};

#endif
