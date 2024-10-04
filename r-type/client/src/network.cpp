/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** network.cpp
*/

#include "client_config.hpp"

std::tuple<uint8_t, potEngine::EventType, std::vector<uint16_t>> RType::Client::recv_message(struct sockaddr_in& addr, socklen_t& addr_len)
{
    uint8_t buffer[BUFFER_SIZE];
    ssize_t recv_len = recvfrom(client_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);

    if (recv_len < 0) {
        return std::make_tuple(0, potEngine::EventType::UNKNOW, std::vector<uint16_t>{});
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
