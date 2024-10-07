/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server.hpp
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include "game_config.hpp"
#include "cross_config.hpp"


#include <memory>
#include <vector>
#include <iostream>
#include <chrono>
#include <cstring>

namespace RType
{
    class Server {
    public:
        Server();
        ~Server();

        void start();
        void handle_action(uint8_t client_id, struct sockaddr_in client_addr, potEngine::EventType action, std::vector<uint16_t> params);
        std::tuple<uint8_t, potEngine::EventType, std::vector<uint16_t>> recv_message(struct sockaddr_in& addr, socklen_t& addr_len);
        void init_subscribe();

    private:
        int current_players;
        int server_fd;
        struct sockaddr_in server_addr;
        std::shared_ptr<potEngine::ECSManager> ecs_manager;
    };
}

#endif // SERVER_HPP
