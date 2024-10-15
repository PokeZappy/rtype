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
#include <fcntl.h>
#include <termios.h>
#include <thread>

void title_screen(const std::string& asset_path);

namespace RType
{
    class Client {
    public:
        Client(const std::string& ip, int port);
        ~Client();

        void start();
        void init_subscribe();
        void setNonBlockingInput();
        void create_background();
        void handle_connection();

        void send_message(size_t entity_id, potEngine::EventType action, const std::vector<size_t>& params, size_t maxP, int fd);
        std::tuple<size_t, potEngine::EventType, std::vector<size_t>> recv_message();
        void handle_message();
        void createPlayerEntity(std::vector<size_t> params, size_t entity_id);
        void createShootEntity(std::vector<size_t> params, size_t entity_id);
        void createHurdleEntity(std::vector<size_t> params, size_t entity_id);
        void handleCreateEntity(std::vector<size_t> params, size_t entity_id);
    private:
        size_t player_id;
        int client_fd;
        struct sockaddr_in _addr;
        socklen_t _addr_len;
    };
}

#endif // CLIENT_CONFIG_HPP