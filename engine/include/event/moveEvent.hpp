#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "MainLoopEvent.hpp"
#include "EventRender.hpp"

namespace potEngine
{
    class MoveInfoEvent : public IEvent {
    public:
        int clientId;
        EventType action;
        // entiities
    };

    class MoveEvent : public IEvent {
    public:
        MoveEvent() {
            // eventBus.subscribe(this, &MoveEvent::move);
        };

        int move(std::shared_ptr<MoveInfoEvent> tmp) {
            if (tmp.get()->action == MOVE_RIGHT)
                return 0;
            return 0;
        }
    };
}