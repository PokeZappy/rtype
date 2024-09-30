#pragma once

#include <SFML/Graphics.hpp>
#include "AComponent.hpp"
#include <vector>

namespace potEngine
{
    class PositionComponent : public AComponent{
        public :
            PositionComponent(int x, int y) : _position({x, y}) {};
            PositionComponent() = default;
            ~PositionComponent() = default;
            std::vector<int> getPosition() const { return _position; }
            void setPosition(int x, int y) { _position = {x, y}; }
        private:
            std::vector<int> _position = {0, 0};
    };
}