#include "AComponent.hpp"

namespace potEngine {
    AComponent::AComponent()
    {
        static std::atomic<std::uint32_t> id = 0;
        _id = id++;
    }

    AComponent::~AComponent() {}

    std::uint32_t AComponent::getID() const
    {
        return _id;
    }
}