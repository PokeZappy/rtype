/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** MoveClientEntitySystem.hpp
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
#include "MoveClientEvent.hpp"

namespace potEngine
{
    class MoveClientEntitySystem : public ASystem {
    int tmp = 0;
    public:
        int _serverFd;
        struct sockaddr_in _serverAddr;

        MoveClientEntitySystem(int fd, struct sockaddr_in addr) : _serverFd(fd), _serverAddr(addr)
        {
            engine.subscribeEvent(this, &MoveClientEntitySystem::updateSystem);
        }

        ~MoveClientEntitySystem() {}

        void update(float) override {}

        void movePlayerEntity(std::shared_ptr<AEntity> entity, EventType directionX, EventType directionY)
        {
            if (directionX != MOVE_X_STOP) {
                auto moveInfo = std::make_shared<MoveClientInfoEvent>(
                    -1,
                    _serverAddr,
                    directionX,
                    entity->getID()
                );
                engine.publishEvent(moveInfo);
            } if (directionY != MOVE_Y_STOP) {
                auto moveInfo = std::make_shared<MoveClientInfoEvent>(
                    -1,
                    _serverAddr,
                    directionY,
                    entity->getID()
                );
                engine.publishEvent(moveInfo);
            }
        }

        void moveNonPlayerEntity(std::shared_ptr<AEntity> entity, EventType directionX, EventType directionY)
        {
            if (directionX != MOVE_X_STOP) {
                auto moveInfo = std::make_shared<MoveClientInfoEvent>(
                    -1,
                    _serverAddr,
                    directionX,
                    entity->getID()
                );
                engine.publishEvent(moveInfo);
            } if (directionY != MOVE_Y_STOP) {
                auto moveInfo = std::make_shared<MoveClientInfoEvent>(
                    -1,
                    _serverAddr,
                    directionY,
                    entity->getID()
                );
                engine.publishEvent(moveInfo);
            }
        }

        void updateSystem(std::shared_ptr<NoneEvent> event)
        {
            if (tmp != engine.timer.timerGetTick())
                return;
            tmp = (tmp + 1) % 20;
            for (auto entity : engine.getEntities()) {
                auto moveComponent = entity->getComponent<MovementComponent>();
                if (!moveComponent)
                    continue;
                auto directionX = moveComponent->get()->moveDirectionX;
                auto directionY = moveComponent->get()->moveDirectionY;

                if (directionX == MOVE_X_STOP && directionY == MOVE_Y_STOP) {
                    continue;
                }
                if (entity->getComponent<PlayerComponent>())
                    movePlayerEntity(entity, directionX, directionY);
            }
        }
    };
}
