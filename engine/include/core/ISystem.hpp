#pragma once

#include "Entity.hpp"

namespace potEngine {
    class Entity;
    class ISystem {
    public:
        virtual ~ISystem() = default;

        virtual void update(float deltaTime) = 0;
        virtual std::bitset<64> getSignature() = 0;
        virtual std::vector<std::shared_ptr<Entity>> &getEntities() = 0;

        // virtual removeEntity(const std::size_t id) = 0;
    };
}