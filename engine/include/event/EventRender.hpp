#pragma once

#include <memory>

#include "IEvent.hpp"
// #include "MainLoopEvent.hpp"

namespace potEngine {
    class MainLoopEvent;
    struct EventRender : public IEvent {
        EventRender(AEntity windows, std::vector<AEntity> sprites) : windows(windows), sprites(sprites) {}
        AEntity windows;
        std::vector<AEntity> sprites;

        void render(std::shared_ptr<MainLoopEvent>) {
            std::cout << "render" << std::endl;
        }
    };
}
