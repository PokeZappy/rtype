#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"

namespace potEngine
{
    struct BlcEvent : public IEvent
    {
        BlcEvent()
        {
        };
    };
};
