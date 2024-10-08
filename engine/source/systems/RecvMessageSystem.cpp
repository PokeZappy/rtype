#include "RecvMessageSystem.hpp"
#include <iostream>
#include <cmath>
#include <cstring>
#include "PositionComponent.hpp"
#include "PlayerComponent.hpp"
#include "MovementComponent.hpp"
#include "LifeComponent.hpp"
#include "CollisionComponent.hpp"
#include "SpriteComponent.hpp"
#include "ShootComponent.hpp"

namespace potEngine
{
    RecvMessageSystem::RecvMessageSystem(int cliFd, struct sockaddr_in servAddr, socklen_t adLen, size_t id) : _clientFd(cliFd), _addrLen(adLen), _playerId(id), ASystem()
    {
        // _signature.set(AComponent::getID<RenderComponent>(), true);
        eventBus.subscribe(this, &RecvMessageSystem::updateSystem);
    }

    RecvMessageSystem::~RecvMessageSystem() {
    }

    std::tuple<size_t, potEngine::EventType, std::vector<size_t>> RecvMessageSystem::recv_message()
    {
        uint8_t buffer[1024];
        ssize_t recv_len = recvfrom(_clientFd, buffer, sizeof(buffer), 0, (struct sockaddr*)&_addr, &_addrLen);

        if (recv_len < 0 || static_cast<size_t>(recv_len) < sizeof(size_t)) {
            return std::make_tuple(0, potEngine::EventType::UNKNOW, std::vector<size_t>{});
        }

        size_t header;
        std::memcpy(&header, buffer, sizeof(size_t));
        size_t entity_id = header & ((1ULL << (sizeof(size_t) * 8 - 8)) - 1);
        potEngine::EventType event_type = static_cast<potEngine::EventType>(header >> (sizeof(size_t) * 8 - 8));
        std::vector<size_t> params;
        for (size_t i = sizeof(size_t); i + sizeof(size_t) <= static_cast<size_t>(recv_len); i += sizeof(size_t)) {
            size_t param;
            std::memcpy(&param, buffer + i, sizeof(size_t));
            params.push_back(param);
        }
        return std::make_tuple(entity_id, event_type, params);
    }


    std::string assetFinder();

    void RecvMessageSystem::createPlayerEntity(std::vector<size_t> params, size_t entity_id)
    {
        size_t username_length = params[1];
        std::string username;
        for (size_t i = 0; i < username_length; ++i) {
            username += static_cast<char>(params[2 + i]);
        }
        std::vector<size_t> position(params.begin() + 2 + username_length, params.end());

        auto entity = ecsManager.createServerEntity(entity_id);

        sf::Texture playerTexture;
        if (!playerTexture.loadFromFile(assetFinder() + "/sprites/r-typesheet42.gif"))
            std::cout << assetFinder() << std::endl;

        std::shared_ptr<PlayerComponent> playerComponent = std::make_shared<PlayerComponent>(username);
        std::shared_ptr<PositionComponent> positionComponent = std::make_shared<PositionComponent>(position[0], position[1]);
        std::shared_ptr<MovementComponent> movementComponent = std::make_shared<MovementComponent>(1.0f);
        std::shared_ptr<LifeComponent> lifeComponent = std::make_shared<LifeComponent>(3);
        std::shared_ptr<CollisionComponent> collisionComponent = std::make_shared<CollisionComponent>();
        std::shared_ptr<SpriteComponent> spriteComponent = std::make_shared<SpriteComponent>(playerTexture, sf::IntRect(sf::Vector2i(66, 1), sf::Vector2i(33, 17)));
        ecsManager.addComponent(entity, playerComponent);
        ecsManager.addComponent(entity, positionComponent);
        ecsManager.addComponent(entity, movementComponent);
        ecsManager.addComponent(entity, lifeComponent);
        ecsManager.addComponent(entity, collisionComponent);
        ecsManager.addComponent(entity, spriteComponent);

        std::cout << "[CLIENT] New PlayerEntity created {ID}-[" << static_cast<int>(entity_id)
            << "] {username}-[" << username <<  "] {POS}-[" << position[0] << "," << position[1] << "]." << std::endl;
    }

    void RecvMessageSystem::createShootEntity(std::vector<size_t> params, size_t entity_id)
    {

        std::vector<size_t> position(params.begin() + 1, params.end());

        auto entity = ecsManager.createServerEntity(entity_id);

        sf::Texture playerTexture;
        // if (!playerTexture.loadFromFile(assetFinder() + "/sprites/r-typesheet42.gif"))
        //     std::cout << assetFinder() << std::endl;

            std::shared_ptr<PositionComponent> positionComponent = std::make_shared<PositionComponent>(position[0], position[1]);
            std::shared_ptr<MovementComponent> movementComponent = std::make_shared<MovementComponent>(5.0f);
            std::shared_ptr<CollisionComponent> collisionComponent = std::make_shared<CollisionComponent>();
            std::shared_ptr<ShootComponent> shootComponent = std::make_shared<ShootComponent>();

            ecsManager.addComponent(entity, positionComponent);
            ecsManager.addComponent(entity, movementComponent);
            ecsManager.addComponent(entity, collisionComponent);
            ecsManager.addComponent(entity, shootComponent);

        std::cout << "[CLIENT] New ShootEntity created {ID}-[" << static_cast<int>(entity_id)
            << "] {POS}-[" << position[0] << "," << position[1] << "]." << std::endl;
    }

    void RecvMessageSystem::handleCreateEntity(std::vector<size_t> params, size_t entity_id)
    {
        size_t type = params[0];

        if (type == EntityType::PLAYER)
            return RecvMessageSystem::createPlayerEntity(params, entity_id);
        if (type == EntityType::PEW)
            return RecvMessageSystem::createShootEntity(params, entity_id);
    }

    void RecvMessageSystem::updateSystem(std::shared_ptr<BlcEvent> event) {
        // std::cout << "RECEIVE" << std::endl;
        auto [entity_id, event_type, params] = recv_message();
        if (event_type != EventType::UNKNOW) {
            std::cout << "[CLIENT] Received event from server: " << static_cast<int>(event_type) << std::endl;
        }
        if (event_type == EventType::CONNECTION) {
            createPlayerEntity(params, entity_id);
        }
        if (event_type == EventType::DISCONNECT) {
            if (entity_id == _playerId) {
                std::cout << "[CLIENT] Disconnected from server." << std::endl;
                // TODO fermer le client ici.
                return;
            }
            std::cout << "[CLIENT] Client with {ID}-[" << static_cast<int>(entity_id) << "] disconnected from server." << std::endl;
        }
        if (event_type == EventType::MOVE_UP || event_type == EventType::MOVE_DOWN || event_type == EventType::MOVE_LEFT || event_type == EventType::MOVE_RIGHT) {
            auto entity = ecsManager.getEntity(entity_id);
            if (!entity) {
                std::cout << "[CLIENT] {ID}-[" << static_cast<int>(entity_id) << "] not found." << std::endl;
                return;
            }
            std::vector<int> convertedParams(params.begin(), params.end());
            entity->getComponent<potEngine::PositionComponent>()->get()->_position = convertedParams;

            auto player_comp = entity->getComponent<PlayerComponent>();
            std::string username = "";
            if (player_comp)
                username = player_comp->get()->username;

            std::cout << "[CLIENT] Entity {ID}-[" << std::to_string(static_cast<int>(entity_id))
                << "], {username}-[" << username << "], has move to {" << convertedParams[0] << "," << convertedParams[1] << "}" << std::endl;
        }
        if (event_type == EventType::INFORMATION) {
            // ici le joueur recoit les informations de toutes les entities déja présente
            handleCreateEntity(params, entity_id);
        }
    }
}