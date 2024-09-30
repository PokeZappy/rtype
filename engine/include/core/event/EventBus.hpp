#pragma once

#include <map>
#include <list>
#include <typeindex>
#include <memory>

#include "AEventHandler.hpp"

namespace potEngine {
    typedef std::list<std::shared_ptr<AEventHandler>> HandlerList;
    class EventBus {
    public:
        EventBus() = default;
        ~EventBus() {}
        template<typename EventType>
        void publish(std::shared_ptr<EventType> evnt) {
            std::shared_ptr<HandlerList> handlers = subscribers[typeid(EventType)];

            if (handlers == nullptr)
                return;
            for (auto& handler : *handlers)
                if (handler != nullptr)
                    handler->exec(evnt);
        }

        template<class T, class EventType>
        void subscribe(T* instance, void (T::*memberFunction)(EventType *)) {
            std::shared_ptr<HandlerList> handlers = subscribers[typeid(EventType)];

            if (handlers == nullptr) {
                handlers = std::make_shared<HandlerList>();
                subscribers[typeid(EventType)] = handlers;
            }
            handlers->push_back(std::make_shared(MemberFunctionHandler<T, EventType>(instance, memberFunction)));
        }
    private:
        std::map<std::type_index, std::shared_ptr<HandlerList>> subscribers;
    };
}
