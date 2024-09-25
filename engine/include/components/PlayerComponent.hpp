/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** PlayerComponent.hpp
*/

#pragma once

#include <iostream>

#include "AComponent.hpp"

namespace potEngine
{
    class PlayerComponent : public AComponent {
    public:
        std::string _username;

        PlayerComponent(std::string username = "none") : _username(username) {}
        ~PlayerComponent() {}
    };
}
