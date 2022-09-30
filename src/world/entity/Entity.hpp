#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../../../libs/raylib/src/raylib.h"
#include "../../../libs/raylib/src/raymath.h"
#include "string"

class Entity {
    public:
        Vector3 lookat; // Not relative to position
        Vector3 position;
        Vector3 velocity;
        Vector3 head; // Relative to position
        Vector3 hitbox; // Dimension of hitbox
        std::string identifier;
        virtual void draw() = 0;
        virtual void update() = 0;
        void _update();
        virtual ~Entity() {};
};

#endif
