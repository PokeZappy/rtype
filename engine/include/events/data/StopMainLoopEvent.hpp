#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "Engine.hpp"

namespace potEngine
{
    class StopMainLoopEvent : public IEvent {
    public:
        StopMainLoopEvent() {}
    };
};