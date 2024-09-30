/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** PositionComponent.hpp
*/

#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP

#include "AComponent.hpp"

namespace polEngine
{
    class PositionComponent : public AComponent {
    public:
        float x, y;

        PositionComponent(float posX = 0.0f, float posY = 0.0f)
            : AComponent("Position"), x(posX), y(posY) {}
    };
}

#endif // POSITION_COMPONENT_HPP
