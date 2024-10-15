#pragma once

#include <cstdint>
#include <atomic>
#include <typeinfo>

namespace potEngine {
    /*!
    * @brief Interface for components in the game engine.
    */
    class IComponent {
    public:
        virtual ~IComponent() = default;
    };
}