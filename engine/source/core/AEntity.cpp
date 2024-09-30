#include "AEntity.hpp"

namespace potEngine
{
    AEntity::AEntity(const std::size_t id): _id(id) {}

    AEntity::~AEntity()
    {
        _components.clear();
    }

    std::size_t AEntity::getID() const
    {
        return _id;
    }
}
