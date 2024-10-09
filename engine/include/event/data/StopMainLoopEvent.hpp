#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"

namespace potEngine
{
    class StopMainLoopEvent : public IEvent {
    public:
        StopMainLoopEvent() {}
    };
};