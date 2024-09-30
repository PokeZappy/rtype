#include "RenderSystem.hpp"
#include "RenderComponent.hpp"
#include "WindowEntity.hpp"
#include "WindowComponent.hpp"
#include "PositionComponent.hpp"
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
            auto windowEntity = entity->getComponent<WindowComponent>();
            if (windowEntity == std::nullopt) {
                continue;
            }
            auto window = windowEntity->get()->getWindow();
            window->clear();
            for (auto& nentity : _entitiesSystem) {
                auto render = nentity->getComponent<RenderComponent>();
                if (render && render->get()->getSprite()) {                        
                    auto nrender = render->get();
                    auto position = nentity->getComponent<PositionComponent>();
                    if (position != std::nullopt) {
                        auto pos = position->get()->getPosition();
                        nrender->getSprite()->setPosition(pos[0], pos[1]);
                    }
                    window->draw(*nrender->getSprite());
                }
            }
            window->display();
        }
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
};