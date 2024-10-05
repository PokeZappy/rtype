#pragma once

#include <SFML/Graphics.hpp>
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "WindowEntity.hpp"
#include "EventBus.hpp"
#include "WindowComponent.hpp"
#include "EventRender.hpp"
#include "AnimationComponent.hpp"

namespace potEngine {
    struct AnimationEventData : public IEvent {
        AnimationEventData(std::vector<std::shared_ptr<AEntity>> spritesArray) : sprites(spritesArray) {}
        std::vector<std::shared_ptr<AEntity>> sprites;
    };
    class AnimationSystem : public ASystem {
    public:
        AnimationSystem();
        ~AnimationSystem();

        void update(float) override {};

        void updateAnimations(std::shared_ptr<AnimationEventData> event);
    };
}