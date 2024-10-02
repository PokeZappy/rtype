/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server.hpp
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include "game_config.hpp"

#include <memory>
#include <vector>
#include <netinet/in.h>
#include <iostream>

namespace RType
{
    class Server {
    public:
        Server();
        ~Server();

        void start();
        void handle_action(uint8_t client_id, uint8_t action);
        void handle_client_connection(uint8_t client_id, struct sockaddr_in client_addr, std::vector<uint16_t> params);

    private:
        int current_players;
        int server_fd;
        struct sockaddr_in server_addr;

        std::shared_ptr<potEngine::ECSManager> ecs_manager;

        uint8_t assign_client_id();
        void remove_client(uint8_t client_id);
        void create_player_entity(uint8_t client_id, const std::string& username, const sockaddr_in& client_addr);
    };
}

#endif // SERVER_HPP

