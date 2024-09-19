#pragma once

#include "ISystem.hpp"

namespace potEngine {
    class ASystem : public ISystem {
    public:
        ASystem();
        virtual ~ASystem() = default;

        virtual void update(float deltaTime) = 0;

        void addEntity(Entity& entity) override;
        void removeEntity(const std::size_t id) override;

        std::vector<Entity*> getEntities() const;
    private:
        std::vector<Entity*> _entitiesSystem;
    };
}