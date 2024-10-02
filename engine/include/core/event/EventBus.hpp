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
            std::shared_ptr<HandlerList> handlers = _subscribers[typeid(EventType)];
            std::cout << "Event start to publish" << std::endl;
            std::cout << "Event type " << typeid(EventType).name() << std::endl;

            if (handlers == nullptr) {
                std::cout << "No handler" << std::endl;
                return;
            }
            for (auto& handler : *handlers)
                if (handler != nullptr)
                    _handlers.push_back(std::make_pair(event, handlers));
            std::cout << "Event published" << typeid(handlers).name() << std::endl;
        }

        template<class T, class EventType>
        void subscribe(T* instance, void (T::*memberFunction)(std::shared_ptr<EventType>)) {
            std::shared_ptr<HandlerList> handlers = _subscribers[typeid(EventType)];

            if (!handlers) {
                handlers = std::make_shared<HandlerList>();
                _subscribers[typeid(EventType)] = handlers;
            }
            handlers->push_back(std::make_shared<MemberHandler<T, EventType>>(instance, memberFunction));
            std::cout << "Event subscribed "  << typeid(handlers).name() << _subscribers.size() << std::endl;
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
