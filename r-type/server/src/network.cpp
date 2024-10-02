/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** network.cpp
*/

#include "server_config.hpp"

std::tuple<uint8_t, potEngine::EventType, std::vector<uint16_t>> RType::Server::recv_message(struct sockaddr_in& addr, socklen_t& addr_len)
{
    uint8_t buffer[1024];
    ssize_t recv_len = recvfrom(SERVER_SOCKET, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);

    if (recv_len < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            return std::make_tuple(0, potEngine::EventType::UNKNOW, std::vector<uint16_t>{});
        } else {
            return std::make_tuple(0, potEngine::EventType::UNKNOW, std::vector<uint16_t>{});
        }
    }

    int entity_id_bits = std::ceil(std::log2(MAX_PLAYERS + 1));
    int action_bits = 8 - entity_id_bits;

    uint8_t entity_id = (buffer[0] >> action_bits) & ((1 << entity_id_bits) - 1);
    uint8_t action = buffer[0] & ((1 << action_bits) - 1);

    potEngine::EventType event_type = static_cast<potEngine::EventType>(action);

    std::vector<uint16_t> params;
    for (ssize_t i = 1; i + 1 < recv_len; i += 2) {
        uint16_t param = (buffer[i] << 8) | buffer[i + 1];
        params.push_back(param);
    }

    return std::make_tuple(entity_id, event_type, params);
}


void RType::Server::send_message(const struct sockaddr_in& addr, uint8_t entity_id, potEngine::EventType action, const std::vector<uint16_t>& params)
{
    int entity_id_bits = std::ceil(std::log2(MAX_PLAYERS + 1));
    int action_bits = 8 - entity_id_bits;

    size_t packet_size = 1 + params.size() * sizeof(uint16_t);
    std::vector<uint8_t> packet(packet_size);

    packet[0] = (entity_id & ((1 << entity_id_bits) - 1)) << action_bits | (action & ((1 << action_bits) - 1));

    for (size_t i = 0; i < params.size(); ++i) {
        packet[1 + 2 * i] = (params[i] >> 8) & 0xFF;
        packet[1 + 2 * i + 1] = params[i] & 0xFF;
    }
    sendto(CLIENT_SOCKET, packet.data(), packet.size(), 0, (const struct sockaddr*)&addr, sizeof(addr));
}

void RType::Server::send_message_to_all(uint8_t entity_id, potEngine::EventType event_type, const std::vector<uint16_t>& params, const std::vector<std::shared_ptr<potEngine::AEntity>>& entities)
{
    for (const auto& entity : entities) {
        auto networkComponent = entity->getComponent<potEngine::NetworkComponent>();
        if (networkComponent && entity->getID() != entity_id) {
            send_message(networkComponent->get()->addr, entity_id, event_type, params);
        }
    }
}
