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

        void update(float deltaTime, std::vector<std::shared_ptr<Entity>> entities)
        {
            for (auto& entity : entities) {
                if (entity->hasComponent<PositionComponent>() && entity->hasComponent<MovementComponent>()) {
                    auto position = entity->getComponent<PositionComponent>().value();
                    auto movement = entity->getComponent<MovementComponent>().value();
                    position->x += movement->velocity_x * deltaTime;
                    position->y += movement->velocity_y * deltaTime;
                }
            }
        }
    };
}
