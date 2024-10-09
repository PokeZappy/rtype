#pragma once

#include "RenderComponent.hpp"

namespace potEngine
{
    class staticMoveComponent : public AComponent {
    public:
        staticMoveComponent() {};

        explicit staticMoveComponent(sf::Vector2i end_pos, sf::Vector2i start_pos): _end_pos(end_pos), _start_pos(start_pos) {};
        ~staticMoveComponent() {};
        sf::Vector2i _end_pos;
        sf::Vector2i _start_pos;
        sf::Clock _clock;
    };
}
