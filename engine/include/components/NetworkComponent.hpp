/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** NetworkComponent.hpp
*/

#pragma once

#include <netinet/in.h>

#include "AComponent.hpp"

namespace potEngine
{
    class NetworkComponent : public AComponent {
    public:
        int _maxP;
        struct sockaddr_in _addr;

        NetworkComponent(int maxP, struct sockaddr_in addr) : _maxP(maxP), _addr(addr) {}
        ~NetworkComponent() {}
    };
}
