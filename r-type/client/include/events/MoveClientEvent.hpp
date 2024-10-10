#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"

#include <netinet/in.h>
#include <vector>
#include <SFML/Graphics.hpp>

namespace potEngine
{
    class MoveClientInfoEvent : public IEvent {
    public:
        int max_players;
        int fd; // TODO: pas besoin
        EventType event;
        size_t entity_id;

        MoveClientInfoEvent(int maxP, int fd, EventType event, size_t id, std::vector<size_t> p)
            : max_players(maxP), fd(fd), event(event), entity_id(id) {}
    };

    class MoveClientEvent : public IEvent {
    public:
        MoveClientEvent() {
            eventBus.subscribe(this, &MoveClientEvent::MoveClient);
        };


        void MoveClient(std::shared_ptr<MoveClientInfoEvent> info)
        {
            auto _entity = ecsManager.getEntity(info->entity_id);
            if (!_entity) {
                std::cout << "[CLIENT] {ID}-[" << static_cast<int>(info->entity_id) << "] not found." << std::endl;
                return;
            }

            int save_x = _entity->getComponent<PositionComponent>()->get()->_position[0];
            int save_y = _entity->getComponent<PositionComponent>()->get()->_position[1];

            auto player_comp = _entity->getComponent<PlayerComponent>();
            std::string username = "";
            if (player_comp)
                username = player_comp->get()->username;

            auto position = _entity->getComponent<PositionComponent>()->get()->_position;
            int speed = _entity->getComponent<MovementComponent>()->get()->speed;
            if (info->event == MOVE_UP && position[1] > 0)
                position[1] = (position[1] > speed) ? position[1] - speed : 0;
            if (info->event == MOVE_DOWN && position[1] < 1080)
                position[1] = (position[1] + speed < 1080) ? position[1] + speed : 1080;
            if (info->event == MOVE_RIGHT && position[0] < 1920)
                position[0] = (position[0] + speed < 1920) ? position[0] + speed : 1920;
            if (info->event == MOVE_LEFT && position[0] > 0)
                position[0] = (position[0] > speed) ? position[0] - speed : 0;

            std::vector<size_t> _pos = {static_cast<size_t>(save_x), static_cast<size_t>(save_y)};

            _entity->getComponent<PositionComponent>()->get()->_position = position;

            // std::cout << "[CLIENT] Entity {ID}-[" << std::to_string(static_cast<int>(info->entity_id))
            //     << "], {username}-[" << username << "], is moving to {" << _pos[0] << "," << _pos[1] << "}" << std::endl;
        }
    };
}
