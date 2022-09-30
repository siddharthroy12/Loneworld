#include "ECS.hpp"
#include "iostream"

int getNextEID() {
    static int current = 0;
    int result = current;
    current++;
    return result;
}

ECS::ECS() {
    std::cout << "ECS Created" << std::endl;
}

void ECS::summon(std::shared_ptr<Entity> entity) {
    this->_entities[getNextEID()] = entity;
}
std::shared_ptr<Entity> ECS::getEntityById(int eid){
    return this->_entities[eid];
}

const std::unordered_map<int, std::shared_ptr<Entity>>& ECS::entities() const {
    return this->_entities;
}

void ECS::kill(int eid) {
    this->_entities.erase(eid);
}

ECS::~ECS() {}
