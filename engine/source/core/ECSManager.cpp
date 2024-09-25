#include "ECSManager.hpp"
#include "ASystem.hpp"
#include "Entity.hpp"
#include "RenderSystem.hpp"

#include <algorithm>
#include <iostream>

namespace potEngine {

   ECSManager::ECSManager(): _entityCounter() {}
   ECSManager::~ECSManager() {}

   void ECSManager::addEntity(std::shared_ptr<Entity> entity)
   {
       _entities.push_back(entity);
       EntitySignatureChanged(entity);
   }

   void ECSManager::removeEntity(const std::size_t id)
   {
        auto it = std::find_if(_entities.begin(), _entities.end(), [id](const std::shared_ptr<Entity>& entityPtr) {
            return entityPtr->getID() == id;
        });
        if (it != _entities.end()) {
            auto entity = *it;

            EraseEntitySystem(entity);

            _entities.erase(it);
        }
   }

   void ECSManager::EraseEntitySystem(std::shared_ptr<Entity> entity) {
    for (auto const &system : _systems) {
        auto systemEntities = system->getEntities();
        auto it = std::find(systemEntities.begin(), systemEntities.end(), entity);

        if (it != systemEntities.end()) {
            systemEntities.erase(it);
        }
    }
   }

   void ECSManager::EntitySignatureChanged(std::shared_ptr<Entity> entity) {
    auto const &entitySignature = entity->getSignature();
    // std::cout << entitySignature << std::endl;

    for (auto const &system: _systems) {
        auto const &systemSignature = system->getSignature();
        // std::cout << "system signature : " << systemSignature << std::endl;
        auto &systemEntities = system->getEntities();

        if ((entitySignature & systemSignature) == systemSignature)
        {
            auto it = std::find(systemEntities.begin(), systemEntities.end(), entity);

            if (it == systemEntities.end()) {
                systemEntities.push_back(entity);
            }
        }
        else
        {
            auto it = std::find(systemEntities.begin(), systemEntities.end(), entity);

            if (it != systemEntities.end()) {
                systemEntities.erase(it);
            }
        }

    }
   }

   void ECSManager::init()
   {
   }

   void ECSManager::update(float deltaTime)
   {
        for (auto& system : _systems) {
            if (!system) {
                continue;
            }
            system->update(deltaTime);
        }
   }

   void ECSManager::shutdown()
   {

   }
}