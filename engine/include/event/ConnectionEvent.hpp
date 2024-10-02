#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"

#include <netinet/in.h>

namespace potEngine
{
    struct ConnectionInfoEvent : public IEvent
    {
        struct sockaddr_in client_addr;
        std::vector<uint16_t> params;
        std::shared_ptr<ECSManager> ecs_manager;
    };

    class ConnectionEvent : public IEvent {
    public:
        ConnectionEvent() {
            eventBus.subscribe(this, &ConnectionEvent::connect);
        };

        void connect(std::shared_ptr<ConnectionInfoEvent> info) {
            // handle_client_connection();
            return;
        };
    };
}