#include "Entity.hpp"

namespace potEngine
{
    Entity::Entity(const std::size_t id): _id(id) {}

    Entity::~Entity()
    {
        _components.clear();
    }

    std::size_t Entity::getID() const
    {
        return _id;
    }
}
