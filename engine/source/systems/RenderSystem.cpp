#include "RenderSystem.hpp"
#include "SpriteComponent.hpp"
#include "WindowEntity.hpp"
#include "WindowComponent.hpp"
#include "PositionComponent.hpp"
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <unistd.h>

namespace potEngine
{
    RenderSystem::RenderSystem()
    {
        _signature.set(AComponent::getID<SpriteComponent>(), true);
        eventBus.subscribe(this, &RenderSystem::renderWindow);
    }

    RenderSystem::~RenderSystem() {

    }

    void RenderSystem::renderWindow(std::shared_ptr<BlcEvent> event) {
        // std::cout << "RENDER" << std::endl;
        // std::cout << _entitiesSystem.size() << std::endl;
        for (auto entity : _entitiesSystem) {
            auto windowComponent = entity->getComponent<WindowComponent>();
            if (windowComponent == std::nullopt)
                continue;
            auto window = windowComponent->get()->getWindow();
            window->clear();
            for (auto spriteEntity : _entitiesSystem) {
                auto spriteComponent = spriteEntity->getComponent<SpriteComponent>();
                auto windowComponent = spriteEntity->getComponent<WindowComponent>();
                if (spriteComponent && !windowComponent) {
                    auto position = spriteEntity->getComponent<PositionComponent>();
                    sf::Sprite &sprite = spriteComponent->get()->getSprite();
                    if (position != std::nullopt) {
                        auto pos = position->get()->_position;
                        sprite.setPosition(pos[0], pos[1]);
                    }
                    window->draw(sprite);
                }
            }
            window->display();
        }
    }
}