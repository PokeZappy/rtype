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
    /*!
    * @brief Component class for managing network connections.
    */
    class NetworkComponent : public AComponent {
    public:
        int fd;
        sockaddr_in addr;

        /*!
        * @brief Construct a new NetworkComponent object.
        * @param address The network address.
        * @param filedesc The file descriptor for the network socket.
        */
        NetworkComponent(const sockaddr_in& address, int filedesc)
            : fd(filedesc), addr(address) {}
    };
}


#endif // NETWORK_COMPONENT_HPP
