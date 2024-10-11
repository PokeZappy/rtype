#include "MainLoopEvent.hpp"

potEngine::MainLoopEvent::MainLoopEvent() : isRunning(true)
{
    engine.subscribeEvent(this, &MainLoopEvent::stopMainLoop);
};

void potEngine::MainLoopEvent::eventMainLoop(std::shared_ptr<MainLoopEvent> event)
{
    if (!isRunning)
        return;
    engine.timer.timerAddTick();
    engine.publishEvent(std::make_shared<NoneEvent>());
    engine.publishEvent(event);
    if (engine.timer.timerGetTick() >= engine.timer.timerGetTick()) {
        std::cout << "PAUSE !\n";
        std::chrono::duration<double> elapsed = engine.timer.timerGetElapsedTime();

        if (elapsed.count() < 1.0) {
            double timeToSleep = 1.0 - elapsed.count();
            std::this_thread::sleep_for(std::chrono::duration<double>(timeToSleep));
        }
        engine.timer.timerSetTick(0);
        engine.timer.timerSetTimeNow();
    }
}

void potEngine::MainLoopEvent::stopMainLoop(std::shared_ptr<StopMainLoopEvent> event)
{
    isRunning = false;
}
