/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** PositionComponent.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace potEngine
{
    class PositionComponent : public AComponent {
    public:
        float _x;
        float _y;

        PositionComponent(float x = 0, float y = 0) : _x(x), _y(y) {}
    };
}
