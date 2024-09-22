#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

namespace potEngine {
    class WindowClearComponents : public AComponent {
    public:
        WindowClearComponents() {};
        ~WindowClearComponents() {};

        sf::Color getColorClear() const;
        void setColorClear(sf::Color color);
    private:
        sf::Color _color = sf::Color::Black;
    };
}