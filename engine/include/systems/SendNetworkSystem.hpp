/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** SendNetworkSystem.hpp
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
    class SendNetworkSystem : public ASystem {
    public:
        SendNetworkSystem() {}
        ~SendNetworkSystem() {}

        void update(float deltaTime, std::vector<std::shared_ptr<Entity>> entities) {}

        void send_message(int sockfd, const struct sockaddr_in& addr, uint8_t client_id, uint8_t action)
        {
            int client_id_bits = std::ceil(std::log2(MAX_PLAYERS));
            int action_bits = 8 - client_id_bits;
            uint8_t packet = (client_id & ((1 << client_id_bits) - 1)) << action_bits | (action & ((1 << action_bits) - 1));

            sendto(sockfd, &packet, sizeof(packet), 0, (const struct sockaddr*)&addr, sizeof(addr));
        }
    };
}
