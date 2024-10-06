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
    class SendAllDataInfoEvent : public IEvent {
    public:
        int max_players;
        int fd;
        struct sockaddr_in client_addr;
        uint8_t entity_id;

        SendAllDataInfoEvent(int maxP, int fd, struct sockaddr_in c_addr)
            : max_players(maxP), fd(fd), client_addr(c_addr) {}
    };

    class SendAllDataEvent : public IEvent {
    public:
        SendAllDataEvent() {
            eventBus.subscribe(this, &SendAllDataEvent::sendAllData);
        };

        void sendAllData(std::shared_ptr<SendAllDataInfoEvent> info)
        {
            if (ecsManager.getEntity(info->entity_id) == nullptr)
                return;
            // todo

            // std::vector<std::shared_ptr<AEntity>> _entities = ecsManager.getEntities();
            // auto _entitiesPtr = _entities ;

            // for (auto entity : _entities) {
            //     std::vector<int> position = entity->getComponent<PositionComponent>()->get()->_position;
            //     std::vector<uint16_t> _pos(position.begin(), position.end());

            //     auto sendMessageEventInfo = std::make_shared<SendMessageToAllEvent>(info->max_players, info->fd, info->entity_id, GETINFO, _pos, info->ecs_manager);
            //     eventBus.publish(sendMessageEventInfo);
            // }
        }
    };
}
