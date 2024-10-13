#include "StartEvent.hpp"

namespace potEngine {
    StartEvent::StartEvent() {
            engine.subscribeEvent(this, &StartEvent::eventStart);
        };
    
    void StartEvent::eventStart(std::shared_ptr<StartEvent>) 
    {
        if (!_mainLoopEvent) {
            _mainLoopEvent = std::make_shared<MainLoopEvent>();
        }
        engine.subscribeEvent(_mainLoopEvent.get(), &MainLoopEvent::eventMainLoop);
        engine.publishEvent(_mainLoopEvent);
    };

    // void StartEvent::addEvent(std::shared_ptr<IEvent> e) {
    //     events.push_back(e);
    // }
};