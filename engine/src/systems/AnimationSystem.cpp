#include "AnimationSystem.hpp"
#include "SpriteComponent.hpp"
#include "InputInfoEvent.hpp"
#include <iostream>

namespace potEngine {

    /*!
    * @brief Construct a new Animation System object.
    *
    * This constructor initializes the AnimationSystem and sets up the necessary component signatures and event subscriptions.
    */
    AnimationSystem::AnimationSystem() : ASystem()
    {
        _signature.set(AComponent::getID<SpriteComponent>(), true);
        _signature.set(AComponent::getID<AnimationComponent>(), true);
        engine.subscribeEvent(this, &AnimationSystem::updateAnimations);
    }

    /*!
    * @brief Destroy the Animation System object.
    */
    AnimationSystem::~AnimationSystem() {

    }

    /*!
    * @brief Update the animations.
    *
    * This function updates the animations by iterating through entities with animation components and updating their frames based on the elapsed time.
    *
    * @param event The event triggering the animation update.
    */
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
                sf::IntRect newTextureRect = changeFrameFunction(frame);
                sprite.setTextureRect(newTextureRect);
                animationComponent->get()->setActualFrame(frame);
                clock.restart();
            }

        }
    }
};