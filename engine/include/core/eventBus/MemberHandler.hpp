#pragma once

#include <memory>

#include "AEventHandler.hpp"

namespace potEngine {
    /*!
    * @brief Template class for handling member function events.
    * @tparam T The type of the instance.
    * @tparam EventType The type of the event.
    */
    template<class T, class EventType>
    class MemberHandler : public AEventHandler {
        public:
            typedef void (T::*MemberFunction)(std::shared_ptr<EventType>);
            /*!
            * @brief Construct a new MemberHandler object.
            * @param instance Pointer to the instance.
            * @param memberFunction Pointer to the member function.
            */
            MemberHandler(T* instance, MemberFunction memberFunction)
                : _instance(instance), _memberFunction(memberFunction) {}

            /*!
            * @brief Call the member function with the event.
            * @param evnt Shared pointer to the event.
            */
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