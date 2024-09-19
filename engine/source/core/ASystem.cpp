#include "ASystem.hpp"

namespace potEngine {

    ASystem::ASystem()
    {
        _entitiesSystem = std::vector<Entity*>();
    }
    void ASystem::addEntity(Entity& entity)
    {
        _entitiesSystem.push_back(&entity);
    }

    void ASystem::removeEntity(const std::size_t id)
    {
        for (auto it = _entitiesSystem.begin(); it != _entitiesSystem.end(); ++it) {
            if ((*it)->getID() == id) {
                _entitiesSystem.erase(it);
                break;
            }
        }
    }

    std::vector<Entity*> ASystem::getEntities() const
    {
        return _entitiesSystem;
    }
}