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
        float xDirection;
        float yDirection;
        float speed;

        MovementComponent(float speed = 1.0f)
            : xDirection(0.0f), yDirection(0.0f), speed(speed) {}
    };
}

#endif // MOVEMENT_COMPONENT_HPP
