#ifndef SCREEN_HPP
#define SCREEN_HPP

class Game;
#include "iostream"
#include "../../libs/raylib/src/raylib.h"

class Screen {
    public:
        virtual void loop(Game *context) = 0;
        virtual ~Screen() {}
};

#endif
