#pragma once

#include <memory>

#include "IEvent.hpp"

namespace potEngine {
    struct EventRender : public IEvent {
        EventRender(AEntity windows, AEntity sprite) : windows(windows), sprite(sprite) {}
        AEntity windows;
        AEntity sprite;
    };
}
