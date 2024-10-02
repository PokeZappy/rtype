#pragma once
#include <vector>
#include <memory>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"
// #include "EventRender.hpp"

namespace potEngine
{
    struct MainLoopEvent : public IEvent
    {
        MainLoopEvent()
        {
            eventBus.subscribe(this, &MainLoopEvent::eventMainLoop);
        };

        void eventMainLoop(std::shared_ptr<MainLoopEvent> event) {
            eventBus.publish(event);
        }

        void addEventMainLoop(std::shared_ptr<IEvent> event) {
            eventBus.publish(event);
        };
    };
}