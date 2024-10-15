#include "MainLoopEvent.hpp"

potEngine::MainLoopEvent::MainLoopEvent() : isRunning(true)
{
    engine.subscribeEvent(this, &MainLoopEvent::stopMainLoop);
};

void potEngine::MainLoopEvent::eventMainLoop(std::shared_ptr<MainLoopEvent> event)
{
    if (!isRunning)
        return;

    if (engine.timer.isFirstCall()) {
        engine.timer.initializePreviousTime();
    }

    std::chrono::duration<double> elapsedTime = engine.timer.getElapsedTimeSinceLastTick();

    engine.timer.timerAddTick();
    engine.publishEvent(std::make_shared<NoneEvent>());
    engine.publishEvent(event);

    double tickDuration = 1.0f / engine.timer.timerGetTps();
    auto now = std::chrono::high_resolution_clock::now() + elapsedTime;

    if (elapsedTime.count() < tickDuration) {
        double timeToSleep = tickDuration;
        std::this_thread::sleep_for(std::chrono::duration<double>(timeToSleep));
    }

    if (engine.timer.timerGetTick() >= engine.timer.timerGetTps()) {
        engine.timer.timerSetTick(0);
    }
}

void potEngine::MainLoopEvent::stopMainLoop(std::shared_ptr<StopMainLoopEvent> event)
{
    isRunning = false;
}
