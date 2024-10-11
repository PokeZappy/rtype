#include "MainLoopEvent.hpp"

potEngine::MainLoopEvent::MainLoopEvent() : isRunning(true)
{
    eventBus.subscribe(this, &MainLoopEvent::stopMainLoop);
};

void potEngine::MainLoopEvent::eventMainLoop(std::shared_ptr<MainLoopEvent> event)
{
    if (!isRunning)
        return;
    ecsManager.timer.timerAddTick();
    eventBus.publish(std::make_shared<NoneEvent>());
    eventBus.publish(event);
    if (ecsManager.timer.timerGetTick() >= ecsManager.timer.timerGetTick()) {
        std::cout << "PAUSE !\n";
        std::chrono::duration<double> elapsed = ecsManager.timer.timerGetElapsedTime();

        if (elapsed.count() < 1.0) {
            double timeToSleep = 1.0 - elapsed.count();
            std::this_thread::sleep_for(std::chrono::duration<double>(timeToSleep));
        }
        ecsManager.timer.timerSetTick(0);
        ecsManager.timer.timerSetTimeNow();
    }
}

void potEngine::MainLoopEvent::stopMainLoop(std::shared_ptr<StopMainLoopEvent> event)
{
    isRunning = false;
}
