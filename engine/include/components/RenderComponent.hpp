#pragma once

#include <SFML/Graphics.hpp>

#include "AComponent.hpp"

namespace potEngine {
    class RenderComponent : public AComponent {
public:
    virtual void draw(sf::RenderWindow& window) = 0; // Méthode virtuelle pure
};
};