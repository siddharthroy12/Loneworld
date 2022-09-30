#ifndef WORLD_HPP
#define WORLD_HPP

#include "../../libs/raylib/src/raylib.h"
#include "./entity/ECS.hpp"

enum class CameraViewMode { FIRST_PERSON, THIRD_PERSON, THIRD_PERSON_FRONT };

class World {
    public:
    World();
    void render();
    void update();
    ~World();
    ECS ecs;

    private:
    Camera camera;
    CameraViewMode cameraMode;
    int selectedEnitityID = 0;
};

#endif
