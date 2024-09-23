/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** server_config.hpp
*/

#ifndef SERVER_CONFIG_HPP
#define SERVER_CONFIG_HPP

#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sys/socket.h>
#include <vector>
#include <algorithm>

#include "game_config.hpp"
#include "NetworkComponent.hpp"
#include "RecvNetworkSystem.hpp"
#include "SendNetworkSystem.hpp"

struct ClientInfo {
    uint8_t client_id;
    struct sockaddr_in client_addr;
};

class Server {
    public:
        Server();
        ~Server();
        void start();

    private:
        int server_fd;
        struct sockaddr_in server_addr;
        std::vector<ClientInfo> clients;
        uint8_t current_players;

        uint8_t assign_client_id();
        void remove_client(uint8_t client_id);

        void handle_action(uint8_t client_id, uint8_t action);
};

#endif // SERVER_CONFIG_HPP
