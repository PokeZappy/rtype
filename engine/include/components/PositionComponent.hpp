/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** PositionComponent.hpp
*/

#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP

#include "AComponent.hpp"
#include <vector>

namespace potEngine
{
    class PositionComponent : public AComponent {
    public:
        std::vector<int> _position = {0, 0};

        PositionComponent(int posX = 0, int posY = 0) : _position({posX, posY}) {}
        PositionComponent() = default;
        ~PositionComponent() = default;
    };
}

#endif // POSITION_COMPONENT_HPP
