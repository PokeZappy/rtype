#include "StartEvent.hpp"

namespace potEngine {

    /*!
    * @brief Construct a new Start Event object.
    *
    * This constructor initializes the StartEvent and subscribes to the eventStart function.
    */
    StartEvent::StartEvent() {
            engine.subscribeEvent(this, &StartEvent::eventStart);
        };

    /*!
    * @brief Handle the start event.
    *
    * This function handles the start event by subscribing to the main loop event and publishing it.
    *
    * @param event The start event.
    */
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