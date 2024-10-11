#pragma once
#include <vector>
#include <memory>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"
#include "NoneEvent.hpp"
#include "StopMainLoopEvent.hpp"

namespace potEngine
{
    struct MainLoopEvent : public IEvent
    {
        MainLoopEvent()
        {
            eventBus.subscribe(this, &MainLoopEvent::stopMainLoop);
        };

        void eventMainLoop(std::shared_ptr<MainLoopEvent> event) {
            if (!isRunning)
                return;
            // ecsManager._timer.timerAddTick();
            eventBus.publish(std::make_shared<NoneEvent>());
            eventBus.publish(event);
            // if (ecsManager._timer.timerGetTick() >= 20) {
            //     std::cout << "PAUSE !\n";
            //     std::chrono::duration<double> elapsed = ecsManager._timer.timerGetElapsedTime();

            //     if (elapsed.count() < 1.0) {
            //         double timeToSleep = 1.0 - elapsed.count();
            //         std::this_thread::sleep_for(std::chrono::duration<double>(timeToSleep));
            //     }
            //     ecsManager._timer.timerSetTick(0);
            //     ecsManager._timer.timerSetTimeNow();
            // }
        }

        void stopMainLoop(std::shared_ptr<StopMainLoopEvent> event) {
            isRunning = false;
        }
        bool isRunning = true;
    };
}