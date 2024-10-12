#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "Engine.hpp"
#include "SendMessageToAllEvent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "LifeComponent.hpp"
#include "ShootComponent.hpp"

namespace potEngine
{
    class CollisionInfoEvent : public IEvent {
    public:
        int max_players;
        int player_fd;
        size_t colliding_entity_id; // l'ID de l'entité qui entre en collision avec une autre
        size_t collided_entity_id; // l'ID de l'entité qui subit la collision

        CollisionInfoEvent(int maxP, int player_fd,  size_t colliding_entity_id, size_t collided_entity_id)
            : max_players(maxP), player_fd(player_fd), colliding_entity_id(colliding_entity_id), collided_entity_id(collided_entity_id) {}
    };
};