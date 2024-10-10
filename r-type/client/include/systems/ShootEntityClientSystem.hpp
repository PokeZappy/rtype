/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** ShootEntityClientSystem.hpp
*/

#pragma once

#include "IEvent.hpp"
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "NoneEvent.hpp"
#include "ShootComponent.hpp"
#include "PositionComponent.hpp"
#include "MoveClientEvent.hpp"

#include <chrono>

namespace potEngine
{
    class ShootEntityClientSystem : public ASystem {
    public:
        int _serverFd;
        std::chrono::time_point<std::chrono::steady_clock> lastUpdateTime;
        float updateInterval;
        int i = 0;

        void update(float) override {};

        ShootEntityClientSystem(int server_fd, float interval) : _serverFd(server_fd), updateInterval(interval)
        {
            lastUpdateTime = std::chrono::steady_clock::now();
            _signature.set(AComponent::getID<ShootComponent>(), true);
            eventBus.subscribe(this, &ShootEntityClientSystem::updateSystem);
        }

        ~ShootEntityClientSystem() {}

        void updateSystem(std::shared_ptr<NoneEvent> event)
        {
            auto currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsedTime = currentTime - lastUpdateTime;

            if (elapsedTime.count() >= updateInterval) {
                lastUpdateTime = currentTime;

                for (auto entity : _entitiesSystem) {
                    // std::cout << "I: " << i++ << std::endl;
                    auto moveInfo = std::make_shared<MoveClientInfoEvent>(
                        4,
                        -1,
                        MOVE_RIGHT,
                        ecsManager.getClientIdFromServerId(entity->getID()),
                        std::vector<size_t> {}
                    );
                    eventBus.publish(moveInfo);
                }
            }
        }
    };
}
