#include <filesystem>

#include "RenderSystem.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "WindowEntity.hpp"
#include "WindowComponent.hpp"
#include "PositionComponent.hpp"

namespace potEngine
{
    RenderSystem::RenderSystem() : ASystem(true)
    {
        _signature.set(AComponent::getID<SpriteComponent>(), true);
        _signature.set(AComponent::getID<TextComponent>(), true);
        _signature.set(AComponent::getID<WindowComponent>(), true);
        engine.subscribeEvent(this, &RenderSystem::renderWindow);
    }

    RenderSystem::~RenderSystem() {

    }

    void RenderSystem::renderWindow(std::shared_ptr<NoneEvent> event) {
        // std::cout << "RENDER" << std::endl;
        // std::cout << _entitiesSystem.size() << std::endl;
        for (auto entity : _entitiesSystem) {
            auto windowComponent = entity->getComponent<WindowComponent>();
            if (windowComponent == std::nullopt)
                continue;
            auto window = windowComponent->get()->getWindow();
            window->clear();
            for (auto renderEntity : _entitiesSystem) {
                if (auto spriteComponent = renderEntity->getComponent<SpriteComponent>()) {
                    auto position = renderEntity->getComponent<PositionComponent>();
                    sf::Sprite &sprite = spriteComponent->get()->getSprite();
                    if (position != std::nullopt) {
                        auto pos = position->get()->_position;
                        sprite.setPosition(pos[0], pos[1]);
                    }
                    spriteComponent->get()->draw(*window);
                }
                if (auto textComponent = renderEntity->getComponent<TextComponent>()) {
                    textComponent->get()->draw(*window);
                }
            }
            window->display();
        }
    }
}