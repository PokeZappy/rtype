/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** RecvMessageServerSystem.hpp
*/

#pragma once

#include "ServerInclude.hpp"
#include "DisconnectionEvent.hpp"

namespace potEngine
{
    class RecvMessageServerSystem : public ASystem {
    public:
        int _serverFd;
        struct sockaddr_in _addr;
        socklen_t _addrLen;
        int current_players;

        void update(float) override {};

        RecvMessageServerSystem(int serverFd, struct sockaddr_in server_addr, socklen_t server_addr_len);

        ~RecvMessageServerSystem();

        std::tuple<size_t, EventType, std::vector<size_t>> recv_message();

        void updateSystem(std::shared_ptr<NoneEvent> event);
    };
}