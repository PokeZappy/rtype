#pragma once

#include <memory>

#include "AEventHandler.hpp"

namespace potEngine {
    template<class T, class EventType>
    class MemberHandler : public AEventHandler {
        public:
            typedef void (T::*MemberFunction)(std::shared_ptr<EventType>);
            MemberHandler(T* instance, MemberFunction memberFunction)
                : _instance(instance), _memberFunction(memberFunction) {}
        
            void call(std::shared_ptr<IEvent> evnt) {
                std::shared_ptr<EventType> castedEvent = std::dynamic_pointer_cast<EventType>(evnt);
                if (castedEvent && _instance) {
                    (_instance->*_memberFunction)(castedEvent);
                }
            }
    private:
        T* _instance;
        MemberFunction _memberFunction;
    };
}