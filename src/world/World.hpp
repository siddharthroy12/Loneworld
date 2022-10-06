#ifndef WORLD_HPP
#define WORLD_HPP

#include "../../libs/raylib/src/raylib.h"
#include "./entity/ECS.hpp"
#include "../Game.hpp"
#include "./chunk/Chunk.hpp"
#include <memory>
#include <thread>
#include <unordered_map>
#include <string>
#include "WorldCamera.hpp"

class World {
    public:
    World(Game *context);
    void render();
    void update();
    ~World();
    ECS ecs;

    private:
    std::unordered_map<std::string, std::shared_ptr<Chunk>> loadedChunks;
    Game *context;
    WorldCamera camera;
    void handleChunkLoading();
    void threadProcess();
    bool threadRunning = true;
    std::thread thread;
    int followingEntity = 0;
    bool pointVisible(Vector3 point);
    bool boundingBoxVisible(BoundingBox box);
};

#endif
