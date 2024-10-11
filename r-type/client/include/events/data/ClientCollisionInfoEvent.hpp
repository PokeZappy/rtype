#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "Engine.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "LifeComponent.hpp"
#include "ShootComponent.hpp"

namespace potEngine
{
    class ClientCollisionInfoEvent : public IEvent {
    public:
        size_t colliding_entity_id; // l'ID de l'entité qui entre en collision avec une autre
        size_t collided_entity_id; // l'ID de l'entité qui subit la collision

        ClientCollisionInfoEvent(size_t colliding_entity_id, size_t collided_entity_id)
            : colliding_entity_id(colliding_entity_id), collided_entity_id(collided_entity_id) {}
    };
};