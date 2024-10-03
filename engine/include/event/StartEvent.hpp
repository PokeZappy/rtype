#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "MainLoopEvent.hpp"
#include "EventRender.hpp"

namespace potEngine
{
    class StartEvent : public IEvent
    {
        public:
        StartEvent() {
            eventBus.subscribe(this, &StartEvent::eventStart);
        };

        void eventStart(std::shared_ptr<StartEvent>) {

            if (!_mainLoopEvent) {
                _mainLoopEvent = std::make_shared<MainLoopEvent>(events);
            }
            eventBus.subscribe(_mainLoopEvent.get(), &MainLoopEvent::eventMainLoop);
            eventBus.publish(_mainLoopEvent);
        };

        void addEvent(std::shared_ptr<IEvent> e) {
            events.push_back(e);
        }
        std::vector<std::shared_ptr<IEvent>> events;
        std::shared_ptr<MainLoopEvent> _mainLoopEvent;
    };
}