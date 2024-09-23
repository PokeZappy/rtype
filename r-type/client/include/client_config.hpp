/*
** EPITECH PROJECT, 2024
** EPITECH
** File description:
** client_config.hpp
*/

#ifndef CLIENT_CONFIG_HPP
#define CLIENT_CONFIG_HPP

#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdint>

#include "game_config.hpp"
#include "NetworkComponent.hpp"
#include "RecvNetworkSystem.hpp"
#include "SendNetworkSystem.hpp"

class Client {
    public:
        Client();
        ~Client();

        void connect_to_server();
        int handle_input();
        void set_id(uint8_t id);
        uint8_t get_id() const;

    private:
        int sockfd;
        struct sockaddr_in server_addr;
        uint8_t client_id;
};

#endif // CLIENT_CONFIG_HPP
