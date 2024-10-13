/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** PlayerComponent.hpp
*/

#ifndef PLAYER_COMPONENT_HPP
#define PLAYER_COMPONENT_HPP

#include <iostream>
#include <optional>

#include "AComponent.hpp"

namespace potEngine
{
    class PlayerComponent : public AComponent {
    public:
        std::string username;

        PlayerComponent(std::string username = "none", size_t playerNb=0)
            : username(username), _playerNumber(playerNb) {}

        void setShootAnimationEntityId(int value) {_shootAnimationEntityId = value; }
        std::optional<int> &getShootAnimationEntityId() { return (_shootAnimationEntityId); }
        size_t getPlayerNumber() { return (_playerNumber); }
    private:
        std::optional<int> _shootAnimationEntityId;
        size_t _playerNumber;
    };
}

#endif // PLAYER_COMPONENT_HPP
