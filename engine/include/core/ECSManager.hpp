#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "Entity.hpp"
#include "ISystem.hpp"

namespace potEngine {
    class ECSManager {
    public:
        ECSManager();
        ~ECSManager();

        Entity& createEntity();
        void removeEntity(const std::size_t id);

        template <typename T>
        void registerSystem();
        template <typename T>
        void unregisterSystem();

        void init();
        void update(float deltaTime);
        void shutdown();

    private:
        std::size_t _entityCounter;
        std::unordered_map<std::type_index, std::unique_ptr<ISystem>> _systems;
        std::vector<Entity> _entities;
    };
}