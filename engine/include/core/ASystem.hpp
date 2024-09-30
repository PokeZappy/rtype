#pragma once

#include "ISystem.hpp"

namespace potEngine {
    class ASystem : public ISystem {
    public:
        ASystem();
        virtual ~ASystem() = default;

        virtual void update(float deltaTime) = 0;

        // void addEntity(Entity& entity);
        // void removeEntity(const std::size_t id);

        std::vector<std::shared_ptr<Entity>> &getEntities();
        std::bitset<64> getSignature() { return (_signature); }
    protected:
        std::vector<std::shared_ptr<Entity>> _entitiesSystem;
        std::bitset<64> _signature;
    };
}