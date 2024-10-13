#pragma once

#include <vector>
#include <cmath>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "InputInfoEvent.hpp"
#include "SendMessageEvent.hpp"
#include "AnimationComponent.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "Config.hpp"

namespace potEngine {

    class ShipAnimationSystem : public ASystem {
        public:
            ShipAnimationSystem(size_t playerId) : _playerId(playerId) {
                engine.subscribeEvent(this, &ShipAnimationSystem::updateAnimation);
            };

            // TODO adapter cette fonction pour qu'elle prenne un offsetX (ou y), pour gérer quand c'est des autres ship qu'on doit animer
            static sf::IntRect changeUpAnimationRect(int frame, int offset) {
                return sf::IntRect(sf::Vector2i(66 + 33 * (frame), 1 + offset), sf::Vector2i(33, 17));
            }
            static sf::IntRect changeDownAnimationRect(int frame, int offset) {
                return sf::IntRect(sf::Vector2i(66 - 33 * (frame), 1 + offset), sf::Vector2i(33, 17));
            }
            void updateAnimation(std::shared_ptr<NoneEvent> event);

            void update(float deltaTime) {}
        private:
            size_t _playerId;
    };
};