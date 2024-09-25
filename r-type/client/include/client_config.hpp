/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** client_config.hpp
*/

#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdint>
#include <thread>
#include <vector>
#include <string>
#include <memory>

#include "Entity.hpp"
#include "game_config.hpp"

#include "NetworkSystem.hpp"

#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "NetworkComponent.hpp"

namespace potEngine
{
    class Client {
    public:
        Client();
        ~Client();

        void connect_to_server();
        int handle_input();
        void set_id(uint8_t id);
        uint8_t get_id() const;

        void create_player_entity(uint8_t client_id, const std::string& username);
        void delete_player_entity();
        void wait_for_server_response();

    private:
        NetworkSystem network_system;

        int sockfd;
        struct sockaddr_in server_addr;
        uint8_t client_id;
        std::shared_ptr<Entity> player_entity;
    };
}
