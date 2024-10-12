#include "MainLoopEvent.hpp"

potEngine::MainLoopEvent::MainLoopEvent() : isRunning(true)
{
    engine.subscribeEvent(this, &MainLoopEvent::stopMainLoop);
};

void potEngine::MainLoopEvent::eventMainLoop(std::shared_ptr<MainLoopEvent> event)
{
    if (!isRunning)
        return;

    auto start = std::chrono::high_resolution_clock::now();
    engine.timer.timerAddTick();

    engine.publishEvent(std::make_shared<NoneEvent>());
    engine.publishEvent(event);

    std::chrono::duration<double> elapsedTick = std::chrono::high_resolution_clock::now() - start;

    double tickDuration = 1.0 / engine.timer.timerGetTps();
    if (elapsedTick.count() < tickDuration) {
        double timeToSleep = tickDuration - elapsedTick.count();
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
