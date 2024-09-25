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
        float _vx;
        float _vy;

        MovementComponent(float vx = 1, float vy = 1) : _vx(vx), _vy(vy) {}
    };
}
