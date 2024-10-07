#ifndef CLIENT_CONFIG_HPP
#define CLIENT_CONFIG_HPP

#include "cross_config.hpp"
#include "game_config.hpp"

#include <cstring>
#include <iostream>

namespace RType
{
    class Client {
    public:
        Client();
        ~Client();

        void start();
        std::tuple<uint8_t, potEngine::EventType, std::vector<uint16_t>> recv_message(struct sockaddr_in& addr, socklen_t& addr_len);
        void init_subscribe();
        void handle_input();
        void setNonBlockingInput();
        void handle_connection();
        void handle_create_entity_player(uint8_t entity_id,  std::string username);

    private:
        uint8_t player_id;
        int client_fd;
        struct sockaddr_in server_addr;
        std::shared_ptr<potEngine::ECSManager> ecs_manager;
    };
}

#endif // CLIENT_CONFIG_HPP