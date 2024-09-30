/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** ISystem.hpp
*/

#ifndef ISYSTEM_HPP
#define ISYSTEM_HPP

#include <vector>
#include <memory>

#include "Entity.hpp"
#include "Event.hpp"

namespace polEngine
{
    class ISystem {
    public:
        virtual ~ISystem() = default;

        virtual void update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities) = 0;
        virtual void handleEvent(const Event& event, std::vector<std::shared_ptr<Entity>>& entities) = 0;
    };
}

#endif // ISYSTEM_HPP
