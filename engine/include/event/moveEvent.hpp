#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "MainLoopEvent.hpp"
#include "EventRender.hpp"

namespace potEngine
{
    enum EventType {
        CONNECTION = 0x01,
        DISCONNECT = 0x02,
        MOVE_UP = 0x03,
        MOVE_DOWN = 0x04,
        MOVE_LEFT = 0x05,
        MOVE_RIGHT = 0x06
    };

    class MoveInfoEvent : public IEvent {
    public:
        int clientId;
        EventType action;
    };

    class MoveEvent : public IEvent
    {
        public:
        MoveEvent() {
            eventBus.subscribe(this, &MoveEvent::move);
        };

        int move(std::shared_ptr<MoveInfoEvent> tmp) {
            if (tmp.get()->action == MOVE_RIGHT)
                return 0;
            return 0;
        }
    };
}