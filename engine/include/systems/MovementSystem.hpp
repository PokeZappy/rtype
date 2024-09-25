/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** MovementSystem.hpp
*/

#pragma once

#include "ASystem.hpp"
#include "MovementComponent.hpp"
#include "PositionComponent.hpp"

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
                auto velocity = entity->getComponent<MovementComponent>().value()->_vy;
                position->_y += 1 * velocity;
            }
        }

        void moveDown(std::shared_ptr<Entity> entity)
        {
            if (entity->hasComponent<PositionComponent>() && entity->hasComponent<MovementComponent>()) {
                auto position = entity->getComponent<PositionComponent>().value();
                auto velocity = entity->getComponent<MovementComponent>().value()->_vy;
                position->_y -= 1 * velocity;
            }
        }

        void moveLeft(std::shared_ptr<Entity> entity)
        {
            if (entity->hasComponent<PositionComponent>() && entity->hasComponent<MovementComponent>()) {
                auto position = entity->getComponent<PositionComponent>().value();
                auto velocity = entity->getComponent<MovementComponent>().value()->_vx;
                position->_x -= 1 * velocity;
            }
        }

        void moveRight(std::shared_ptr<Entity> entity)
        {
            if (entity->hasComponent<PositionComponent>() && entity->hasComponent<MovementComponent>()) {
                auto position = entity->getComponent<PositionComponent>().value();
                auto velocity = entity->getComponent<MovementComponent>().value()->_vx;
                position->_x += 1 * velocity;
            }
        }

        void update(float deltaTime, std::vector<std::shared_ptr<Entity>> entities) {}
    };

}
