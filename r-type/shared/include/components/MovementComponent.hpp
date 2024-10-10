/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** MovementComponent.hpp
*/

#ifndef MOVEMENT_COMPONENT_HPP
#define MOVEMENT_COMPONENT_HPP

#include "AComponent.hpp"

namespace potEngine
{
    class MovementComponent : public AComponent {
    public:
        int speed;

        MovementComponent(int speed = 1)
            : speed(speed) {}
    };
}

#endif // MOVEMENT_COMPONENT_HPP
