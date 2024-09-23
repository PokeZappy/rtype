/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** MovementSystem.hpp
*/

#pragma once

#include "ASystem.hpp"
#include "MovementComponent.hpp"

namespace potEngine
{
    class MovementSystem : public ASystem {
    public:
        MovementSystem() {}
        ~MovementSystem() {}

        void update(float deltaTime, std::vector<std::shared_ptr<Entity>> entities) override
        {
            for (auto& entity : entities) {
                auto movement = entity->getComponent<MovementComponent>();
                if (movement) {
                    movement->x += deltaTime * 10;
                }
            }
        }
    };
}
