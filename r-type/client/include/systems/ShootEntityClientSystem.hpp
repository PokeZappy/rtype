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
#include "Engine.hpp"
#include "NoneEvent.hpp"
#include "ShootComponent.hpp"
#include "PositionComponent.hpp"
#include "MoveClientEvent.hpp"

namespace potEngine
{
    class ShootEntityClientSystem : public ASystem {
    public:
        int _serverFd;

        ShootEntityClientSystem()
        {
            _signature.set(AComponent::getID<ShootComponent>(), true);
            engine.subscribeEvent(this, &ShootEntityClientSystem::updateSystem);
        }

        ~ShootEntityClientSystem() {}

        void update(float) override {}

        void updateSystem(std::shared_ptr<NoneEvent> event)
        {
            for (auto entity : _entitiesSystem) {
                auto moveInfo = std::make_shared<MoveClientInfoEvent>(
                    MOVE_RIGHT,
                    engine.getClientIdFromServerId(entity->getID())
                );
                engine.publishEvent(moveInfo);
            }
        }
    };
}

