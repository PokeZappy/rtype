#pragma once

namespace potEngine
{
    enum EventType {
        UNKNOW = 0x00,
        CONNECTION = 0x01,
        DISCONNECT = 0x02,
        MOVE_UP = 0x03,
        MOVE_DOWN = 0x04,
        MOVE_LEFT = 0x05,
        MOVE_RIGHT = 0x06
    };

    class IEvent {
    public:
        virtual ~IEvent() = default;
    };
}