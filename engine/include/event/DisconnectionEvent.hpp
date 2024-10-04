#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "SendMessageToAllEvent.hpp"
#include "PlayerComponent.hpp"
#include "NetworkComponent.hpp"

#include <netinet/in.h>
#include <vector>

namespace potEngine
{
    class DisconnectionInfoEvent : public IEvent {
    public:
        int max_players;
        int socket;
        uint8_t entity_id;
        std::vector<uint16_t> params;
        std::shared_ptr<ECSManager> ecs_manager;

        DisconnectionInfoEvent(int maxP, int socket, uint8_t id, std::vector<uint16_t> p, std::shared_ptr<ECSManager> ecs)
            : max_players(maxP), socket(socket), entity_id(id), params(p), ecs_manager(ecs) {}
    };

    class DisconnectionEvent : public IEvent {
    public:
        DisconnectionEvent() {
            eventBus.subscribe(this, &DisconnectionEvent::disconnect);
        };

        void disconnect(std::shared_ptr<DisconnectionInfoEvent> info) {
            std::string player_name = info->ecs_manager.get()->getEntity(info->entity_id).get()->getComponent<potEngine::PlayerComponent>()->get()->username;
            info->ecs_manager->removeEntity(info->entity_id);
            // std::cout << "[SERVER] Player disconnected: {id}-[" << std::to_string(static_cast<int>(info->entity_id)) << "], {username}-[" << player_name << "]" << std::endl;

            auto sendMessageToAllEventInfo = std::make_shared<SendMessageToAllEventInfo>(info->max_players, info->socket, info->entity_id, DISCONNECT, info->params, info->ecs_manager->getEntities());
            eventBus.publish(sendMessageToAllEventInfo);
        }
    };
}
