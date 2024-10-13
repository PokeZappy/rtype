#pragma once

#include <SFML/Graphics.hpp>

#include "ASystem.hpp"
#include "AEntity.hpp"
#include "WindowEntity.hpp"
#include "EventBus.hpp"
#include "WindowComponent.hpp"
#include "AnimationComponent.hpp"
#include "MainLoopEvent.hpp"
#include "NoneEvent.hpp"

namespace potEngine {
    class AnimationSystem : public ASystem {
    public:
        AnimationSystem();
        ~AnimationSystem();

        void update(float) override {};

        void updateAnimations(std::shared_ptr<NoneEvent> event);
    };
}