#pragma once

#include "Entity.hpp"

namespace potEngine {
    class Entity;
    class ISystem {
    public:
        virtual ~ISystem() = default;

        virtual void init() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void shutdown() = 0;

        virtual void addEntity(Entity& entity) = 0;
        virtual void removeEntity(const std::size_t id) = 0;
    };
}