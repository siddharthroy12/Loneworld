#ifndef SCREEN_HPP
#define SCREEN_HPP
class Game;
#include "iostream"

class Screen {
    public:
        virtual void loop(Game *context) = 0;
};

#endif
