#pragma once

#include "ISystem.hpp"

namespace potEngine {
    class ASystem : public ISystem {
    public:
        ASystem();
        virtual ~ASystem() = default;

        virtual void update(float deltaTime, std::vector<std::shared_ptr<AEntity>> entities) = 0;

        // void addEntity(AEntity& entity);
        // void removeEntity(const std::size_t id);

        std::vector<std::shared_ptr<AEntity>> getEntities() const;
    private:
        std::vector<std::shared_ptr<AEntity>> _entitiesSystem;
    };
}