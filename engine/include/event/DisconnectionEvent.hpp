#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"
#include "SendMessageEvent.hpp"

#include <netinet/in.h>
#include <vector>

namespace potEngine
{
    class DisconnectionInfoEvent : public IEvent {
    public:
        int max_players;
        int socket;
        struct sockaddr_in client_addr;
        std::vector<uint16_t> params;
        std::shared_ptr<ECSManager> ecs_manager;

        DisconnectionInfoEvent(int maxP, int socket, struct sockaddr_in c_addr, std::vector<uint16_t> p, std::shared_ptr<ECSManager> ecs)
            : max_players(maxP), socket(socket), client_addr(c_addr), params(p), ecs_manager(ecs) {}
    };

    class DisconnectionEvent : public IEvent {
    public:
        DisconnectionEvent() {
            eventBus.subscribe(this, &DisconnectionEvent::disconnect);
        };

        void disconnect(std::shared_ptr<DisconnectionInfoEvent> info) {
            // todo
        }
    };
}
