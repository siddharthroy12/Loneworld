#ifndef MAIN_SCREEN_HPP
#define MAIN_SCREEN_HPP
#include "Screen.hpp"

class MainScreen : public Screen {
    public:
    MainScreen();
    void loop(Game *context);
    ~MainScreen();
};

#endif
