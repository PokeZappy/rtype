#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "MainLoopEvent.hpp"

namespace potEngine
{
    struct StartEvent : public IEvent
    {
        StartEvent() {
            eventBus.subscribe(this, &StartEvent::eventStart);
        };

        void eventStart(std::shared_ptr<StartEvent>) {
            if (!_mainLoopEvent) {
                _mainLoopEvent = std::make_shared<MainLoopEvent>();
            }
            eventBus.subscribe(_mainLoopEvent.get(), &MainLoopEvent::eventMainLoop);
            eventBus.publish(std::make_shared<MainLoopEvent>());
        };
        std::shared_ptr<MainLoopEvent> _mainLoopEvent;
    };
}