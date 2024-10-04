#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "SendMessageToAllEvent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"

#include <netinet/in.h>
#include <vector>

namespace potEngine
{
    class MoveInfoEvent : public IEvent {
    public:
        int max_players;
        int socket;
        EventType event;
        uint8_t entity_id;
        std::shared_ptr<ECSManager> ecs_manager;

        MoveInfoEvent(int maxP, int socket, EventType event, uint8_t id, std::vector<uint16_t> p, std::shared_ptr<ECSManager> ecs)
            : max_players(maxP), socket(socket), event(event), entity_id(id), ecs_manager(ecs) {}
    };

    class MoveEvent : public IEvent {
    public:
        MoveEvent() {
            eventBus.subscribe(this, &MoveEvent::Move);
        };

        void Move(std::shared_ptr<MoveInfoEvent> info) {
            auto _entity = info->ecs_manager->getEntity(info->entity_id);
            if (!_entity) {
                std::cout << "[SERVER] {ID}-[" << static_cast<int>(info->entity_id) << "] not found." << std::endl;
                return;
            }
            auto position = _entity->getComponent<PositionComponent>()->get()->_position;
            auto username = _entity->getComponent<PlayerComponent>()->get()->username;
            if (info->event == MOVE_UP && position[1] < 1920)
                position[1] += 1;
            if (info->event == MOVE_DOWN && position[1] > 0)
                position[1] -= 1;
            if (info->event == MOVE_RIGHT && position[0] < 1080)
                position[0] += 1;
            if (info->event == MOVE_LEFT && position[0] > 0)
                position[0] -= 1;
            _entity->getComponent<PositionComponent>()->get()->_position = position;
            std::vector<uint16_t> _pos(position.begin(), position.end());

            auto sendMessageEventInfo = std::make_shared<SendMessageToAllEventInfo>(
                info->max_players,
                info->socket,
                info->entity_id,
                info->event,
                _pos,
                info->ecs_manager->getEntities()
            );
            eventBus.publish(sendMessageEventInfo);
            std::cout << "[SERVER] Entity {ID}-[" << std::to_string(static_cast<int>(info->entity_id))
                << "], {username}-[" << username << "], is moving to {" << position[0] << "," << position[1] << "}" << std::endl;
        }
    };
}
