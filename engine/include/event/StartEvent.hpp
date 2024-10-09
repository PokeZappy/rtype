#pragma once

#include <vector>
#include "IEvent.hpp"
#include "EventBus.hpp"
#include "MainLoopEvent.hpp"

namespace potEngine
{
    class MainLoopEvent;
    class StartEvent : public IEvent
    {
        public:
        StartEvent();

        void eventStart(std::shared_ptr<StartEvent>);

        // void addEvent(std::shared_ptr<IEvent> e);

        // std::vector<std::shared_ptr<IEvent>> events;
        std::shared_ptr<MainLoopEvent> _mainLoopEvent;
    };
}