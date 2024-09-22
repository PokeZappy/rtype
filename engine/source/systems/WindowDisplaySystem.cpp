#include "WindowDisplaySystem.hpp"

namespace potEngine
{
    WindowDisplaySystem::WindowDisplaySystem()
    {
    }

    WindowDisplaySystem::~WindowDisplaySystem() {}

    void WindowDisplaySystem::update(float deltaTime, std::vector<std::shared_ptr<Entity>> entities)
    {
        for (auto &entity : entities) {
            auto windowDisplayComponent = static_cast<std::optional<std::shared_ptr<WindowDisplayComponent>>>(entity->getComponent<WindowDisplayComponent>());
            if (windowDisplayComponent) {
                auto window = std::static_pointer_cast<WindowEntity>(entity);
                window->getWindowEntity()->clear(sf::Color::Black);
            }
        }
    }
}