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
#include <vector>
#include <memory>
#include <unordered_map>
#include <mutex>

#include "Entity.hpp"
#include "game_config.hpp"

#include "NetworkSystem.hpp"
#include "MovementSystem.hpp"

#include "PositionComponent.hpp"
#include "PlayerComponent.hpp"
#include "NetworkComponent.hpp"

struct ClientInfo {
    uint8_t client_id;
    struct sockaddr_in client_addr;
};

namespace potEngine
{
    class Server {
    public:
        Server();
        ~Server();

        void start();
        void handle_client_connection(uint8_t client_id, struct sockaddr_in client_addr, std::vector<uint16_t> params);

    private:
        uint8_t current_players;
        MovementSystem movement_system;
        NetworkSystem network_system;
        int server_fd;
        struct sockaddr_in server_addr;
        std::vector<ClientInfo> clients;
        std::unordered_map<uint8_t, std::shared_ptr<Entity>> entities;

        uint8_t assign_client_id();
        void remove_client(uint8_t client_id);
        void handle_action(uint8_t client_id, uint8_t action);
        void create_player_entity(uint8_t client_id, const std::string& username, const sockaddr_in& client_addr);
    };
}
