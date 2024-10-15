#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>

namespace potEngine {
    /*!
    * @brief Abstract base class for renderable components in the game engine.
    */
    class RenderComponent : public AComponent {
public:
    /*!
    * @brief Pure virtual function to draw the component on the given window.
    * @param window Reference to the SFML RenderWindow.
    */
    virtual void draw(sf::RenderWindow& window) = 0; // Méthode virtuelle pure
};
};