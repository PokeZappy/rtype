#pragma once

#include <vector>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "Engine.hpp"
#include "SendMessageEvent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "ShootComponent.hpp"
#include "MonstreComponent.hpp"
#include "Config.hpp"

namespace potEngine
{
    class SendAllDataInfoEvent : public IEvent {
    public:
        int max_players;
        int fd;
        struct sockaddr_in client_addr;
        size_t player_id;

        SendAllDataInfoEvent(int maxP, int fd, struct sockaddr_in addr, size_t id)
            : max_players(maxP), fd(fd), client_addr(addr), player_id(id) {}
    };

    class SendAllDataEvent : public IEvent {
    public:
        SendAllDataEvent() {
            engine.subscribeEvent(this, &SendAllDataEvent::sendAllData);
        };

        EntityType checkEntity(std::shared_ptr<potEngine::AEntity> entity)
        {
            if (entity->getComponent<PlayerComponent>())
                return EntityType::PLAYER;
            if (entity->getComponent<MonstreComponent>())
                return EntityType::MONSTRE;
            if (entity->getComponent<ShootComponent>())
                return EntityType::PEW;
            else
                return EntityType::NONE_ENTITY;
        }

        void sendAllData(std::shared_ptr<SendAllDataInfoEvent> info)
        {
            if (engine.getEntity(info->player_id) == nullptr)
                return;
            std::vector<std::shared_ptr<AEntity>> _entities = engine.getEntities();
            auto _entitiesPtr = _entities ;

            for (auto entity : _entities) {
                if (entity->getID() == info->player_id)
                    continue;
                std::vector<float> position = entity->getComponent<PositionComponent>()->get()->_position;
                EntityType _entityType = checkEntity(entity);
                std::vector<size_t> _pos;

                if (_entityType == EntityType::PLAYER) {
                    auto username = entity->getComponent<PlayerComponent>()->get()->username;
                    _pos.push_back(_entityType);
                    _pos.push_back(static_cast<size_t>(username.size()));
                    for (char c : username) {
                        _pos.push_back(static_cast<size_t>(c));
                    }
                    _pos.insert(_pos.end(), position.begin(), position.end());
                } else {
                    _pos.push_back(_entityType);
                    _pos.insert(_pos.end(), position.begin(), position.end());
                }

                auto sendMessageEventInfo = std::make_shared<SendMessageEventInfo>(
                    info->max_players,
                    info->fd,
                    info->client_addr,
                    entity->getID(),
                    INFORMATION,
                    _pos
                );
                engine.publishEvent(sendMessageEventInfo);
                std::cout << "[SERVER] Sending data of entity {ID}-[" << static_cast<int>(entity->getID())
                    << "] to {ID}-[" << static_cast<int>(info->player_id) << "]." << std::endl;
            }
        }
    };
}
