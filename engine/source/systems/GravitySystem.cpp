#include "GravitySystem.hpp"

#include <memory>

namespace potEngine
{
    void GravitySystem::update(float deltaTime)
    {
        for (auto& entity : _entitiesSystem) {
            auto gravity = entity->getComponent<GravityComponent>();
            if (gravity) {
                auto position = (entity->getComponent<PositionComponent>());
                if (position != std::nullopt) {
                    position->get()->setPosition(position->get()->getPosition()[0],
                    position->get()->getPosition()[1] +
                    gravity->get()->getGravity() * deltaTime);
                }
            }
        }
    }
}