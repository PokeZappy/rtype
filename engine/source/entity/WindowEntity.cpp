#include "WindowEntity.hpp"
#include "WindowComponent.hpp"

namespace potEngine
{
    WindowEntity::WindowEntity(const std::size_t id) : AEntity(id)
    {
        auto WindowComponentPtr = std::make_shared<WindowComponent>();
        this->addComponent<WindowComponent>(WindowComponentPtr);
    }

    WindowEntity::WindowEntity(const std::size_t id, sf::RenderWindow* window) : AEntity(id)
    {
        auto WindowComponentPtr = std::make_shared<WindowComponent>();
        this->addComponent<WindowComponent>(WindowComponentPtr);
    }

    WindowEntity::~WindowEntity() {}

    void WindowEntity::setWindowEntity(sf::RenderWindow* window) {
        
    }

    sf::RenderWindow* WindowEntity::getWindowEntity() {
        return getComponent<WindowComponent>()->get()->getWindow();
    }

    sf::Color WindowEntity::getColorClear() const {
        return sf::Color::Black;
    }

    void WindowEntity::setColorClear(sf::Color color) {
    }
}