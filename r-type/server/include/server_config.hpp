/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server.hpp
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include "ServerInclude.hpp"
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
        void init_subscribe();
        void setNonBlockingInput();

    private:
        int current_players;
        int server_fd;
        struct sockaddr_in server_addr;
        socklen_t server_addr_len;
    };
}

#endif // SERVER_HPP
