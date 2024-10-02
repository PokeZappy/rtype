#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <algorithm>

#include "AEntity.hpp"
#include "ASystem.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"

namespace potEngine {
    class ECSManager {
    public:
        ECSManager();
        ~ECSManager();

        std::shared_ptr<AEntity> createEntity();

        // void addEntity(std::shared_ptr<AEntity> entity);
        template <typename T>
        void addComponent(std::shared_ptr<AEntity> entity, std::shared_ptr<T> component);

        void removeEntity(const std::size_t id);

        template <typename T>
        void registerSystem();
        template <typename T>
        void unregisterSystem();

        void EntitySignatureChanged(std::shared_ptr<AEntity> entity);
        void EraseEntitySystem(std::shared_ptr<AEntity> entity);

        void init();
        void update(float deltaTime);
        void shutdown();

        StartEvent getStartEvent() {
            return _startEvent;
        }

    private:
        std::size_t _entityCounter;
        StartEvent _startEvent;
        std::vector<std::shared_ptr<ISystem>> _systems;
        std::vector<std::shared_ptr<AEntity>> _entities;

    };

    template <typename T>
    void ECSManager::registerSystem()
    {
        static_assert(std::is_base_of<ISystem, T>::value, "T must derive from ISystem");
        _systems.push_back(std::make_shared<T>());
    }

    template <typename T>
    void ECSManager::unregisterSystem()
    {
        _systems.erase(std::remove_if(_systems.begin(), _systems.end(), [](const std::shared_ptr<ASystem>& system) {
            return typeid(T) == typeid(*system);
        }), _systems.end());
    }

    template <typename T>
    void ECSManager::addComponent(std::shared_ptr<AEntity> entity, std::shared_ptr<T> component) {
        entity->addComponent<T>(component);
        EntitySignatureChanged(entity);
    }
}