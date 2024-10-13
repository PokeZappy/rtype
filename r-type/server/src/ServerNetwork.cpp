/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server.cpp
*/

#include "server_config.hpp"

std::tuple<size_t, potEngine::EventType, std::vector<size_t>> RType::Server::recv_message()
{
    uint8_t buffer[1024];
    ssize_t recv_len = recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&_addr, &_addr_len);

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

void RType::Server::handle_message()
{
    auto [entity_id, event_type, params] = recv_message();
    // if (event_type != EventType::UNKNOW)
    //     std::cout << "[SERVER] Received event from client: " << static_cast<int>(event_type) << std::endl;

    if (event_type == potEngine::CONNECTION && 4 > current_players) {
        auto connectionInfo = std::make_shared<potEngine::ConnectionInfoEvent>(4, server_fd, _addr, params);
        potEngine::engine.publishEvent(connectionInfo);
        current_players++;
    }
    if (event_type == potEngine::DISCONNECT) {
        auto disconnectInfo = std::make_shared<potEngine::DisconnectionInfoEvent>(4, server_fd, entity_id, params);
        potEngine::engine.publishEvent(disconnectInfo);
        current_players--;
    }
    if (event_type == potEngine::MOVE_UP || event_type == potEngine::MOVE_DOWN || event_type == potEngine::MOVE_RIGHT || event_type == potEngine::MOVE_LEFT) {
        auto moveInfo = std::make_shared<potEngine::MoveInfoEvent>(4, server_fd, event_type, entity_id);
        potEngine::engine.publishEvent(moveInfo);
    }
    if (event_type == potEngine::SHOOT) {
        auto createShootEntity = std::make_shared<potEngine::EntityCreateInfoEvent>(
            4,
            server_fd,
            potEngine::engine.getEntity(entity_id)->getComponent<potEngine::PositionComponent>()->get()->_position,
            entity_id,
            potEngine::EntityType::PEW
        );
        potEngine::engine.publishEvent(createShootEntity);
    } if (event_type == potEngine::DEATH) {
        std::cout << "[SERVER] Entity {ID}-[" << entity_id << "] is removed." << std::endl;
        potEngine::engine.removeEntity(entity_id);
    }
}
