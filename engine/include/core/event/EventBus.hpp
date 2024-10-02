#pragma once

#include <map>
#include <list>
#include <typeindex>
#include <memory>
#include <iostream>

#include "AEventHandler.hpp"
#include "MemberHandler.hpp"
#include "IEvent.hpp"

namespace potEngine {
    typedef std::list<std::shared_ptr<AEventHandler>> HandlerList;
    class EventBus {
    public:
        static EventBus& getInstance() {
            static EventBus instance;
            return instance;
        }
        EventBus(EventBus const&) = delete;
        void operator=(EventBus const&) = delete;
    
        template<class EventType>
        void publish(std::shared_ptr<EventType> event) {
            auto it = _subscribers.find(std::type_index(typeid(EventType)));
            
            if (it == _subscribers.end() || !it->second) {
                std::cout << "No handler for event type: " << typeid(it->second).name() << std::endl;
                return;
            }
            // std::shared_ptr<HandlerList> handlers = _subscribers[typeid(EventType)];
            // std::cout << "Event start to publish" << std::endl;
            // std::cout << "Event type " << typeid(EventType).name() << std::endl;

            // if (handlers == nullptr) {
            //     std::cout << "No handler" << std::endl;
            //     return;
            // }
            for (auto& handler : *it->second)
                if (handler != nullptr)
                    _handlers.push_back(std::make_pair(event, it->second));
            std::cout << "Event published" << typeid(it->second).name() << std::endl;
        }

        template<class T, class EventType>
        void subscribe(T* instance, void (T::*memberFunction)(std::shared_ptr<EventType>)) {
            // auto it = _subscribers.find(typeid(EventType));
            // std::shared_ptr<HandlerList> handlers = _subscribers[typeid(EventType)];
    auto it = _subscribers.find(std::type_index(typeid(EventType)));
    std::shared_ptr<HandlerList> handlers;

    // If no entry exists for the event type, create a new handler list
    if (it == _subscribers.end()) {
        handlers = std::make_shared<HandlerList>();
        _subscribers[std::type_index(typeid(EventType))] = handlers;
    } else {
        handlers = it->second;
    }

    // Add the new member handler for this event type
    handlers->push_back(std::make_shared<MemberHandler<T, EventType>>(instance, memberFunction));
        // if (!handlers) {
        //         handlers = std::make_shared<HandlerList>();
        //         _subscribers[typeid(EventType)] = handlers;
        //     }
        //     handlers->push_back(std::make_shared<MemberHandler<T, EventType>>(instance, memberFunction));
            std::cout << "Event subscribed "  << typeid(handlers).name() << std::endl;
        }

        std::pair<std::shared_ptr<IEvent>, std::shared_ptr<HandlerList>> getHandler() {
            if (_handlers.empty())
                return std::make_pair(nullptr, nullptr);
            auto handler = _handlers.front();
            _handlers.erase(_handlers.begin());
            return handler;
        }

    private:
        EventBus() = default;
        std::map<std::type_index, std::shared_ptr<HandlerList>> _subscribers;
        std::vector<std::pair<std::shared_ptr<IEvent>, std::shared_ptr<HandlerList>>> _handlers;
    };
    static EventBus& eventBus = EventBus::getInstance();
}
