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
        int fd;
        size_t entity_id;
        std::vector<size_t> params;

        DisconnectionInfoEvent(int maxP, int fd, size_t id, std::vector<size_t> p)
            : max_players(maxP), fd(fd), entity_id(id), params(p) {}
    };

    class DisconnectionEvent : public IEvent {
    public:
        DisconnectionEvent() {
            eventBus.subscribe(this, &DisconnectionEvent::disconnect);
        };

        void disconnect(std::shared_ptr<DisconnectionInfoEvent> info) {
            if (ecsManager.getEntity(info->entity_id) == nullptr)
                return;
            std::string player_name = ecsManager.getEntity(info->entity_id).get()->getComponent<potEngine::PlayerComponent>()->get()->username;
            std::cout << "[SERVER] Player disconnected: {id}-[" << std::to_string(static_cast<int>(info->entity_id)) << "], {username}-[" << player_name << "]" << std::endl;

            auto sendMessageToAllEventInfo = std::make_shared<SendMessageToAllEventInfo>(
                info->max_players,
                info->fd,
                info->entity_id,
                DISCONNECT,
                info->params,
                ecsManager.getEntities()
            );
            eventBus.publish(sendMessageToAllEventInfo);
        }
    };
}
