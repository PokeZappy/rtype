/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** client_config.hpp
*/

#ifndef CLIENT_CONFIG_HPP
#define CLIENT_CONFIG_HPP

#include <cstring>
#include <iostream>
#include <libconfig.h++>

#include "ClientInclude.hpp"
#include "Config.hpp"

void title_screen(const std::string& asset_path);

namespace RType
{
    class Client {
    public:
        Client();
        ~Client();

        void start();
        std::tuple<size_t, potEngine::EventType, std::vector<size_t>> recv_message(struct sockaddr_in& addr, socklen_t& addr_len);
        void init_subscribe();
        void setNonBlockingInput();
        void create_background();
        void handle_connection();

    private:
        size_t player_id;
        int client_fd;
        struct sockaddr_in server_addr;
    };
}

#endif // CLIENT_CONFIG_HPP