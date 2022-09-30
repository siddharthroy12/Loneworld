#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "Entity.hpp"

#define HEIGHT 1.8
#define WIDTH 0.6

class Human : public Entity {
    public:
    Human();
    void draw();
    void update();
    ~Human();
};

#endif
