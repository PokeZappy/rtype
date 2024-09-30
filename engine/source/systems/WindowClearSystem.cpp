#include "WindowClearSystem.hpp"

namespace potEngine
{
    WindowClearSystem::WindowClearSystem()
    {
    }

    WindowClearSystem::~WindowClearSystem() {}

    void WindowClearSystem::update(float deltaTime, std::vector<std::shared_ptr<AEntity>> entities)
    {
        for (auto &entity : entities) {
        auto windowClearComponent = entity->getComponent<WindowClearComponents>();

        if (windowClearComponent) {
            auto window = std::static_pointer_cast<WindowEntity>(entity);
            window->getWindowEntity()->clear(sf::Color::Black);
            }
        }
    }
}
