#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

#include "AEntity.hpp"

namespace potEngine
{
    /*!
    * @brief Class representing a window entity in the game engine.
    */
    class WindowEntity : public AEntity {
    public:
        WindowEntity(const std::size_t id);
        WindowEntity(const std::size_t id, sf::RenderWindow* window);
        ~WindowEntity();

        void setWindowEntity(sf::RenderWindow* window);
        sf::RenderWindow* getWindowEntity();
        sf::Color getColorClear() const;
        void setColorClear(sf::Color color);
    };
}