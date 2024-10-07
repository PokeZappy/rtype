#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "SendMessageToAllEvent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "MovementComponent.hpp"
#include "ShootComponent.hpp"
#include "MonstreComponent.hpp"

#include <netinet/in.h>
#include <vector>

namespace potEngine
{
    class EntityCreateInfoEvent : public IEvent {
    public:
        int max_players;
        int fd;
        EntityType _entityType;

        EntityCreateInfoEvent(int maxP, int fd, EntityType type)
            : max_players(maxP), fd(fd), _entityType(type) {}
    };

    class EntityCreateEvent : public IEvent {
    public:
        EntityCreateEvent() {
            eventBus.subscribe(this, &EntityCreateEvent::EntityCreate);
        };

        void EntityCreate(std::shared_ptr<EntityCreateInfoEvent> info)
        {
            auto entity = ecsManager.createEntity();
            auto entity_id = entity->getID();

            std::vector<uint16_t> _pos;
            _pos.push_back(info->_entityType);
            // _pos.insert(_pos.end(), position.begin(), position.end());

            auto sendMessageToAllEventInfo = std::make_shared<SendMessageToAllEventInfo>(
                info->max_players,
                info->fd,
                entity_id,
                INFORMATION,
                _pos,
                ecsManager.getEntities()
            );
            eventBus.publish(sendMessageToAllEventInfo);

            std::cout << "[SERVER] New entity created {ID}-[" << static_cast<int>(entity_id) << "] {TYPE}-[" << info->_entityType << "]" << std::endl;
        }
    };
}
