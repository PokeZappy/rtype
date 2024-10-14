/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** network.cpp
*/

#include "client_config.hpp"

void RType::Client::send_message(size_t entity_id, potEngine::EventType action, const std::vector<size_t>& params, size_t maxP, int fd)
{
    const size_t EVENT_TYPE_BITS = 8;
    size_t packet_size = sizeof(size_t) + params.size() * sizeof(size_t);
    std::vector<uint8_t> packet(packet_size);

    size_t header = entity_id;
    header |= (static_cast<size_t>(action) << (sizeof(size_t) * 8 - EVENT_TYPE_BITS));
    std::memcpy(packet.data(), &header, sizeof(size_t));
    for (size_t i = 0; i < params.size(); ++i) {
        std::memcpy(packet.data() + sizeof(size_t) + i * sizeof(size_t), &params[i], sizeof(size_t));
    }
    sendto(fd, packet.data(), packet.size(), 0, (const struct sockaddr*)&_addr, _addr_len);
}

std::tuple<size_t, potEngine::EventType, std::vector<size_t>> RType::Client::recv_message()
{
    uint8_t buffer[1024];
    ssize_t recv_len = recvfrom(client_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&_addr, &_addr_len);

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

void RType::Client::createPlayerEntity(std::vector<size_t> params, size_t entity_id)
{
    size_t username_length = params[1];
    std::string username;
    for (size_t i = 0; i < username_length; ++i) {
        username += static_cast<char>(params[2 + i]);
    }
    std::vector<size_t> position(params.begin() + 2 + username_length, params.end());

    auto entity = potEngine::engine.createServerEntity(entity_id);

    const std::string &texturePath = assetFinder() + "/sprites/r-typesheet42.gif";

    std::shared_ptr<potEngine::PlayerComponent> playerComponent = std::make_shared<potEngine::PlayerComponent>(username);
    std::shared_ptr<potEngine::PositionComponent> positionComponent = std::make_shared<potEngine::PositionComponent>(position[0], position[1]);
    std::shared_ptr<potEngine::MovementComponent> movementComponent = std::make_shared<potEngine::MovementComponent>(1.0f);
    std::shared_ptr<potEngine::LifeComponent> lifeComponent = std::make_shared<potEngine::LifeComponent>(3);
    std::shared_ptr<potEngine::CollisionComponent> collisionComponent = std::make_shared<potEngine::CollisionComponent>();
    std::shared_ptr<potEngine::SpriteComponent> spriteComponent = std::make_shared<potEngine::SpriteComponent>(texturePath, sf::IntRect(sf::Vector2i(66, 1), sf::Vector2i(33, 17)));
    potEngine::engine.addComponent(entity, playerComponent);
    potEngine::engine.addComponent(entity, positionComponent);
    potEngine::engine.addComponent(entity, movementComponent);
    potEngine::engine.addComponent(entity, lifeComponent);
    potEngine::engine.addComponent(entity, collisionComponent);
    potEngine::engine.addComponent(entity, spriteComponent);
}

void RType::Client::createShootEntity(std::vector<size_t> params, size_t entity_id)
{
    std::vector<size_t> position(params.begin() + 1, params.end());

    auto entity = potEngine::engine.createServerEntity(entity_id);


    std::shared_ptr<potEngine::PositionComponent> positionComponent = std::make_shared<potEngine::PositionComponent>(position[0], position[1]);
    std::shared_ptr<potEngine::MovementComponent> movementComponent = std::make_shared<potEngine::MovementComponent>(1.0f);
    std::shared_ptr<potEngine::CollisionComponent> collisionComponent = std::make_shared<potEngine::CollisionComponent>();
    std::shared_ptr<potEngine::ShootComponent> shootComponent = std::make_shared<potEngine::ShootComponent>();

    const std::string &texturePath = assetFinder() + "/sprites/r-typesheet1.gif";
    std::shared_ptr<potEngine::SpriteComponent> spriteComponent = std::make_shared<potEngine::SpriteComponent>(texturePath, sf::IntRect(sf::Vector2i(249, 89), sf::Vector2i(16, 6)));

    potEngine::engine.addComponent(entity, positionComponent);
    potEngine::engine.addComponent(entity, movementComponent);
    potEngine::engine.addComponent(entity, collisionComponent);
    potEngine::engine.addComponent(entity, shootComponent);
    potEngine::engine.addComponent(entity, spriteComponent);

    std::cout << "[CLIENT] New ShootEntity created {ID}-[" << static_cast<int>(entity_id)
        << "] {POS}-[" << position[0] << "," << position[1] << "]." << std::endl;
}

void RType::Client::handleCreateEntity(std::vector<size_t> params, size_t entity_id)
{
    size_t type = params[0];

    if (type == potEngine::EntityType::PLAYER)
        return createPlayerEntity(params, entity_id);
    if (type == potEngine::EntityType::PEW)
        return createShootEntity(params, entity_id);
}

void RType::Client::handle_message()
{
    auto [entity_id, event_type, params] = recv_message();

    if (event_type == potEngine::EventType::CONNECTION) {
        createPlayerEntity(params, entity_id);
    }
    if (event_type == potEngine::EventType::DISCONNECT) {
        if (entity_id == player_id) {
            std::cout << "[CLIENT] Disconnected from server." << std::endl;
            return;
        }
    }
    if (event_type == potEngine::MOVE_UP || event_type == potEngine::MOVE_DOWN || event_type == potEngine::MOVE_RIGHT || event_type == potEngine::MOVE_LEFT) {
        auto entity = potEngine::engine.getEntity(entity_id);
        if (!entity)
            return;

        auto movementComponent = entity->getComponent<potEngine::MovementComponent>();
        auto positionComponent = entity->getComponent<potEngine::PositionComponent>();
        if (!movementComponent || !positionComponent)
            return;

        std::vector<int> convertedParams(params.begin(), params.end());
        entity->getComponent<potEngine::PositionComponent>()->get()->_position = convertedParams;
        if (event_type == potEngine::MOVE_UP || event_type == potEngine::MOVE_DOWN) {
            movementComponent->get()->moveDirectionY = event_type;
        } else {
            movementComponent->get()->moveDirectionX = event_type;
        }
    }
    if (event_type == potEngine::MOVE_X_STOP || event_type == potEngine::MOVE_Y_STOP) {
        auto entity = potEngine::engine.getEntity(entity_id);
        if (!entity)
            return;

        auto movementComponent = entity->getComponent<potEngine::MovementComponent>();
        if (!movementComponent)
            return;

        if (event_type == potEngine::MOVE_X_STOP) {
            movementComponent->get()->moveDirectionX = event_type;
        } else {
            movementComponent->get()->moveDirectionY = event_type;
        }
    }
    if (event_type == potEngine::EventType::INFORMATION) {
        handleCreateEntity(params, entity_id);
    }
    if (event_type == potEngine::EventType::DEATH) {
        std::cout << "[CLIENT] Entity {ID}-[" << entity_id << "] is removed." << std::endl;
        potEngine::engine.removeEntity(potEngine::engine.getClientIdFromServerId(entity_id));
        if (entity_id == player_id)
            potEngine::engine.publishEvent(std::make_shared<potEngine::StopMainLoopEvent>());
    }
    if (event_type == potEngine::EventType::COLLISION) {
        std::shared_ptr<potEngine::ClientCollisionInfoEvent> event = std::make_shared<potEngine::ClientCollisionInfoEvent>(entity_id, params[0]);
        potEngine::engine.publishEvent(event);
    }
}
