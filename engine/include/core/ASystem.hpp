#pragma once

#include "ISystem.hpp"

namespace potEngine {
    class ASystem : public ISystem {
    public:
        ASystem();
        virtual ~ASystem() = default;

        virtual void update(float deltaTime) = 0;

        // void addEntity(AEntity& entity);
        // void removeEntity(const std::size_t id);

        std::vector<std::shared_ptr<AEntity>> &getEntities();
        std::bitset<64> getSignature() { return (_signature); }
    protected:
        std::vector<std::shared_ptr<AEntity>> _entitiesSystem;
        std::bitset<64> _signature;
    };
}