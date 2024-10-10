#pragma once
#include <vector>
#include <memory>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"
#include "NoneEvent.hpp"
#include "StopMainLoopEvent.hpp"

namespace potEngine
{
    struct MainLoopEvent : public IEvent
    {
        MainLoopEvent()
        {
            eventBus.subscribe(this, &MainLoopEvent::stopMainLoop);
        };

        void eventMainLoop(std::shared_ptr<MainLoopEvent> event) {
            if (!isRunning)
                return;
            eventBus.publish(std::make_shared<NoneEvent>());
            eventBus.publish(event);
        }

        void stopMainLoop(std::shared_ptr<StopMainLoopEvent> event) {
            isRunning = false;
        }
        bool isRunning = true;
    };
}