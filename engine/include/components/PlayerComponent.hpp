/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** PlayerComponent.hpp
*/

#ifndef PLAYER_COMPONENT_HPP
#define PLAYER_COMPONENT_HPP

#include <iostream>

#include "AComponent.hpp"
#include <optional>

namespace potEngine
{
    class PlayerComponent : public AComponent {
    public:
        std::string username;


        PlayerComponent(std::string username = "none")
            : username(username) {}

        void setShootAnimationEntityId(int value) {_shootAnimationEntityId = value; }
        std::optional<int> &getShootAnimationEntityId() { return (_shootAnimationEntityId); }
    private:
        std::optional<int> _shootAnimationEntityId;
    };
}

#endif // PLAYER_COMPONENT_HPP
