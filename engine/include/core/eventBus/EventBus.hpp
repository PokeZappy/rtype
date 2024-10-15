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
    /*!
    * @brief Class for managing event subscriptions and publishing events.
    */
    class EventBus {
    public:
        /*!
        * @brief Get the singleton instance of the EventBus.
        * @return Reference to the EventBus instance.
        */
        static EventBus& getInstance() {
            static EventBus instance;
            return instance;
        }
        /*!
        * @brief Deleted copy constructor to enforce singleton pattern.
        */
        EventBus(EventBus const&) = delete;
        /*!
        * @brief Deleted assignment operator to enforce singleton pattern.
        */
        void operator=(EventBus const&) = delete;

        /*!
        * @brief Publish an event to all subscribed handlers.
        * @tparam EventType The type of the event.
        * @param event Shared pointer to the event.
        */
        template<class EventType>
        void publish(std::shared_ptr<EventType> event) {
            auto it = _subscribers.find(std::type_index(typeid(EventType)));

            if (it == _subscribers.end() || !it->second) {
                // std::cout << "[EVENTBUS] No handler for event type: " << typeid(EventType).name() << std::endl;
                return;
            }
            // std::shared_ptr<HandlerList> handlers = _subscribers[typeid(EventType)];
            // std::cout << "Event start to publish" << std::endl;
            // std::cout << "Event type " << typeid(EventType).name() << std::endl;

            // if (handlers == nullptr) {
            //     std::cout << "No handler" << std::endl;
            //     return;
            // }
            for (auto& handler : *it->second) {
                if (handler != nullptr) {
                    _handlers.push_back(std::make_pair(event, it->second));
                    // std::cout << "[EVENTBUS] Event published " << typeid(EventType).name() << std::endl;
                }
            }
        }

        /*!
        * @brief Subscribe a member function to an event type.
        * @tparam T The type of the instance.
        * @tparam EventType The type of the event.
        * @param instance Pointer to the instance.
        * @param memberFunction Pointer to the member function.
        */
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
            // std::cout << "[EVENTBUS] Event subscribed "  << typeid(EventType).name() << std::endl;
        }

        /*!
        * @brief Get the next handler for an event.
        * @return A pair containing the event and the handler list.
        */
        std::pair<std::shared_ptr<IEvent>, std::shared_ptr<HandlerList>> getHandler() {
            if (_handlers.empty())
                return std::make_pair(nullptr, nullptr);
            // std::cout << "taille de la queue :" << _handlers.size() << std::endl;
            auto handler = _handlers.front();
            _handlers.erase(_handlers.begin());
            return handler;
        }

    private:
        EventBus() = default;
        std::map<std::type_index, std::shared_ptr<HandlerList>> _subscribers;
        std::vector<std::pair<std::shared_ptr<IEvent>, std::shared_ptr<HandlerList>>> _handlers;
    };
}
