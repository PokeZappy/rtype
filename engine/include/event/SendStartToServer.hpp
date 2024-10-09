#pragma once

#include <memory>

#include "IEvent.hpp"
#include "EventBus.hpp"

namespace potEngine
{
    class SendStartToServer : public IEvent
    {

    public:
        SendStartToServer() {
            eventBus.subscribe(this, &SendStartToServer::sendStartToServer);
        };
        ~SendStartToServer() = default;
        void sendStartToServer(std::shared_ptr<SendStartToServer> event)  {
            
        };
    };
} // namespace potEngine