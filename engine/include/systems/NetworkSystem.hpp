/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** NetworkSystem.hpp
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

namespace potEngine
{
    class NetworkSystem : public ASystem {
        int _max_player;
    public:
        NetworkSystem(int maxP) : _max_player(maxP) {}
        ~NetworkSystem() {}

        void update(float deltaTime, std::vector<std::shared_ptr<Entity>> entities) {}

        std::tuple<uint8_t, uint8_t, std::vector<uint16_t>> recv_message(int sockfd, struct sockaddr_in& addr, socklen_t& addr_len)
        {
            uint8_t buffer[1024];
            ssize_t recv_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);

            if (recv_len < 1) {
                return std::make_tuple(0, 0, std::vector<uint16_t>{});
            }

            int client_id_bits = std::ceil(std::log2(_max_player + 1));
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

        void send_message(int sockfd, const struct sockaddr_in& addr, uint8_t client_id, uint8_t action, const std::vector<uint16_t>& params)
        {
            int client_id_bits = std::ceil(std::log2(_max_player + 1));
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
