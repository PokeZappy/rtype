#pragma once

#include <SFML/Graphics.hpp>
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "WindowEntity.hpp"
#include "EventBus.hpp"
#include "WindowComponent.hpp"
#include "MainLoopEvent.hpp"
#include "BlcEvent.hpp"

namespace potEngine {
    class InputSystem : public ASystem {
    public:
        InputSystem();
        ~InputSystem();

        void update(float) override {};

        void pollInputs(std::shared_ptr<BlcEvent> event);
    };
}