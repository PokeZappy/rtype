/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** RecvNetworkSystem.hpp
*/

#pragma once

#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdint>
#include <cstring>
#include <utility>
#include <cmath>
#include <memory>

#include "ASystem.hpp"
#include "game_config.hpp"

namespace potEngine
{
    class RecvNetworkSystem : public ASystem {
    public:
        RecvNetworkSystem() {}
        ~RecvNetworkSystem() {}

        void update(float deltaTime, std::vector<std::shared_ptr<Entity>> entities) {}

        std::pair<uint8_t, uint8_t> recv_message(int sockfd, struct sockaddr_in& addr, socklen_t& addr_len)
        {
            uint8_t packet;
            recvfrom(sockfd, &packet, sizeof(packet), 0, (struct sockaddr*)&addr, &addr_len);

            int client_id_bits = std::ceil(std::log2(MAX_PLAYERS));
            int action_bits = 8 - client_id_bits;

            uint8_t client_id = (packet >> action_bits) & ((1 << client_id_bits) - 1);
            uint8_t action = packet & ((1 << action_bits) - 1);

            return std::make_pair(client_id, action);
        }
    };
}
