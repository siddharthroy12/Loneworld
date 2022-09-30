#include "World.hpp"
#include "../../libs/raylib/src/raymath.h"
#include "./entity/Human.hpp"
#include <memory>
#include "iostream"



World::World() {
    std::cout << "World created" << std::endl;
    // Setup camera
    camera.fovy = 45.0f;
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.target = { 0.0f, 0.0f, 0.0f} ;
    camera.position = { 10.0f, 10.0f, 10.0f };
    camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_FREE);
    DisableCursor();

    ecs.summon(std::shared_ptr<Entity>(new Human()));
}

void World::render() {
    BeginMode3D(this->camera);
    DrawGrid(50, 1);
    // Draw entities
    for (auto i : this->ecs.entities()) {
        i.second->draw();
    }
    EndMode3D();
}

void World::update() {
    // Update camera
    //updateLookAtVectorFromMouse(camera.position, &camera.target);
    if (this->selectedEnitityID > -1) {
        auto entity = this->ecs.getEntityById(this->selectedEnitityID);
        camera.position = Vector3Add(entity->position, entity->head);
        camera.target = entity->lookat;
    }

    // Update entities
    for (auto i : this->ecs.entities()) {
        i.second->update();
    }
}
World::~World() {
}
