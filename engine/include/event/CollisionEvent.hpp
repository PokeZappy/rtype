#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "SendMessageToAllEvent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "LifeComponent.hpp"

#include <netinet/in.h>
#include <vector>

namespace potEngine
{
    class CollisionInfoEvent : public IEvent {
    public:
        int max_players;
        int player_fd;
        uint8_t player_id;
        uint8_t entity_id;

        CollisionInfoEvent(int maxP, int player_fd,  uint8_t player_id, uint8_t entity_id)
            : max_players(maxP), player_fd(player_fd), player_id(player_id), entity_id(entity_id) {}
    };

    class CollisionEvent : public IEvent {
    public:
        CollisionEvent() {
            eventBus.subscribe(this, &CollisionEvent::Collision);
        };

        // EVENT PUBLISH MES COUILLES

        void Collision(std::shared_ptr<CollisionInfoEvent> info)
        {
            auto player = ecsManager.getEntity(info->player_id);
            if (player == nullptr) {
                return;
            }

            auto username = player->getComponent<PlayerComponent>()->get()->username;
            auto life = player->getComponent<LifeComponent>()->get()->life--;
            std::cout << "[SERVER] Entity {ID}-[" << std::to_string(static_cast<int>(info->entity_id))
                << "], {username}-[" << username << "] collide and has now {LIFE}-[" << life << "]" << std::endl;

            if (life < 0) {
                // todo implémenter la death
            }
        }
    };
}
