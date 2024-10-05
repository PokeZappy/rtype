#pragma once

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "InputInfoEvent.hpp"
#include "SendMessageEvent.hpp"
#include "AnimationComponent.hpp"
#include "RenderComponent.hpp"

#include <netinet/in.h>
#include <cmath>
#include <vector>

namespace potEngine {

    class ShipAnimationEvent : public IEvent {
        public:
            ShipAnimationEvent(uint8_t playerId) : _playerId(playerId) {
                eventBus.subscribe(this, &ShipAnimationEvent::shipInputEvent);
            };

            static sf::IntRect changeUpAnimationRect(int frame) {
                return sf::IntRect(sf::Vector2i(66 + 33 * (frame), 1), sf::Vector2i(33, 17));
            }
            static sf::IntRect changeDownAnimationRect(int frame) {
                return sf::IntRect(sf::Vector2i(66 - 33 * (frame), 1), sf::Vector2i(33, 17));
            }
            void shipInputEvent(std::shared_ptr<InputInfoEvent> event) {
                if (event->type == sf::Event::KeyPressed) {

                    // on monte le ship vers le haut
                    if (event->key == sf::Keyboard::Z) {
                        auto playerEntity = ecsManager.getEntity(_playerId);

                        if (playerEntity->getComponent<AnimationComponent>() == std::nullopt) {
                            std::shared_ptr<AnimationComponent> upAnimation = std::make_shared<AnimationComponent>(2, 0.5, false, changeUpAnimationRect);
                            ecsManager.addComponent(playerEntity, upAnimation);
                        }
                    // on monte le ship vers le bas
                    } else if (event->key == sf::Keyboard::S) {
                        auto playerEntity = ecsManager.getEntity(_playerId);

                        if (playerEntity->getComponent<AnimationComponent>() == std::nullopt) {
                            std::shared_ptr<AnimationComponent> upAnimation = std::make_shared<AnimationComponent>(2, 0.5, false, changeDownAnimationRect);
                            ecsManager.addComponent(playerEntity, upAnimation);
                        }
                    } 
                } else if (event->type == sf::Event::KeyReleased) {
                     // on arrête de monter le ship vers le haut
                    if (event->key == sf::Keyboard::Z || event->key == sf::Keyboard::S) {
                        auto playerEntity = ecsManager.getEntity(_playerId);

                        if (playerEntity->getComponent<AnimationComponent>() != std::nullopt) {
                            playerEntity->removeComponent<AnimationComponent>();
                            auto spriteComponent = playerEntity->getComponent<RenderComponent>();
                            if (spriteComponent != std::nullopt) {
                                sf::Sprite &sprite = spriteComponent->get()->getSprite();
                                sprite.setTextureRect(spriteComponent->get()->getInitialTextRect());
                            }
                        }
                    }
                }
            }
        private:
            uint8_t _playerId;
    };
};