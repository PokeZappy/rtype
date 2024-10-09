/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** ShootEntitySystem.hpp
*/

#pragma once

#include "IEvent.hpp"
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "BlcEvent.hpp"
#include "ShootComponent.hpp"
#include "PositionComponent.hpp"
#include "MoveEvent.hpp"

#include <chrono>

namespace potEngine
{
    class ShootEntitySystem : public ASystem {
    public:
        int _serverFd;
        std::chrono::time_point<std::chrono::steady_clock> lastUpdateTime;
        float updateInterval;

        void update(float) override {};

        ShootEntitySystem(int server_fd, float interval) : _serverFd(server_fd), updateInterval(interval)
        {
            lastUpdateTime = std::chrono::steady_clock::now();
            _signature.set(AComponent::getID<ShootComponent>(), true);
            eventBus.subscribe(this, &ShootEntitySystem::updateSystem);
        }

        ~ShootEntitySystem() {}

        void updateSystem(std::shared_ptr<BlcEvent> event)
        {
            auto currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsedTime = currentTime - lastUpdateTime;

            if (elapsedTime.count() >= updateInterval) {
                lastUpdateTime = currentTime;

                auto entities = ecsManager.getEntities();

                for (auto entity : entities) {
                    if (entity->getComponent<ShootComponent>()) {
                        auto moveInfo = std::make_shared<MoveInfoEvent>(
                            4,
                            -1,
                            MOVE_RIGHT,
                            ecsManager.getClientIdFromServerId(entity->getID()),
                            // entity->getID(),
                            std::vector<size_t> {}
                        );
                        eventBus.publish(moveInfo);
                    }
                }
            }
        }
    };
}
