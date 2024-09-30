/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** Event.hpp
*/

#ifndef EVENT_HPP
#define EVENT_HPP

#include <queue>
#include <tuple>
#include <mutex>

namespace polEngine
{
    enum EventType {
        CONNECTION = 0x01,
        DISCONNECT = 0x02,
        MOVE_UP = 0x03,
        MOVE_DOWN = 0x04,
        MOVE_LEFT = 0x05,
        MOVE_RIGHT = 0x06
    };

    class Event {
    public:
        int clientId;
        EventType action;

        Event(int id, EventType act) : clientId(id), action(act) {}
    };
}

#endif // EVENT_HPP
