/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** client_config.hpp
*/

#ifndef CLIENT_CONFIG_HPP
#define CLIENT_CONFIG_HPP

#include "game_config.hpp"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <iostream>

namespace RType
{
    class Client {
    public:
        Client();
        ~Client();

        void start();
        std::tuple<uint8_t, potEngine::EventType, std::vector<uint16_t>> recv_message(struct sockaddr_in& addr, socklen_t& addr_len);

    private:
        int client_fd;
        struct sockaddr_in server_addr;
        std::shared_ptr<potEngine::ECSManager> ecs_manager;
    };
}


#endif // CLIENT_CONFIG_HPP
