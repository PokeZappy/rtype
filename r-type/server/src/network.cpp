/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** network.cpp
*/

#include "server_config.hpp"

std::tuple<size_t, potEngine::EventType, std::vector<size_t>> RType::Server::recv_message(struct sockaddr_in& addr, socklen_t& addr_len)
{
    uint8_t buffer[BUFFER_SIZE];
    ssize_t recv_len = recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);

    if (recv_len < 0 || static_cast<size_t>(recv_len) < sizeof(size_t)) {
        return std::make_tuple(0, potEngine::EventType::UNKNOW, std::vector<size_t>{});
    }

    int entity_id_bits = std::ceil(std::log2(MAX_PLAYERS + 1));
    int action_bits = sizeof(size_t) * 8 - entity_id_bits;

    size_t header;
    std::memcpy(&header, buffer, sizeof(size_t));

    size_t entity_id = (header >> action_bits) & ((1 << entity_id_bits) - 1);
    size_t action = header & ((1 << action_bits) - 1);

    potEngine::EventType event_type = static_cast<potEngine::EventType>(action);

    std::vector<size_t> params;
    for (size_t i = sizeof(size_t); i + sizeof(size_t) <= static_cast<size_t>(recv_len); i += sizeof(size_t)) {
        size_t param;
        std::memcpy(&param, buffer + i, sizeof(size_t));
        params.push_back(param);
    }

    return std::make_tuple(entity_id, event_type, params);
}
