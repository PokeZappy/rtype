/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** MovementSystem.hpp
*/
#ifndef MOVEMENT_SYSTEM_HPP
#define MOVEMENT_SYSTEM_HPP

#include "Event.hpp"
#include "ASystem.hpp"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"

namespace polEngine
{
    class MovementSystem : public ASystem {
    public:
        void handleEvent(const Event& event, std::vector<std::shared_ptr<Entity>>& entities)
        {
            for (auto& entity : entities) {
                if (entity->id == event.clientId) {
                    auto movement = entity->getComponent<MovementComponent>();
                    auto position = entity->getComponent<PositionComponent>();

                    if (movement && position) {
                        switch (event.action) {
                            case MOVE_UP:
                                movement->yDirection = 1.0f;
                                position->y += movement->speed;
                                break;
                            case MOVE_DOWN:
                                movement->yDirection = -1.0f;
                                position->y -= movement->speed;
                                break;
                            case MOVE_LEFT:
                                movement->xDirection = -1.0f;
                                position->x -= movement->speed;
                                break;
                            case MOVE_RIGHT:
                                movement->xDirection = 1.0f;
                                position->x += movement->speed;
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
    };
}

#endif // MOVEMENT_SYSTEM_HPP
