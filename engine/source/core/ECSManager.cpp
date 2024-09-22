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
   }

   void ECSManager::removeEntity(const std::size_t id)
   {
        auto it = std::find_if(_entities.begin(), _entities.end(), [id](const std::shared_ptr<Entity>& entityPtr) {
            return entityPtr->getID() == id;
        });
        if (it != _entities.end()) {
            _entities.erase(it);
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
            system->update(deltaTime, _entities);
        }
   }

   void ECSManager::shutdown()
   {

   }
}