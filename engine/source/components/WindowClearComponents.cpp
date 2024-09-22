#include "WindowClearComponent.hpp"

namespace potEngine {
    sf::Color WindowClearComponents::getColorClear() const
    {
        return _color;
    }

    void WindowClearComponents::setColorClear(sf::Color color)
    {
        _color = color;
    }
}