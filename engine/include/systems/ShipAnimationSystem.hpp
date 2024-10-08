#pragma once

#include <vector>
#include "IEvent.hpp"
#include "EventBus.hpp"
#include "InputInfoEvent.hpp"
#include "SendMessageEvent.hpp"
#include "AnimationComponent.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"

#include <netinet/in.h>
#include <cmath>

namespace potEngine {

    class ShipAnimationSystem : public ASystem {
        public:
            ShipAnimationSystem(uint8_t playerId) : _playerId(playerId) {
                eventBus.subscribe(this, &ShipAnimationSystem::updateAnimation);
            };

            static sf::IntRect changeUpAnimationRect(int frame) {
                return sf::IntRect(sf::Vector2i(66 + 33 * (frame), 1), sf::Vector2i(33, 17));
            }
            static sf::IntRect changeDownAnimationRect(int frame) {
                return sf::IntRect(sf::Vector2i(66 - 33 * (frame), 1), sf::Vector2i(33, 17));
            }
            void updateAnimation(std::shared_ptr<BlcEvent> event);

            void update(float deltaTime) {}
        private:
            uint8_t _playerId;
    };
};