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

        void send_message(int sockfd, const struct sockaddr_in& addr, uint8_t client_id, uint8_t action, const std::vector<uint16_t>& params)
        {
            int client_id_bits = std::ceil(std::log2(MAX_PLAYERS + 1));
            int action_bits = 8 - client_id_bits;

            size_t packet_size = 1 + params.size() * sizeof(uint16_t);
            std::vector<uint8_t> packet(packet_size);

            packet[0] = (client_id & ((1 << client_id_bits) - 1)) << action_bits | (action & ((1 << action_bits) - 1));

            for (size_t i = 0; i < params.size(); ++i) {
                packet[1 + 2 * i] = (params[i] >> 8) & 0xFF;
                packet[1 + 2 * i + 1] = params[i] & 0xFF;
            }
            sendto(sockfd, packet.data(), packet.size(), 0, (const struct sockaddr*)&addr, sizeof(addr));
        }


    };
}
