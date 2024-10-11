#pragma once
#include <vector>
#include <memory>
#include <thread>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"
#include "NoneEvent.hpp"
#include "StopMainLoopEvent.hpp"

namespace potEngine
{
    class MainLoopEvent : public IEvent {
        public:
        bool isRunning;

        MainLoopEvent();

        void eventMainLoop(std::shared_ptr<MainLoopEvent> event);
        void stopMainLoop(std::shared_ptr<StopMainLoopEvent> event);
    };
}
