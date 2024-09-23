/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** MovementComponent.hpp
*/

#pragma once

#include "IComponent.hpp"

namespace potEngine
{
    class MovementComponent : public AComponent {
    public:
        float velocity_x, velocity_y;

        MovementComponent(float vx = 0, float vy = 0) : velocity_x(vx), velocity_y(vy) {}
    };
}

