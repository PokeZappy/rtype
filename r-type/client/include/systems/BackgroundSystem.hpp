#pragma once

#include <vector>
#include "IEvent.hpp"
#include "EventBus.hpp"
#include "InputInfoEvent.hpp"
#include "SendMessageEvent.hpp"
#include "AnimationComponent.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "staticMoveComponent.hpp"
#include "ASystem.hpp"

#include <netinet/in.h>
#include <cmath>

namespace potEngine {

    class BackgroundSystem : public ASystem {
        public:
            BackgroundSystem() : ASystem() {
                _signature.set(AComponent::getID<staticMoveComponent>(), true);
                _signature.set(AComponent::getID<PositionComponent>(), true);
                eventBus.subscribe(this, &BackgroundSystem::moveBackground);
            };

            void moveBackground(std::shared_ptr<NoneEvent> event) {
                for (auto entity : _entitiesSystem) {
                    auto pos_component = entity->getComponent<staticMoveComponent>();
                    auto sprite_component = entity->getComponent<PositionComponent>();
                    if (!pos_component || !sprite_component) {
                        continue;
                    }
                    auto &backgroundPosition = sprite_component->get()->_position;
//                    TODO : bouger cette clock ideuse
                    auto &clock = pos_component->get()->_clock;
                    float timeElapsed = clock.getElapsedTime().asSeconds();
                    float progress = timeElapsed / 1.f;

                    sf::Vector2i &end_pos = pos_component->get()->_end_pos;
                    sf::Vector2i &start_pos = pos_component->get()->_start_pos;
//                    if (progress > 1.0f) progress = 1.0f;
//                    TODO -fix here
                    backgroundPosition[0] = start_pos.x + (progress/ 350) * (end_pos.x - start_pos.x);
                    backgroundPosition[1] = start_pos.y + (progress/ 350) * (end_pos.y - start_pos.y);
                    // std::cout << "progress " << progress << ", endpos: " << end_pos.x << ", " << end_pos.y << " startpos " << start_pos.x << ", " << start_pos.y << " background "<< backgroundPosition[0] << backgroundPosition[1] << std::endl;
                }
            }
            void update(float deltaTime) {}
        private:

    };
};