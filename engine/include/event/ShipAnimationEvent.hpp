#pragma once

#include <vector>
#include "IEvent.hpp"
#include "EventBus.hpp"
#include "InputInfoEvent.hpp"
#include "SendMessageEvent.hpp"
#include "AnimationComponent.hpp"
#include "SpriteComponent.hpp"

#include <netinet/in.h>
#include <cmath>

namespace potEngine {

    class ShipAnimationEvent : public IEvent {
        public:
            ShipAnimationEvent(size_t playerId) : _playerId(playerId) {
                eventBus.subscribe(this, &ShipAnimationEvent::shipInputEvent);
            };

            static sf::IntRect changeUpAnimationRect(int frame) {
                return sf::IntRect(sf::Vector2i(66 + 33 * (frame), 1), sf::Vector2i(33, 17));
            }
            static sf::IntRect changeDownAnimationRect(int frame) {
                return sf::IntRect(sf::Vector2i(66 - 33 * (frame), 1), sf::Vector2i(33, 17));
            }
            void shipInputEvent(std::shared_ptr<InputInfoEvent> event);
        private:
            size_t _playerId;
    };
};