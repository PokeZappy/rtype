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
        std::vector<float> _position = {0, 0};

        PositionComponent(float posX = 0.0f, float posY = 0.0f) : _position({posX, posY}) {}
        PositionComponent() = default;
        ~PositionComponent() = default;
    };
}

#endif // POSITION_COMPONENT_HPP
