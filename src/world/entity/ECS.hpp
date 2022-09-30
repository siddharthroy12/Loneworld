#ifndef ECS_HPP
#define ECS_HPP

#include "Entity.hpp"
#include <unordered_map>
#include <memory>

class ECS {
    public:
    ECS();
    ~ECS();
    void summon(std::shared_ptr<Entity> entity);
    void kill(int eid);
    std::shared_ptr<Entity> getEntityById(int eid);
    const std::unordered_map<int, std::shared_ptr<Entity>>& entities() const;
    private:
    std::unordered_map<int, std::shared_ptr<Entity>> _entities;
};

#endif
