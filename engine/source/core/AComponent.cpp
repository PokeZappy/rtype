#include "AComponent.hpp"

namespace potEngine {
    AComponent::AComponent()
    {
    }

    static std::size_t generateID() {
        static std::size_t lastID = 0;
        return lastID++;
    }

    AComponent::~AComponent() {}
}