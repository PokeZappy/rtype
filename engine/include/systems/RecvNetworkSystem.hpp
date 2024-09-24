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

        std::tuple<uint8_t, uint8_t, std::vector<uint16_t>> recv_message(int sockfd, struct sockaddr_in& addr, socklen_t& addr_len)
        {
            uint8_t buffer[1024];
            ssize_t recv_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);

            if (recv_len < 1) {
                return std::make_tuple(0, 0, std::vector<uint16_t>{});
            }

            int client_id_bits = std::ceil(std::log2(MAX_PLAYERS + 1));
            int action_bits = 8 - client_id_bits;

            uint8_t client_id = (buffer[0] >> action_bits) & ((1 << client_id_bits) - 1);
            uint8_t action = buffer[0] & ((1 << action_bits) - 1);

            std::vector<uint16_t> params;
            for (ssize_t i = 1; i + 1 < recv_len; i += 2) {
                uint16_t param = (buffer[i] << 8) | buffer[i + 1];
                params.push_back(param);
            }

            return std::make_tuple(client_id, action, params);
        }


    };
}
