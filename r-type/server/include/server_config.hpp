/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server.hpp
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include "ServerInclude.hpp"

#include <memory>
#include <vector>
#include <netinet/in.h>
#include <iostream>
#include <fcntl.h>
#include <chrono>
#include <cstring>
#include <unistd.h>
#include <thread>

namespace RType
{
    /*!
    * @brief Class representing the server.
    *
    * This class handles the server-side operations, including initializing the server, handling messages, and managing connections.
    */
    class Server {
    public:
        Server();
        Server(int port);
        ~Server();

        void start();
        void init_subscribe();
        void setNonBlockingInput();

        std::tuple<size_t, potEngine::EventType, std::vector<size_t>> recv_message();
        void handle_message();
    private:
        int current_players;
        int server_fd;
        struct sockaddr_in _addr;
        socklen_t _addr_len;
        void init(int port);
    };
}

#endif // SERVER_HPP
