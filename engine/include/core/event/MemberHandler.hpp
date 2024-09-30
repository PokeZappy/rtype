#pragma once

#include <memory>

#include "AEventHandler.hpp"

namespace potEngine {
    template<class T, class EventType>
    class MemberHandler : public 
    {
    public:
        typedef void (T::*MemberFunction)(std::shared_ptr<EventType>);

        MemberFunctionHandler(T* instance, MemberFunction memberFunction) : instance{ instance }, memberFunction{ memberFunction } {};
        void call(std::shared_ptr<Event> evnt) {
            (instance->*memberFunction)(static_pointer_cast<EventType>(evnt));
        }
    private:
        T* instance;
        MemberFunction memberFunction;
    };
}