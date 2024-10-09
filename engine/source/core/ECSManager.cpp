#include "ECSManager.hpp"
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "RenderSystem.hpp"
#include "SpriteComponent.hpp"
#include "WindowComponent.hpp"

#include <algorithm>
#include <iostream>

namespace potEngine {

    ECSManager::ECSManager()
    {
        _entityCounter = 1;
    }

    ECSManager::~ECSManager() {}

        std::shared_ptr<AEntity> ECSManager::createServerEntity(size_t serverId)
        {
            auto entity = std::make_shared<AEntity>(_entityCounter);
            _entities.push_back(entity);
            _serverToClientId[serverId] = _entityCounter;
            _entityCounter++;
            return entity;
        }

        std::shared_ptr<AEntity> ECSManager::createEntity()
        {
            auto entity = std::make_shared<AEntity>(_entityCounter);
            _entities.push_back(entity);
            _entityCounter++;
            return entity;
        }

    // std::shared_ptr<AEntity> ECSManager::createEntity(size_t id)
    // {
    //     auto entity = std::make_shared<AEntity>(id);
    //     _entities.push_back(entity);
    //     return entity;
    // }

    std::shared_ptr<AEntity> ECSManager::createSpriteEntity(const std::string &texturePath) {
        auto entity = std::make_shared<AEntity>(32);

        // sf::Sprite sprite(texture);
        // sprite.setPosition(100, 100);
        std::shared_ptr<potEngine::SpriteComponent> spriteComponent = std::make_shared<SpriteComponent>(texturePath);
        addComponent<SpriteComponent>(entity, spriteComponent);

        _entities.push_back(entity);
        return (entity);
    }

    std::shared_ptr<AEntity> ECSManager::createWindowEntity() {
        auto entity = std::make_shared<AEntity>(_entityCounter);
        _entityCounter++;
        std::shared_ptr<potEngine::WindowComponent> windowComponent = std::make_shared<potEngine::WindowComponent>();

        addComponent<WindowComponent>(entity, windowComponent);

        _entities.push_back(entity);
        return (entity);
    }

    //    void ECSManager::addEntity(std::shared_ptr<AEntity> entity)
    //    {
    //        _entities.push_back(entity);
    //        EntitySignatureChanged(entity);
    //    }

    void ECSManager::removeEntity(const std::size_t id)
    {
            auto it = std::find_if(_entities.begin(), _entities.end(), [id](const std::shared_ptr<AEntity> entityPtr) {
                return entityPtr->getID() == id;
            });
            if (it != _entities.end()) {
                auto entity = *it;

                EraseEntitySystem(entity);

                _entities.erase(it);
                // std::cout << "entité supprimée, tableau entity size : " << _entities.size() << std::endl;
            }
    }

    void ECSManager::EraseEntitySystem(std::shared_ptr<AEntity> entity) {
        for (auto const &system : _systems) {
            auto &systemEntities = system->getEntities();
            auto it = std::find(systemEntities.begin(), systemEntities.end(), entity);

            if (it != systemEntities.end()) {
                // std::cout << "je remove l'entité du système" << std::endl;
                systemEntities.erase(it);
            }
        }
    }

    void ECSManager::EntitySignatureChanged(std::shared_ptr<AEntity> entity) {
        auto const &entitySignature = entity->getSignature();

        for (auto const &system: _systems) {
            auto const &systemSignature = system->getSignature();
            auto &systemEntities = system->getEntities();
            bool doesSignaturesMatch = false;

            if (system->isInclusive()) {
                doesSignaturesMatch = (entitySignature & systemSignature).any();
            } else {
                doesSignaturesMatch = (entitySignature & systemSignature) == systemSignature;
            }

            if (doesSignaturesMatch)
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

    void ECSManager::update(float deltaTime)
    {
        auto handler = eventBus.getHandler();
        while (handler != std::pair<std::shared_ptr<IEvent>, std::shared_ptr<HandlerList>>(nullptr, nullptr)) {
            // std::cout << "[ECSManager] Event received" << std::endl;
            for (auto event : *handler.second) {
                event->exec(handler.first);
            }
            handler = eventBus.getHandler();
        }
    }

    void ECSManager::shutdown()
    {

    }

    std::vector<std::shared_ptr<AEntity>> ECSManager::getEntities() const {
        return _entities;
    }

    std::shared_ptr<AEntity> ECSManager::getEntity(size_t entity_id) {
        size_t newId = getClientIdFromServerId(entity_id);
        for (const auto& entity : _entities) {
            if (entity->getID() == newId) {
                return entity;
            }
        }
        return nullptr;
    }

    size_t ECSManager::getClientIdFromServerId(size_t serverId) {
        if (_serverToClientId.find(serverId) != _serverToClientId.end()) {
            return (_serverToClientId[serverId]);
        } else {
            return (serverId);
        }
    }
}