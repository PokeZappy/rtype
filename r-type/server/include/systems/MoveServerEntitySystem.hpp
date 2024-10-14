/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** MoveServerEntitySystem.hpp
*/

#pragma once

#include "IEvent.hpp"
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "EventBus.hpp"
#include "Engine.hpp"
#include "NoneEvent.hpp"
#include "ShootComponent.hpp"
#include "PositionComponent.hpp"
#include "MoveServerEvent.hpp"

namespace potEngine
{
    class MoveServerEntitySystem : public ASystem {
    public:
        int _serverFd;

        MoveServerEntitySystem()
        {
            engine.subscribeEvent(this, &MoveServerEntitySystem::updateSystem);
        }

        ~MoveServerEntitySystem() {}

        void update(float) override {}

        void movePlayerEntity(std::shared_ptr<AEntity> entity, EventType directionX, EventType directionY)
        {
            auto networkComponent = entity->getComponent<NetworkComponent>();
            if (!networkComponent)
                return;
            if (directionX != MOVE_X_STOP) {
                auto moveInfo = std::make_shared<MoveServerInfoEvent>(
                    4,
                    networkComponent->get()->fd,
                    directionX,
                    entity->getID()
                );
                engine.publishEvent(moveInfo);
            } if (directionY != MOVE_Y_STOP) {
                auto moveInfo = std::make_shared<MoveServerInfoEvent>(
                    4,
                    networkComponent->get()->fd,
                    directionY,
                    entity->getID()
                );
                engine.publishEvent(moveInfo);
            }
        }

        void moveNonPlayerEntity(std::shared_ptr<AEntity> entity, EventType directionX, EventType directionY)
        {
            if (directionX != MOVE_X_STOP) {
                auto moveInfo = std::make_shared<MoveServerInfoEvent>(
                    4,
                    -1,
                    directionX,
                    entity->getID()
                );
                engine.publishEvent(moveInfo);
            } if (directionY != MOVE_Y_STOP) {
                auto moveInfo = std::make_shared<MoveServerInfoEvent>(
                    4,
                    -1,
                    directionY,
                    entity->getID()
                );
                engine.publishEvent(moveInfo);
            }
        }

        void updateSystem(std::shared_ptr<NoneEvent> event)
        {
            for (auto entity : engine.getEntities()) {
                auto moveComponent = entity->getComponent<MovementComponent>();
                if (!moveComponent)
                    continue;
                auto directionX = moveComponent->get()->moveDirectionX;
                auto directionY = moveComponent->get()->moveDirectionY;

                if (directionX == MOVE_X_STOP && directionY == MOVE_Y_STOP)
                    continue;
                if (entity->getComponent<PlayerComponent>())
                    movePlayerEntity(entity, directionX, directionY);
                else {
                    moveNonPlayerEntity(entity, directionX, directionY);
                }
            }
        }
    };
}
