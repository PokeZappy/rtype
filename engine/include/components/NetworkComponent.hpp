/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** NetworkComponent.hpp
*/

#ifndef NETWORK_COMPONENT_HPP
#define NETWORK_COMPONENT_HPP

#include <netinet/in.h>

#include "AComponent.hpp"

namespace polEngine
{
    class NetworkComponent : public AComponent {
    public:
        int sockfd;
        sockaddr_in addr;

        NetworkComponent(int socket, const sockaddr_in& address)
            : AComponent("Network"), sockfd(socket), addr(address) {}
    };
}


#endif // NETWORK_COMPONENT_HPP
