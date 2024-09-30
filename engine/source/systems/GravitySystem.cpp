#include "GravitySystem.hpp"

#include <memory>

namespace potEngine
{
    void GravitySystem::update(float deltaTime, std::vector<std::shared_ptr<AEntity>> entities)
    {
        for (auto& entity : entities) {
            auto gravity = entity->getComponent<GravityComponent>();
            if (gravity) {
                auto position = (entity->getComponent<PositionComponent>());
                if (position != std::nullopt) {
                    position->setPosition(position->getPosition()[0], position->getPosition()[1] + gravity->getGravity() * deltaTime);
                }
            }
        }
    }
}