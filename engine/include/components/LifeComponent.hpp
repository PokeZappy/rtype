/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** LifeComponent.hpp
*/

#ifndef LIFE_COMPONENT_HPP
#define LIFE_COMPONENT_HPP

#include "AComponent.hpp"

namespace potEngine
{
    class LifeComponent : public AComponent {
    public:
        int life;

        LifeComponent(int life = 1)
            : life(life) {}
    };
}

#endif // LIFE_COMPONENT_HPP
