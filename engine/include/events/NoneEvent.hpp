#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"

namespace potEngine
{
    /*!
    * @brief Event class representing a no-operation event.
    */
    struct NoneEvent : public IEvent
    {
        NoneEvent()
        {
        };
    };
};
