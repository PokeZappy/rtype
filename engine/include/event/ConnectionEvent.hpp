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
    class ConnectionInfoEvent : public IEvent {
    public:
        int max_players;
        int socket;
        struct sockaddr_in client_addr;
        std::vector<uint16_t> params;
        std::shared_ptr<ECSManager> ecs_manager;

        ConnectionInfoEvent(int maxP, int socket, struct sockaddr_in c_addr, std::vector<uint16_t> p, std::shared_ptr<ECSManager> ecs)
            : max_players(maxP), socket(socket), client_addr(c_addr), params(p), ecs_manager(ecs) {}
    };

    class ConnectionEvent : public IEvent {
    public:
        ConnectionEvent() {
            eventBus.subscribe(this, &ConnectionEvent::connect);
        };

        void connect(std::shared_ptr<ConnectionInfoEvent> info) {
            auto player_entity = info->ecs_manager->createEntity();
            uint8_t player_id = player_entity->getID();
            std::string player_name;

            if (info->params.empty()) {
                player_name = "Player_" + std::to_string(static_cast<int>(player_id));
            } else {
                player_name.assign(info->params.begin(), info->params.end());
            }

            std::shared_ptr<PlayerComponent> playerComponent = std::make_shared<PlayerComponent>(player_name);
            std::shared_ptr<PositionComponent> positionComponent = std::make_shared<PositionComponent>(0.0f, 0.0f);
            std::shared_ptr<MovementComponent> movementComponent = std::make_shared<MovementComponent>(1.0f);
            std::shared_ptr<NetworkComponent> networkComponent = std::make_shared<NetworkComponent>(info->client_addr);

            info->ecs_manager->addComponent(player_entity, playerComponent);
            info->ecs_manager->addComponent(player_entity, positionComponent);
            info->ecs_manager->addComponent(player_entity, movementComponent);
            info->ecs_manager->addComponent(player_entity, networkComponent);

            std::cout << "[SERVER] Player connected: {id}-[" << std::to_string(static_cast<int>(player_id)) << "], {username}-[" << player_name << "]" << std::endl;

            std::vector<uint16_t> _sendId = {static_cast<uint16_t>(player_id)};
            auto sendMessageEventInfo = std::make_shared<SendMessageEventInfo>(info->max_players, info->socket, info->client_addr, 0, CONNECTION, _sendId);
            eventBus.publish(sendMessageEventInfo);

            auto sendMessageToAllEventInfo = std::make_shared<SendMessageToAllEventInfo>(info->max_players, info->socket, player_id, CONNECTION, info->params, info->ecs_manager->getEntities());
            eventBus.publish(sendMessageToAllEventInfo);
        }
    };
}
