#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "Engine.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "SendMessageEvent.hpp"

#include <netinet/in.h>
#include <vector>
#include <SFML/Graphics.hpp>

namespace potEngine
{
    class MoveClientInfoEvent : public IEvent {
    public:
        int fd;
        struct sockaddr_in _addr;
        EventType event;
        size_t entity_id;
        std::chrono::time_point<std::chrono::high_resolution_clock> _time;

        MoveClientInfoEvent(int fd, struct sockaddr_in addr, EventType event, size_t id)
            : fd(fd), _addr(addr), event(event), entity_id(id)
        {
            _time = std::chrono::high_resolution_clock::now();
        }
    };

    class MoveClientEvent : public IEvent {
    public:
        MoveClientEvent() {
            engine.subscribeEvent(this, &MoveClientEvent::MoveClient);
        };

        std::shared_ptr<AEntity> check_collision(std::shared_ptr<MoveClientInfoEvent> info, std::vector<float> current_pos)
        {
            auto current_entity = engine.getEntity(info->entity_id);
            if (current_entity->getComponent<CollisionComponent>() == nullptr || current_entity->getComponent<PositionComponent>() == nullptr)
                return nullptr;

            for (auto entity : engine.getEntities()) {
                if (entity->getComponent<CollisionComponent>() == nullptr || entity->getComponent<PositionComponent>() == nullptr || entity->getID() == info->entity_id
                    || (entity->getComponent<PlayerComponent>() && current_entity->getComponent<PlayerComponent>()))
                    continue;
                int entity_x = entity->getComponent<PositionComponent>()->get()->_position[0];
                int entity_y = entity->getComponent<PositionComponent>()->get()->_position[1];
                if (entity_x == current_pos[0] && entity_y == current_pos[1]) {
                    return entity;
                }
            }
            return nullptr;
        }

        void MoveClient(std::shared_ptr<MoveClientInfoEvent> info)
        {
            auto _entity = engine.getEntity(info->entity_id);
            if (!_entity)
                return;

            auto _timeTemp = std::chrono::high_resolution_clock::now();
            auto tmp = _timeTemp - info->_time;
            auto multiplicator = std::chrono::duration<double>(tmp).count();

            auto position = _entity->getComponent<PositionComponent>()->get()->_position;
            float speed = _entity->getComponent<MovementComponent>()->get()->speed * multiplicator;


            if (info->event == MOVE_UP && position[1] > 0)
                position[1] = (position[1] - speed > 0) ? position[1] - speed : 0;
            if (info->event == MOVE_DOWN && position[1] < 600)
                position[1] = (position[1] + speed < 600) ? position[1] + speed : 600;
            if (info->event == MOVE_RIGHT && position[0] < 800)
                position[0] = (position[0] + speed < 800) ? position[0] + speed : 800;
            if (info->event == MOVE_LEFT && position[0] > 0)
                position[0] = (position[0] - speed > 0) ? position[0] - speed : 0;

            auto entity_collide = check_collision(info, position);
            if (entity_collide == nullptr) {
                if (info->fd != -1) {
                    if (info->event == MOVE_UP || info->event == MOVE_DOWN || info->event == MOVE_Y_STOP)
                        _entity->getComponent<MovementComponent>()->get()->moveDirectionY = info->event;
                    if (info->event == MOVE_RIGHT || info->event == MOVE_LEFT || info->event == MOVE_X_STOP)
                        _entity->getComponent<MovementComponent>()->get()->moveDirectionX = info->event;
                }
                _entity->getComponent<PositionComponent>()->get()->_position = position;
            }

            if (info->fd != -1) {
                auto sendInfo = std::make_shared<potEngine::SendMessageEventInfo>(MAX_PLAYERS, info->fd, info->_addr, info->entity_id, info->event, std::vector<size_t>{position.begin(), position.end()});
                potEngine::engine.publishEvent(sendInfo);
            }
        }
    };
}
