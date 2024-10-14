#pragma once

namespace potEngine
{
    enum EventType {
        UNKNOW = 0x00,
        CONNECTION = 0x01,
        DISCONNECT = 0x02,
        INFORMATION = 0x03,
        MOVE_UP = 0x04,
        MOVE_DOWN = 0x05,
        MOVE_LEFT = 0x06,
        MOVE_RIGHT = 0x07,
        MOVE_X_STOP = 0x08,
        MOVE_Y_STOP = 0x09,
        COLLISION = 0x10,
        DEATH = 0x11,
        SHOOT = 0x12
    };
    // TODO à enlever

    enum EntityType {
        NONE = 0x00,
        PLAYER = 0x01,
        MONSTRE = 0x02,
        PEW = 0x03
    };

    class IEvent {
    public:
        virtual ~IEvent() = default;
    };
}
