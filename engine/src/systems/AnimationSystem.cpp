#include "AnimationSystem.hpp"
#include "SpriteComponent.hpp"
#include "InputInfoEvent.hpp"

namespace potEngine {

    AnimationSystem::AnimationSystem() : ASystem()
    {
        _signature.set(AComponent::getID<SpriteComponent>(), true);
        _signature.set(AComponent::getID<AnimationComponent>(), true);
        engine.subscribeEvent(this, &AnimationSystem::updateAnimations);
    }

    AnimationSystem::~AnimationSystem() {

    }

    void AnimationSystem::updateAnimations(std::shared_ptr<NoneEvent> event) {
        // std::cout << "ANIMATION" << std::endl;
        for (auto entity : _entitiesSystem) {
            auto animationComponent = entity->getComponent<AnimationComponent>();
            auto spriteComponent = entity->getComponent<SpriteComponent>();
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
                auto offset = animationComponent->get()->getAnimationOffset();
                sf::IntRect newTextureRect = changeFrameFunction(frame, offset);
                sprite.setTextureRect(newTextureRect);
                animationComponent->get()->setActualFrame(frame);
                clock.restart();
            }

        }
    }
};