#ifndef INTRO_SCREEN_HPP
#define INTRO_SCREEN_HPP

#include "Screen.hpp"

class IntroScreen : public Screen {
    public:
    IntroScreen(Game *context);
    void loop();
    ~IntroScreen();
};


#endif
