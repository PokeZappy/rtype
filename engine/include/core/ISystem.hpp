#pragma once

#include "AEntity.hpp"

namespace potEngine {
    class AEntity;
    /*!
    * @brief The ISystem class is an interface for all systems in the game engine.
    */
    class ISystem {
    public:
        virtual ~ISystem() = default;

        virtual void update(float deltaTime) = 0;
        virtual std::bitset<64> getSignature() = 0;
        virtual std::vector<std::shared_ptr<AEntity>> &getEntities() = 0;
        virtual bool isInclusive() = 0;

        // virtual removeEntity(const std::size_t id) = 0;
    };
}