#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include "../world/World.hpp"
#include "Screen.hpp"
#include <memory>

class GameScreen : public Screen {
    public:
        GameScreen(Game *context);
        void loop();
        ~GameScreen();
    private:
        std::unique_ptr<World> world;
};

#endif
