#ifndef SCREEN_HPP
#define SCREEN_HPP

class Game;
#include "iostream"
#include "../../libs/raylib/src/raylib.h"

class Screen {
    public:
        Screen(Game *context);
        virtual void loop() = 0;
        virtual ~Screen();
    protected:
        Game *context;
};

#endif
