#include "AEntity.hpp"

namespace potEngine
{
    /*!
    * @brief Construct a new AEntity object.
    *
    * This constructor initializes the AEntity with the given ID.
    *
    * @param id The ID of the entity.
    */
    AEntity::AEntity(const std::size_t id): _id(id) {}

    /*!
    * @brief Destroy the AEntity object.
    *
    * This destructor clears all components of the entity.
    */
    AEntity::~AEntity()
    {
        _components.clear();
    }

    /*!
    * @brief Get the ID of the entity.
    *
    * @return The ID of the entity.
    */
    std::size_t AEntity::getID() const
    {
        return _id;
    }
}
