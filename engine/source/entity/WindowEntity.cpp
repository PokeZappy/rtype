#include "WindowEntity.hpp"

namespace potEngine
{
    WindowEntity::WindowEntity(const std::size_t id) : Entity(id), _window(nullptr) {}

    WindowEntity::WindowEntity(const std::size_t id, sf::RenderWindow* window) : Entity(id), _window(window) {}

    WindowEntity::~WindowEntity() {}

    void WindowEntity::setWindowEntity(sf::RenderWindow* window) {
        _window = window;
    }

    sf::RenderWindow* WindowEntity::getWindowEntity() {
        return _window;
    }

    sf::Color WindowEntity::getColorClear() const {
        return _color;
    }

    void WindowEntity::setColorClear(sf::Color color) {
        _color = color;
    }
}