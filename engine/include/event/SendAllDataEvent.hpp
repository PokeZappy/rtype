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
        int socket;
        struct sockaddr_in client_addr;
        uint8_t entity_id;
        std::shared_ptr<ECSManager> ecs_manager;

        SendAllDataInfoEvent(int maxP, int socket, struct sockaddr_in c_addr, std::vector<uint16_t> p, std::shared_ptr<ECSManager> ecs)
            : max_players(maxP), socket(socket), client_addr(c_addr), ecs_manager(ecs) {}
    };

    class SendAllDataEvent : public IEvent {
    public:
        SendAllDataEvent() {
            eventBus.subscribe(this, &SendAllDataEvent::sendAllData);
        };

        void sendAllData(std::shared_ptr<SendAllDataInfoEvent> info) {
            // todo

            // std::vector<std::shared_ptr<AEntity>> _entities = info->ecs_manager->getEntities();
            // auto _entitiesPtr = _entities ;

            // for (auto entity : _entities) {
            //     std::vector<int> position = entity->getComponent<PositionComponent>()->get()->_position;
            //     std::vector<uint16_t> _pos(position.begin(), position.end());

            //     auto sendMessageEventInfo = std::make_shared<SendMessageToAllEvent>(info->max_players, info->socket, info->entity_id, GETINFO, _pos, info->ecs_manager);
            //     eventBus.publish(sendMessageEventInfo);
            // }
        }
    };
}
