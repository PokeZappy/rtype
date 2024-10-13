#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "Engine.hpp"
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
        EventType event;
        size_t entity_id;

        MoveClientInfoEvent(EventType event, size_t id)
            : event(event), entity_id(id) {}
    };

    class MoveClientEvent : public IEvent {
    public:
        MoveClientEvent() {
            engine.subscribeEvent(this, &MoveClientEvent::MoveClient);
        };


        void MoveClient(std::shared_ptr<MoveClientInfoEvent> info)
        {
            auto _entity = engine.getEntity(info->entity_id);
            if (!_entity) {
                // std::cout << "[CLIENT] {ID}-[" << info->entity_id << "] not found." << std::endl;
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
            if (info->event == MOVE_DOWN && position[1] < 600)
                position[1] = (position[1] + speed < 600) ? position[1] + speed : 600;
            if (info->event == MOVE_RIGHT && position[0] < 800)
                position[0] = (position[0] + speed < 800) ? position[0] + speed : 800;
            if (info->event == MOVE_LEFT && position[0] > 0)
                position[0] = (position[0] > speed) ? position[0] - speed : 0;

            std::vector<size_t> _pos = {static_cast<size_t>(save_x), static_cast<size_t>(save_y)};

            _entity->getComponent<PositionComponent>()->get()->_position = position;

            // std::cout << "[CLIENT] Entity {ID}-[" << std::to_string(static_cast<int>(info->entity_id))
            //     << "], {username}-[" << username << "], is moving to {" << _pos[0] << "," << _pos[1] << "}" << std::endl;
        }
    };
}
