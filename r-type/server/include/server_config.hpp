/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server_config.hpp
*/

#pragma once

#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sys/socket.h>
#include <vector>
#include <algorithm>
#include <memory>
#include <mutex>

#include "Entity.hpp"
#include "game_config.hpp"

#include "NetworkComponent.hpp"
#include "MovementComponent.hpp"
#include "PositionComponent.hpp"

#include "NetworkSystem.hpp"
#include "MovementSystem.hpp"

struct ClientInfo {
    uint8_t client_id;
    struct sockaddr_in client_addr;
};

namespace potEngine
{
    class Server {
        MovementSystem movement_system;
        NetworkSystem network_system;

        public:
            Server();
            ~Server();
            void start();

        private:
            int server_fd;
            struct sockaddr_in server_addr;
            std::vector<ClientInfo> clients;
            std::unordered_map<int, std::shared_ptr<Entity>> entities;
            uint8_t current_players;

            uint8_t assign_client_id();
            void remove_client(uint8_t client_id);
            void handle_action(uint8_t client_id, uint8_t action);
            void handle_client_connection(int client_id);
    };
}