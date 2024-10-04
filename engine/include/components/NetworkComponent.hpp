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

namespace potEngine
{
    class NetworkComponent : public AComponent {
    public:
        int fd;
        sockaddr_in addr;

        NetworkComponent(const sockaddr_in& address, int filedesc)
            : fd(filedesc), addr(address) {}
    };
}


#endif // NETWORK_COMPONENT_HPP
