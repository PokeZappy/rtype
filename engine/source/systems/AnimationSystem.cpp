#include "AnimationSystem.hpp"
#include "RenderComponent.hpp"
#include "EventRender.hpp"
#include "InputInfoEvent.hpp"
#include <iostream>

namespace potEngine {

    AnimationSystem::AnimationSystem()
    {
        // _signature.set(AComponent::getID<RenderComponent>(), true);
        eventBus.subscribe(this, &AnimationSystem::updateAnimations);
    }

    AnimationSystem::~AnimationSystem() {

    }

    void AnimationSystem::updateAnimations(std::shared_ptr<AnimationEventData> event) {
        auto sprites = event->sprites;

        for (auto spriteEntity : sprites) {
            auto animationComponent = spriteEntity->getComponent<AnimationComponent>();
            auto spriteComponent = spriteEntity->getComponent<RenderComponent>();
            if (animationComponent == std::nullopt || spriteComponent == std::nullopt)
                continue;
            float interval = animationComponent->get()->getInterval();
            int frame = animationComponent->get()->getActualFrame();
            int maxFrame = animationComponent->get()->getMaxFrames();
            bool isLooping = animationComponent->get()->isLooping();

            if (frame >= maxFrame && !isLooping)
                continue;
            sf::Sprite &sprite = spriteComponent->get()->getSprite();
            sf::Clock &clock = animationComponent->get()->getClock();

            if (clock.getElapsedTime().asSeconds() >= interval) {
                if (frame >= maxFrame) {
                    frame = 1;
                } else {
                    frame++;
                }
                auto changeFrameFunction = animationComponent->get()->getChangeFrame();
                sf::IntRect newTextureRect = changeFrameFunction(frame);
                sprite.setTextureRect(newTextureRect);
                animationComponent->get()->setActualFrame(frame);
                clock.restart();
            }

        }
    }
};