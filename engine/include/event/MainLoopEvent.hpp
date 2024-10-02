#pragma once
#include <vector>
#include <memory>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"
#include "EventRender.hpp"
#include "InputSystem.hpp"

namespace potEngine
{
    struct MainLoopEvent : public IEvent
    {
        MainLoopEvent(std::vector<std::shared_ptr<IEvent>> eventsList) : events(eventsList) 
        {
            eventBus.subscribe(this, &MainLoopEvent::eventMainLoop);
        };

        void eventMainLoop(std::shared_ptr<MainLoopEvent> event) {
            int i = 0;
            for (auto e : events) {
                // if (i == 0) {
                //     auto test = std::static_pointer_cast<EventRender>(e);
                //     eventBus.publish(test);
                // } else {
                //     auto test = std::static_pointer_cast<ComputeInputEvent>(e);
                //     eventBus.publish(test);
                // }
                // std::cout << "event type: " << typeid(e).name() << std::endl;
                auto renderEvent = std::static_pointer_cast<EventRender>(e);
                eventBus.publish(renderEvent);
                i++;
            }
            eventBus.publish(event);
        }

        std::vector<std::shared_ptr<IEvent>> events;
    };
}