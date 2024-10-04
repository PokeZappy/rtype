#pragma once
#include <vector>
#include <memory>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"
#include "EventRender.hpp"

namespace potEngine
{
    struct MainLoopEvent : public IEvent
    {
        MainLoopEvent(std::vector<std::shared_ptr<IEvent>> eventsList) : events(eventsList) 
        {
        };

        void eventMainLoop(std::shared_ptr<MainLoopEvent> event) {

            for (auto event : events) {
                auto test = std::static_pointer_cast<EventRender>(event);
                eventBus.publish(test);
            }
            eventBus.publish(event);
        }

        std::vector<std::shared_ptr<IEvent>> events;
    };
}