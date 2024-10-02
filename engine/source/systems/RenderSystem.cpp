#include "RenderSystem.hpp"
#include "RenderComponent.hpp"
#include "WindowEntity.hpp"
#include "WindowComponent.hpp"
#include "PositionComponent.hpp"
#include "EventRender.hpp"
#include <iostream>

namespace potEngine {
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
            for (auto& sprite : sprites) {
                auto render = sprite->getComponent<RenderComponent>();
                if (render && render->get()->getSprite()) {                        
                    auto nrender = render->get();
                    auto position = sprite->getComponent<PositionComponent>();
                if (position != std::nullopt) {
                    auto pos = position->get()->getPosition();
                    nrender->getSprite()->setPosition(pos[0], pos[1]);
                }
                window->draw(*nrender->getSprite());
            }
        }
        window->display();
    }

    // void RenderSystem::addEntity(AEntity* entity)
    // {
    //     _entities.push_back(entity);
    // }

    // void RenderSystem::removeEntity(AEntity* entity)
    // {
    //     auto it = std::find(_entities.begin(), _entities.end(), entity);
    //     if (it != _entities.end()) {
    //         _entities.erase(it);
    //     }
    // }
}