/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** ASystem.hpp
*/


#ifndef ASYSTEM_HPP
#define ASYSTEM_HPP

#include "ISystem.hpp"

namespace polEngine
{
    class ASystem : public ISystem {
    public:
        virtual ~ASystem() = default;

        void update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities) override {}
    };
}

#endif // ASYSTEM_HPP
