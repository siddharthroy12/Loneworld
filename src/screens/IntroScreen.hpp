#ifndef INTRO_SCREEN_HPP
#define INTRO_SCREEN_HPP

#include "Screen.hpp"

class IntroScreen : public Screen {
    public:
    IntroScreen();
    void loop(Game *context);
    ~IntroScreen();
};


#endif
