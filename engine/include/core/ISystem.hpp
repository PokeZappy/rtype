#pragma once

#include "AEntity.hpp"

namespace potEngine {
    class AEntity;
    class ISystem {
    public:
        virtual ~ISystem() = default;

        virtual void update(float deltaTime, std::vector<std::shared_ptr<AEntity>> entities) = 0;

        // virtual removeEntity(const std::size_t id) = 0;
    };
}