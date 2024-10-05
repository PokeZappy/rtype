#pragma once
#include <vector>
#include <memory>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"
#include "EventRender.hpp"
#include "InputSystem.hpp"
#include "RecvMessageEventData.hpp"
#include "AnimationSystem.hpp"

namespace potEngine
{
    struct MainLoopEvent : public IEvent
    {
        MainLoopEvent(std::vector<std::shared_ptr<IEvent>> eventsList) : events(eventsList) 
        {
        };

        void eventMainLoop(std::shared_ptr<MainLoopEvent> event) {

            for (auto evt : events) {
                auto renderSystem = std::dynamic_pointer_cast<EventRender>(evt);
                if (renderSystem) {
                    eventBus.publish(renderSystem);
                } else {
                    auto inputSystem = std::dynamic_pointer_cast<ComputeInputEvent>(evt);
                    if (inputSystem) {
                        eventBus.publish(inputSystem);
                    } else {
                        auto recvMessageSystem = std::dynamic_pointer_cast<RecvMessageEventData>(evt);
                        if (recvMessageSystem) {
                            eventBus.publish(recvMessageSystem);
                        } else {
                            auto animationSystem = std::dynamic_pointer_cast<AnimationEventData>(evt);
                            if (animationSystem) {
                                eventBus.publish(animationSystem);
                            }
                        }
                    }
                }
            }
            eventBus.publish(event);
        }

        std::vector<std::shared_ptr<IEvent>> events;
    };
}