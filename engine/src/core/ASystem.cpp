#include "ASystem.hpp"

namespace potEngine {

    /*!
    * @brief Construct a new ASystem object.
    *
    * This constructor initializes the ASystem and sets the inclusive flag.
    *
    * @param inclusive A boolean indicating whether the system is inclusive.
    */
    ASystem::ASystem(bool inclusive) : _inclusive(inclusive)
    {
        _entitiesSystem = std::vector<std::shared_ptr<AEntity>>();
    }
    // void ASystem::addEntity(AEntity& entity)
    // {
    //     _entitiesSystem.push_back(&entity);
    // }

    // void ASystem::removeEntity(const std::size_t id)
    // {
    //     for (auto it = _entitiesSystem.begin(); it != _entitiesSystem.end(); ++it) {
    //         if ((*it)->getID() == id) {
    //             _entitiesSystem.erase(it);
    //             break;
    //         }
    //     }
    // }

    /*!
    * @brief Get the entities in the system.
    *
    * @return A reference to the vector of shared pointers to entities.
    */
    std::vector<std::shared_ptr<AEntity>> &ASystem::getEntities()
    {
        return _entitiesSystem;
    }
}