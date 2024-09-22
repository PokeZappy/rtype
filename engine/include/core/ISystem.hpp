#pragma once

#include "Entity.hpp"

namespace potEngine {
    class Entity;
    class ISystem {
    public:
        virtual ~ISystem() = default;

        virtual void update(float deltaTime, std::vector<std::shared_ptr<Entity>> entities) = 0;

        // virtual removeEntity(const std::size_t id) = 0;
    };
}