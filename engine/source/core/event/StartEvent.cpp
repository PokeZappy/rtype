#include "StartEvent.hpp"

namespace potEngine {
    StartEvent::StartEvent() {
            eventBus.subscribe(this, &StartEvent::eventStart);
        };
    
    void StartEvent::eventStart(std::shared_ptr<StartEvent>) 
    {
        if (!_mainLoopEvent) {
            _mainLoopEvent = std::make_shared<MainLoopEvent>(events);
        }
        eventBus.subscribe(_mainLoopEvent.get(), &MainLoopEvent::eventMainLoop);
        eventBus.publish(_mainLoopEvent);
    };

    void StartEvent::addEvent(std::shared_ptr<IEvent> e) {
        events.push_back(e);
    }
};