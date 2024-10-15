#include "AComponent.hpp"

namespace potEngine {
    /*!
    * @brief Construct a new AComponent object.
    */
    AComponent::AComponent()
    {
    }

    /*!
    * @brief Generate a unique ID for the component.
    *
    * @return A unique ID.
    */
    static std::size_t generateID() {
        static std::size_t lastID = 0;
        return lastID++;
    }

    /*!
    * @brief Destroy the AComponent object.
    */
    AComponent::~AComponent() {}
}