#pragma once

#include <memory>

#include "IEvent.hpp"

namespace potEngine {
    struct EventRender : public IEvent {
        EventRender(AEntity windows, std::vector<AEntity> sprites) : windows(windows), sprites(sprites) {}
        AEntity windows;
        std::vector<AEntity> sprites;
    };
}
