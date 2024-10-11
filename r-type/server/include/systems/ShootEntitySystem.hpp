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
#include "Engine.hpp"
#include "NoneEvent.hpp"
#include "ShootComponent.hpp"
#include "PositionComponent.hpp"
#include "MoveEvent.hpp"

namespace potEngine
{
    class ShootEntitySystem : public ASystem {
    public:
        int _serverFd;

        ShootEntitySystem()
        {
            _signature.set(AComponent::getID<ShootComponent>(), true);
            eventBus.subscribe(this, &ShootEntitySystem::updateSystem);
        }

        ~ShootEntitySystem() {}

        void update(float) override {}

        void updateSystem(std::shared_ptr<NoneEvent> event)
        {
            for (auto entity : _entitiesSystem) {
                auto moveInfo = std::make_shared<MoveInfoEvent>(
                    4,
                    -1,
                    MOVE_RIGHT,
                    entity->getID()
                );
                eventBus.publish(moveInfo);
            }
        }
    };
}
