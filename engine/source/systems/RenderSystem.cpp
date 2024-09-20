#include "../include/systems/RenderSystem.hpp"
#include "RenderComponent.hpp"

namespace potEngine {
    RenderSystem::RenderSystem()
    {
        _window = new sf::RenderWindow(sf::VideoMode(800, 600), "Window");
    }

    RenderSystem::~RenderSystem() {
        _window->close();
        delete _window;
    }

    void RenderSystem::update(float deltaTimeies) {
        _window->clear();

        for (auto& entity : getEntities()) {
            auto renderComponentOpt = entity->getComponent<RenderComponent>();
            if (renderComponentOpt) {
                RenderComponent& renderComponent = renderComponentOpt->get();

                if (renderComponent.getSprite()) {
                    _window->draw(*renderComponent.getSprite());
                }
            }
            _window->display();
        }
    }
}