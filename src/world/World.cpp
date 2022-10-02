#include "World.hpp"
#include "../../libs/raylib/src/raymath.h"
#include "./entity/Human.hpp"
#include "../helper.hpp"
#include <cmath>
#include <memory>
#include <vector>
#include "WorldCamera.hpp"
#include "chunk/Chunk.hpp"
#include "iostream"

// Calculate what chunk a point is in
ChunkPosition worldPositionToChunk(Vector3 position) {
    ChunkPosition chunkPosition = {(int)position.x/CHUNK_SIZE_XZ, (int)position.z/CHUNK_SIZE_XZ};

    // if the position is negative then we have to subtract 1 to get the correct coordinate
    if (position.x < 0) {
        chunkPosition.x -= -1;
    }

    if (position.z < 0) {
        chunkPosition.z -= -1;
    }

    return chunkPosition;
}

World::World(Game *context) {
    std::cout << "World created" << std::endl;
    this->thread = std::thread(&World::threadProcess, this);
    this->context = context;

    // Setup camera
    this->camera =WorldCamera(45.0f, {0, 0, 0}, {1, 1, 1});
    DisableCursor();

    ecs.summon(std::shared_ptr<Entity>(new Human()));
}

void World::render() {
    // Draw UI
    auto chunkPosition = worldPositionToChunk(camera.getPosition());
    DrawText(TextFormat("ChunkX: %d, ChunkZ: %d", chunkPosition.x, chunkPosition.z), 0, 0, 20, BLACK);
    DrawText(TextFormat("X: %f, Y: %f, Z: %f", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z), 0, 20, 20, BLACK);

    this->camera.beginCamera();
    Vector3 front = Vector3Subtract(camera.getLookAt(), camera.getPosition());
    front = Vector3Scale(Vector3Normalize(front), 10);
    front = Vector3Add(camera.getPosition(), front);
    DrawLine3D(front, {front.x+0.5f, front.y, front.z}, RED);
    DrawLine3D(front, {front.x, front.y+0.5f, front.z}, GREEN);
    DrawLine3D(front, {front.x, front.y, front.z+0.5f}, BLUE);

    DrawCube(front, 0.1, 0.1, 0.1, YELLOW);

    // Draw Floor
    DrawGrid(50, 1);

    // Draw Chunks
    for (auto &pair : this->loadedChunks) {
        // Check if the chunk is visible
        if (this->camera.boundingBoxVisible(pair.second.getBoundingbox())) {
            pair.second.draw();
        }
    }

    // Draw entities
    for (auto i : this->ecs.entities()) {
        i.second->draw();
    }
    EndMode3D();
}

void World::update() {

    // Update entities
    for (auto i : this->ecs.entities()) {
        i.second->update();
    }

    // Set camera to following entity
    if (this->followingEntity > -1) {
        auto entity = this->ecs.getEntityById(this->followingEntity);
        camera.setPosition(Vector3Add(entity->position, entity->head));
        camera.setLookAt(entity->lookat);
    }
}

void World::handleChunkLoading() {
    // Get the camera's chunk position
    ChunkPosition cameraChunkPosition = worldPositionToChunk(camera.getPosition());

    // Unload chunks that are out of render distance
    std::vector<std::string> chunksToUnload;

    for (auto &pair : this->loadedChunks) {
        auto outOfRangeX = std::abs((pair.second.position.x - cameraChunkPosition.x)) > this->context->settings.renderDistance;
        auto outOfRangeZ = std::abs((pair.second.position.z - cameraChunkPosition.z)) > this->context->settings.renderDistance;

        if (outOfRangeZ || outOfRangeX) {
            chunksToUnload.push_back(pair.first);
        }
    }

    for(auto &position : chunksToUnload) {
        this->loadedChunks.erase(position);
    }

    // Load chunk in render distance if not loaded
    ChunkPosition startChunkPosition = {
        cameraChunkPosition.x - (int)this->context->settings.renderDistance,
        cameraChunkPosition.z - (int)this->context->settings.renderDistance,
    };

    ChunkPosition endChunkPosition = {
        cameraChunkPosition.x + (int)this->context->settings.renderDistance,
        cameraChunkPosition.z + (int)this->context->settings.renderDistance,
    };

    for (int x = startChunkPosition.x; x < endChunkPosition.x; x++) {
        for (int z = startChunkPosition.z; z < endChunkPosition.z; z++) {
            ChunkPosition chunkPosition = ChunkPosition(x, z);
            auto chunkPositionString = chunkPosition.stringify();
            // If chunk is not loaded, load the chunk
            if (this->loadedChunks.find(chunkPositionString) == this->loadedChunks.end()) {
                this->loadedChunks.insert(std::make_pair(chunkPositionString, Chunk(12, chunkPosition)));
            }
        }
    }
}

void World::threadProcess() {
    std::cout << "Thread started" << std::endl;
    while(this->threadRunning) {
        handleChunkLoading();
    }
    std::cout << "Thread ended" << std::endl;
}

bool World::pointVisible(Vector3 point) {
    Vector2 screenCoord = this->camera.worldToScreen(point);

    return (screenCoord.x > 0 &&
            screenCoord.x < getWindowWidth() &&
            screenCoord.y > 0 &&
            screenCoord.y < getWindowHeight());
}

World::~World() {
    this->threadRunning = false;
    this->thread.join();
}
