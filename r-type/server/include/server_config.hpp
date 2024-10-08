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
#include <fcntl.h>
#include <chrono>
#include <cstring>
#include <unistd.h>

namespace RType
{
    class Server {
    public:
        Server();
        ~Server();

        void start();
        void init_subscribe();
        void setNonBlockingInput();
        void handle_action(size_t entity_id, struct sockaddr_in client_addr, potEngine::EventType action, std::vector<size_t> params);

        std::tuple<size_t, potEngine::EventType, std::vector<size_t>> recv_message(struct sockaddr_in& addr, socklen_t& addr_len);

    private:
        int current_players;
        int server_fd;
        struct sockaddr_in server_addr;
        socklen_t server_addr_len;
    };
}

#endif // SERVER_HPP
