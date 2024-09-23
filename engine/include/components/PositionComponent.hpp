/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** PositionComponent.hpp
*/

#pragma once

#include "IComponent.hpp"

namespace potEngine
{
    class PositionComponent : public AComponent {
    public:
        float x;
        float y;

        PositionComponent(float _x = 0, float _y = 0) : x(_x), y(_y) {}
    };
}
