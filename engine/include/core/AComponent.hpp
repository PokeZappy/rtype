#pragma once

#include "IComponent.hpp"

namespace potEngine
{
    /*!
    * @brief Abstract base class for components in the game engine.
    */
    class AComponent : public IComponent {
    public:
        AComponent();
        ~AComponent();

        static std::size_t generateID() {
            static std::size_t lastID = 0;
            return lastID++;
        }

        template <typename T>
        static std::size_t getID() {
            static std::size_t typeID = generateID();
            return typeID;
        }
    };
}