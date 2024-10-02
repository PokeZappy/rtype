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

namespace RType
{
    class Server {
    public:
        Server();
        ~Server();

        void start();
        void handle_action(uint8_t client_id, struct sockaddr_in client_addr, potEngine::EventType action, std::vector<uint16_t> params);
        void handle_client_connection(struct sockaddr_in client_addr, std::vector<uint16_t> params);
        void handle_client_disconnection(uint8_t entity_id);

        void send_message_to_all(uint8_t entity_id, potEngine::EventType event_type, const std::vector<uint16_t>& params, const std::vector<std::shared_ptr<potEngine::AEntity>>& entities);
        std::tuple<uint8_t, potEngine::EventType, std::vector<uint16_t>> recv_message(struct sockaddr_in& addr, socklen_t& addr_len);
        void send_message(const struct sockaddr_in& addr, uint8_t entity_id, potEngine::EventType action, const std::vector<uint16_t>& params);

    private:
        int current_players;
        int server_fd;
        struct sockaddr_in server_addr;

        std::shared_ptr<potEngine::ECSManager> ecs_manager;
    };
}

#endif // SERVER_HPP

