#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "SendMessageEvent.hpp"
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
            std::vector<std::shared_ptr<AEntity>> _entities = info->ecs_manager->getEntities();

            for (auto entity : _entities) {
                std::vector<uint16_t> _pos = entity->getComponent<PositionComponent>()->get()->_position;
                auto sendMessageEventInfo = std::make_shared<SendMessageEventInfo>(info->max_players, info->socket, info->client_addr, info->entity_id, GETINFO, std::vector<uint16_t>{});
                eventBus.publish(sendMessageEventInfo);
            }
        }
    };
}
