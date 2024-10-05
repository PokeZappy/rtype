#pragma once

#include <SFML/Graphics.hpp>
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "WindowEntity.hpp"
#include "EventBus.hpp"
#include "WindowComponent.hpp"
#include "EventRender.hpp"

namespace potEngine {
    struct ComputeInputEvent : public IEvent {
        ComputeInputEvent(std::shared_ptr<AEntity> windowPtr) : window(windowPtr) {}
        std::shared_ptr<AEntity> window;
    };
    class InputSystem : public ASystem {
    public:
        InputSystem();
        ~InputSystem();

        void update(float) override {};

        void pollInputs(std::shared_ptr<ComputeInputEvent> event);
    };
}