/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** ECSManager.hpp
*/

#ifndef ECS_MANAGER_HPP
#define ECS_MANAGER_HPP

#include <vector>
#include <memory>
#include <algorithm>

#include "Entity.hpp"
#include "systems/ISystem.hpp"

namespace polEngine
{
    class ECSManager {
    private:
        std::vector<std::shared_ptr<Entity>> entities;
        std::vector<std::shared_ptr<ISystem>> systems;

    public:
        void addEntity(std::shared_ptr<Entity> entity) {
            entities.push_back(entity);
        }

        void removeEntity(uint8_t entityId) {
            entities.erase(std::remove_if(entities.begin(), entities.end(),
                [entityId](const std::shared_ptr<Entity>& entity) {
                    return entity->getId() == entityId;
                }), entities.end());
        }

        bool hasEntity(uint8_t entityId) {
            for (const auto& entity : entities) {
                if (entity->getId() == entityId) {
                    return true;
                }
            }
            return false;
        }

        std::shared_ptr<Entity> getEntity(uint8_t entityId) {
            for (const auto& entity : entities) {
                if (entity->getId() == entityId) {
                    return entity;
                }
            }
            return nullptr;
        }

        void addSystem(std::shared_ptr<ISystem> system) {
            systems.push_back(system);
        }

        void update(float deltaTime) {
            for (auto& system : systems) {
                system->update(deltaTime, entities);
            }
        }
    };
}

#endif // ECS_MANAGER_HPP
