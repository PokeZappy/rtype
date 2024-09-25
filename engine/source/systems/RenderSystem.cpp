#include "RenderSystem.hpp"
#include "RenderComponent.hpp"
#include "WindowDisplayComponent.hpp"
#include "WindowEntity.hpp"
#include <iostream>

namespace potEngine {
    RenderSystem::RenderSystem()
    {
        _signature.set(AComponent::getID<RenderComponent>(), true);
    }

    RenderSystem::~RenderSystem() {

    }

    void RenderSystem::update(float deltaTime) {
        for (auto& entity : _entitiesSystem) {
            if (entity->getComponent<WindowDisplayComponent>() == std::nullopt) {
                continue;
            }
            auto windowEntity = std::static_pointer_cast<WindowEntity>(entity);
            if (!windowEntity)
                continue;
            windowEntity->getWindowEntity()->clear(sf::Color::Black);
            for (auto& nentity : _entitiesSystem) {
                auto render = nentity->getComponent<RenderComponent>();
                if (render && render->get()->getSprite()) {
                    auto nrender = render->get();
                    windowEntity->getWindowEntity()->draw(*nrender->getSprite());
                }
            }
            windowEntity->getWindowEntity()->display();
        }
    }

    // void RenderSystem::addEntity(Entity* entity)
    // {
    //     _entities.push_back(entity);
    // }

    // void RenderSystem::removeEntity(Entity* entity)
    // {
    //     auto it = std::find(_entities.begin(), _entities.end(), entity);
    //     if (it != _entities.end()) {
    //         _entities.erase(it);
    //     }
    // }
};