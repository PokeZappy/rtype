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
        int x;
        int y;

        PositionComponent(int x = 0, int y = 0) : x(x), y(y) {}
    };
}
