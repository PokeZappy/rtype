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

        void moveUp(std::shared_ptr<Entity> entity)
        {
            if (entity->hasComponent<PositionComponent>() && entity->hasComponent<MovementComponent>()) {
                auto position = entity->getComponent<PositionComponent>().value();
                position->y += 1;
            }
        }

        void moveDown(std::shared_ptr<Entity> entity)
        {
            if (entity->hasComponent<PositionComponent>() && entity->hasComponent<MovementComponent>()) {
                auto position = entity->getComponent<PositionComponent>().value();
                position->y -= 1;
            }
        }

        void moveLeft(std::shared_ptr<Entity> entity)
        {
            if (entity->hasComponent<PositionComponent>() && entity->hasComponent<MovementComponent>()) {
                auto position = entity->getComponent<PositionComponent>().value();
                position->x -= 1;
            }
        }

        void moveRight(std::shared_ptr<Entity> entity)
        {
            if (entity->hasComponent<PositionComponent>() && entity->hasComponent<MovementComponent>()) {
                auto position = entity->getComponent<PositionComponent>().value();
                position->x += 1;
            }
        }

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
