/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** MovementComponent.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace potEngine
{
    class MovementComponent : public AComponent {
    public:
        int x;
        int y;

        MovementComponent(int init_x = 0, int init_y = 0) : x(init_x), y(init_y) {}
        ~MovementComponent() {}
    };
}
