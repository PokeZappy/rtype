#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "Engine.hpp"
#include "SendMessageToAllEvent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "CollisionComponent.hpp"
#include "CollisionEvent.hpp"

#include <netinet/in.h>
#include <vector>
#include <SFML/Graphics.hpp>

namespace potEngine
{
    class MoveServerInfoEvent : public IEvent {
    public:
        int max_players;
        int fd;
        EventType event;
        size_t entity_id;
        std::chrono::time_point<std::chrono::high_resolution_clock> _time;

        MoveServerInfoEvent(int maxP, int fd, EventType event, size_t id)
            : max_players(maxP), fd(fd), event(event), entity_id(id)
        {
            _time = std::chrono::high_resolution_clock::now();
        }
    };

    class MoveServerEvent : public IEvent {
    public:
        MoveServerEvent() {
            engine.subscribeEvent(this, &MoveServerEvent::Move);
        };

        std::shared_ptr<AEntity> check_collision(std::shared_ptr<MoveServerInfoEvent> info, std::vector<float> current_pos)
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

        int removeShoot(std::shared_ptr<potEngine::AEntity> entity, std::shared_ptr<MoveServerInfoEvent> info)
        {
            auto posComponent = entity->getComponent<PositionComponent>();
            auto shootComponent = entity->getComponent<ShootComponent>();

            if (!shootComponent || !posComponent)
                return 0;

            if ((info->event == MOVE_RIGHT && posComponent->get()->_position[0] == 800) ||
                (info->event == MOVE_LEFT && posComponent->get()->_position[0] == 0)) {
                auto sendMessageToAllEventInfo = std::make_shared<SendMessageToAllEventInfo>(
                    info->max_players,
                    info->fd,
                    entity->getID(),
                    DEATH,
                    std::vector<size_t>{},
                    engine.getEntities()
                );
                engine.publishEvent(sendMessageToAllEventInfo);
                return 1;
            }
            if ((info->event == MOVE_RIGHT && posComponent->get()->_position[0] > 800) ||
                (info->event == MOVE_LEFT && posComponent->get()->_position[0] < 0)) {
                return 1;
            }
            return 0;
        }

        void Move(std::shared_ptr<MoveServerInfoEvent> info)
        {
            auto _entity = engine.getEntity(info->entity_id);
            if (!_entity || removeShoot(_entity, info))
                return;

            auto _timeTemp = std::chrono::high_resolution_clock::now();
            auto tmp = _timeTemp - info->_time;
            auto multiplicator = std::chrono::duration<double>(tmp).count();

            int save_x = _entity->getComponent<PositionComponent>()->get()->_position[0];
            int save_y = _entity->getComponent<PositionComponent>()->get()->_position[1];

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
            std::vector<size_t> _pos = {static_cast<size_t>(save_x), static_cast<size_t>(save_y)};
            if (entity_collide == nullptr) {
                _entity->getComponent<PositionComponent>()->get()->_position = position;
                _pos = {position.begin(), position.end()};
            } else {
                auto collisionEventInfo = std::make_shared<CollisionInfoEvent>(
                    info->max_players,
                    info->fd,
                    info->entity_id,
                    entity_collide->getID()
                );
                engine.publishEvent(collisionEventInfo);
            }
            if (info->fd != -1) {
                auto sendMessageEventInfo = std::make_shared<SendMessageToAllEventInfo>(
                    info->max_players,
                    info->fd,
                    info->entity_id,
                    info->event,
                    _pos,
                    engine.getEntities()
                );
                engine.publishEvent(sendMessageEventInfo);
            }
        }
    };
}
