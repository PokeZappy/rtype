#pragma once

#include <memory>

#include "IEvent.hpp"
// #include "MainLoopEvent.hpp"

namespace potEngine {
    class MainLoopEvent;
    struct EventRender : public IEvent {
        EventRender(std::shared_ptr<AEntity> window, std::vector<std::shared_ptr<AEntity>> sprites) : windows(window), sprites(sprites) {}
        std::shared_ptr<AEntity> windows;
        std::vector<std::shared_ptr<AEntity>> sprites;

        void render(std::shared_ptr<MainLoopEvent>) {
            std::cout << "render" << std::endl;
        }
    };
}
