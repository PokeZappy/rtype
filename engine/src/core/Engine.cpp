#include "Engine.hpp"
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "RenderSystem.hpp"
#include "SpriteComponent.hpp"
#include "WindowComponent.hpp"

#include <algorithm>
#include <iostream>

namespace potEngine {

    /*!
    * @brief Construct a new Engine object.
    *
    * This constructor initializes the Engine and sets the entity counter to 1.
    */
    Engine::Engine()
    {
        _entityCounter = 1;
    }

    /*!
    * @brief Destroy the Engine object.
    */
    Engine::~Engine() {}

        /*!
        * @brief Create a new server entity.
        *
        * @param serverId The server ID of the entity.
        * @return A shared pointer to the created entity.
        */
        std::shared_ptr<AEntity> Engine::createServerEntity(size_t serverId)
        {
            auto entity = std::make_shared<AEntity>(_entityCounter);
            _entities.push_back(entity);
            _serverToClientId[serverId] = _entityCounter;
            _entityCounter++;
            return entity;
        }

        /*!
        * @brief Create a new entity.
        *
        * @return A shared pointer to the created entity.
        */
        std::shared_ptr<AEntity> Engine::createEntity()
        {
            auto entity = std::make_shared<AEntity>(_entityCounter);
            _entities.push_back(entity);
            _entityCounter++;
            return entity;
        }

    /*!
    * @brief Create a new sprite entity.
    *
    * @param texturePath The path to the texture.
    * @return A shared pointer to the created sprite entity.
    */
    std::shared_ptr<AEntity> Engine::createSpriteEntity(const std::string &texturePath) {
        auto entity = std::make_shared<AEntity>(32);

        std::shared_ptr<potEngine::SpriteComponent> spriteComponent = std::make_shared<SpriteComponent>(texturePath);
        addComponent<SpriteComponent>(entity, spriteComponent);

        _entities.push_back(entity);
        return (entity);
    }

    /*!
    * @brief Create a new window entity.
    *
    * @return A shared pointer to the created window entity.
    */
    std::shared_ptr<AEntity> Engine::createWindowEntity() {
        auto entity = std::make_shared<AEntity>(_entityCounter);
        _entityCounter++;
        std::shared_ptr<potEngine::WindowComponent> windowComponent = std::make_shared<potEngine::WindowComponent>();

        addComponent<WindowComponent>(entity, windowComponent);

        _entities.push_back(entity);
        return (entity);
    }

    /*!
    * @brief Remove an entity by its ID.
    *
    * @param id The ID of the entity to remove.
    */
    void Engine::removeEntity(const std::size_t id)
    {
        std::size_t newId = getClientIdFromServerId(id);
        auto it = std::find_if(_entities.begin(), _entities.end(), [newId](const std::shared_ptr<AEntity> entityPtr) {
            return entityPtr->getID() == newId;
        });
        if (it != _entities.end()) {
            auto entity = *it;

            EraseEntitySystem(entity);

            _entities.erase(it);
            // std::cout << "entité supprimée, tableau entity size : " << _entities.size() << std::endl;
        }
    }

    /*!
    * @brief Remove an entity by its shared pointer.
    *
    * @param entity The shared pointer to the entity to remove.
    */
    void Engine::removeEntity(std::shared_ptr<AEntity> entity)
    {
        auto it = std::find(_entities.begin(), _entities.end(), entity);
        if (it != _entities.end()) {
            EraseEntitySystem(entity);

            _entities.erase(it);
            // std::cout << "entité supprimée, tableau entity size : " << _entities.size() << std::endl;
        }
    }

    /*!
    * @brief Erase an entity from all systems.
    *
    * @param entity The shared pointer to the entity to erase.
    */
    void Engine::EraseEntitySystem(std::shared_ptr<AEntity> entity) {
        for (auto const &system : _systems) {
            auto &systemEntities = system->getEntities();
            auto it = std::find(systemEntities.begin(), systemEntities.end(), entity);

            if (it != systemEntities.end()) {
                // std::cout << "je remove l'entité du système" << std::endl;
                systemEntities.erase(it);
            }
        }
    }

    /*!
    * @brief Update the entity signature in all systems.
    *
    * @param entity The shared pointer to the entity whose signature changed.
    */
    void Engine::EntitySignatureChanged(std::shared_ptr<AEntity> entity) {
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

            if (doesSignaturesMatch) {
                auto it = std::find(systemEntities.begin(), systemEntities.end(), entity);

                if (it == systemEntities.end()) {
                    systemEntities.push_back(entity);
                }
            } else {
                auto it = std::find(systemEntities.begin(), systemEntities.end(), entity);

                if (it != systemEntities.end()) {
                    systemEntities.erase(it);
                }
            }

        }
    }

    /*!
    * @brief Update the engine.
    *
    * This function processes all events in the event bus.
    */
    void Engine::update()
    {
        auto handler = _eventBus.getHandler();
        while (handler != std::pair<std::shared_ptr<IEvent>, std::shared_ptr<HandlerList>>(nullptr, nullptr)) {
            for (auto event : *handler.second) {
                event->exec(handler.first);
            }
            handler = _eventBus.getHandler();
        }
    }

    /*!
    * @brief Shutdown the engine.
    *
    * Shutdown the engine ????
    */
    void Engine::shutdown()
    {
        // TODO: pourquoi faire ????
    }

    /*!
    * @brief Get all entities.
    *
    * @return A vector of shared pointers to all entities.
    */
    std::vector<std::shared_ptr<AEntity>> Engine::getEntities() const {
        return _entities;
    }

    /*!
    * @brief Get an entity by its ID.
    *
    * @param entity_id The ID of the entity to get.
    * @return A shared pointer to the entity, or nullptr if not found.
    */
    std::shared_ptr<AEntity> Engine::getEntity(size_t entity_id) {
        size_t newId = getClientIdFromServerId(entity_id);
        for (const auto& entity : _entities) {
            if (entity->getID() == newId) {
                return entity;
            }
        }
        return nullptr;
    }

    /*!
    * @brief Get the client ID from the server ID.
    *
    * @param serverId The server ID.
    * @return The client ID.
    */
    size_t Engine::getClientIdFromServerId(size_t serverId) {
        if (_serverToClientId.find(serverId) != _serverToClientId.end()) {
            return (_serverToClientId[serverId]);
        } else {
            return (serverId);
        }
    }
}