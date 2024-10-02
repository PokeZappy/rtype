#include "ECSManager.hpp"
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "RenderSystem.hpp"

#include <algorithm>
#include <iostream>

namespace potEngine {

   ECSManager::ECSManager(): _entityCounter()
   {
   }

   ECSManager::~ECSManager() {}

    std::shared_ptr<AEntity> ECSManager::createEntity()
    {
        auto entity = std::make_shared<AEntity>(_entityCounter++);
        _entities.push_back(entity);
        return entity;
    }

//    void ECSManager::addEntity(std::shared_ptr<AEntity> entity)
//    {
//        _entities.push_back(entity);
//        EntitySignatureChanged(entity);
//    }

   void ECSManager::removeEntity(const std::size_t id)
   {
        auto it = std::find_if(_entities.begin(), _entities.end(), [id](const std::shared_ptr<AEntity>& entityPtr) {
            return entityPtr->getID() == id;
        });
        if (it != _entities.end()) {
            auto entity = *it;

            EraseEntitySystem(entity);

            _entities.erase(it);
        }
   }

   void ECSManager::EraseEntitySystem(std::shared_ptr<AEntity> entity) {
    for (auto const &system : _systems) {
        auto systemEntities = system->getEntities();
        auto it = std::find(systemEntities.begin(), systemEntities.end(), entity);

        if (it != systemEntities.end()) {
            systemEntities.erase(it);
        }
    }
   }

   void ECSManager::EntitySignatureChanged(std::shared_ptr<AEntity> entity) {
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
        eventBus.publish(std::make_shared<StartEvent>(_startEvent));
   }

   void ECSManager::update(float deltaTime)
   {
        auto handler = eventBus.getHandler();
        while (handler != std::pair<std::shared_ptr<IEvent>, std::shared_ptr<HandlerList>>(nullptr, nullptr)) {
            std::cout << "Event received" << std::endl;
            for (auto event : *handler.second) {
                event->exec(handler.first);
            }
            handler = eventBus.getHandler();
        }
   }

   void ECSManager::shutdown()
   {

   }
}