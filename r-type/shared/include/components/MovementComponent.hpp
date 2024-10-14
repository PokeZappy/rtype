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
        EventType moveDirectionX;
        EventType moveDirectionY;

        MovementComponent(int speed = 1)
            : speed(speed), moveDirectionX(MOVE_X_STOP), moveDirectionY(MOVE_Y_STOP) {}
    };
}

#endif // MOVEMENT_COMPONENT_HPP
