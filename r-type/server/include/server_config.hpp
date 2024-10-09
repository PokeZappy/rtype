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
        Server(int port);
        ~Server();

        void start();
        void init_subscribe();
        void setNonBlockingInput();

    private:
        int current_players;
        int server_fd;
        struct sockaddr_in server_addr;
        socklen_t server_addr_len;
        void init(int port);
    };
}

#endif // SERVER_HPP
