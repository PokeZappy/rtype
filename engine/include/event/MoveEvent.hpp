#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "SendMessageToAllEvent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "CollisionComponent.hpp"
#include "CollisionEvent.hpp"

#include <netinet/in.h>
#include <vector>

namespace potEngine
{
    class MoveInfoEvent : public IEvent {
    public:
        int max_players;
        int fd;
        EventType event;
        uint8_t entity_id;

        MoveInfoEvent(int maxP, int fd, EventType event, uint8_t id, std::vector<uint16_t> p)
            : max_players(maxP), fd(fd), event(event), entity_id(id) {}
    };

    class MoveEvent : public IEvent {
    public:
        MoveEvent() {
            eventBus.subscribe(this, &MoveEvent::Move);
        };

        std::shared_ptr<AEntity> check_collision(std::shared_ptr<MoveInfoEvent> info, std::vector<int> current_pos)
        {
            auto current_entity = ecsManager.getEntity(info->entity_id);
            if (current_entity->getComponent<CollisionComponent>() == nullptr || current_entity->getComponent<PositionComponent>() == nullptr)
                return nullptr;

            for (auto entity : ecsManager.getEntities()) {
                if (entity->getComponent<CollisionComponent>() == nullptr || entity->getComponent<PositionComponent>() == nullptr || entity->getID() == info->entity_id || entity->getComponent<PlayerComponent>())
                    continue;
                int entity_x = entity->getComponent<PositionComponent>()->get()->_position[0];
                int entity_y = entity->getComponent<PositionComponent>()->get()->_position[1];
                if (entity_x == current_pos[0] && entity_y == current_pos[1]) {
                    return entity;
                }
            }
            return nullptr;
        }

        void Move(std::shared_ptr<MoveInfoEvent> info)
        {
            auto _entity = ecsManager.getEntity(info->entity_id);
            if (!_entity) {
                std::cout << "[SERVER] {ID}-[" << static_cast<int>(info->entity_id) << "] not found." << std::endl;
                return;
            }
            int save_x = _entity->getComponent<PositionComponent>()->get()->_position[0];
            int save_y = _entity->getComponent<PositionComponent>()->get()->_position[1];

            auto position = _entity->getComponent<PositionComponent>()->get()->_position;
            auto username = _entity->getComponent<PlayerComponent>()->get()->username;
            int speed = _entity->getComponent<MovementComponent>()->get()->speed;
            if (info->event == MOVE_UP && position[1] > 0)
                position[1] = (position[1] > speed) ? position[1] - speed : 0;
            if (info->event == MOVE_DOWN && position[1] < 1080)
                position[1] = (position[1] + speed < 1080) ? position[1] + speed : 1080;
            if (info->event == MOVE_RIGHT && position[0] < 1920)
                position[0] = (position[0] + speed < 1920) ? position[0] + speed : 1920;
            if (info->event == MOVE_LEFT && position[0] > 0)
                position[0] = (position[0] > speed) ? position[0] - speed : 0;

            auto entity_collide = check_collision(info, position);
            std::vector<uint16_t> _pos = {static_cast<uint16_t>(save_x), static_cast<uint16_t>(save_y)};
            if (entity_collide == nullptr) {
                _entity->getComponent<PositionComponent>()->get()->_position = position;
                _pos = {position.begin(), position.end()};
            } else {
                auto collisionEventInfo = std::make_shared<CollisionInfoEvent>(
                    info->max_players,
                    info->fd,
                    info->entity_id,
                    static_cast<uint8_t>(entity_collide->getID())
                );
                eventBus.publish(collisionEventInfo);
            }
            auto sendMessageEventInfo = std::make_shared<SendMessageToAllEventInfo>(
                info->max_players,
                info->fd,
                info->entity_id,
                info->event,
                _pos,
                ecsManager.getEntities()
            );
            eventBus.publish(sendMessageEventInfo);
            std::cout << "[SERVER] Entity {ID}-[" << std::to_string(static_cast<int>(info->entity_id))
                << "], {username}-[" << username << "], is moving to {" << _pos[0] << "," << _pos[1] << "}" << std::endl;
        }
    };
}
