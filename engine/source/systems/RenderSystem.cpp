#include "RenderSystem.hpp"
#include "RenderComponent.hpp"
#include "WindowEntity.hpp"
#include "WindowComponent.hpp"
#include "PositionComponent.hpp"
#include "EventRender.hpp"
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <unistd.h>

namespace potEngine
{
    RenderSystem::RenderSystem()
    {
        _signature.set(AComponent::getID<RenderComponent>(), true);
        eventBus.subscribe(this, &RenderSystem::renderWindow);
    }

    RenderSystem::~RenderSystem() {

    }

    void RenderSystem::renderWindow(std::shared_ptr<EventRender> event) {

        auto windowEntity = event->windows->getComponent<WindowComponent>();
        if (windowEntity == std::nullopt) {
            return;
        }
        auto window = windowEntity->get()->getWindow();
        window->clear();
        auto sprites = event->sprites;
        for (auto sprite : sprites) {
            auto render = sprite->getComponent<RenderComponent>();
            if (render) {
                auto position = sprite->getComponent<PositionComponent>();
                sf::Sprite &sp = render->get()->getSprite();
                if (position != std::nullopt) {
                    auto pos = position->get()->_position;
                    sp.setPosition(pos[0], pos[1]);
                }
                window->draw(sp);
            }
        }
        window->display();
    }
}