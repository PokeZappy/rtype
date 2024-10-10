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
            engine.subscribeEvent(this, &MainLoopEvent::stopMainLoop);
        };

        void eventMainLoop(std::shared_ptr<MainLoopEvent> event) {
            if (!isRunning)
                return;
            engine.publishEvent(std::make_shared<NoneEvent>());
            engine.publishEvent(event);
        }

        void stopMainLoop(std::shared_ptr<StopMainLoopEvent> event) {
            isRunning = false;
        }
        bool isRunning = true;
    };
}