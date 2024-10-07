#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>

namespace potEngine {
    class RenderComponent : public AComponent {
public:
    virtual void draw(sf::RenderWindow& window) = 0; // Méthode virtuelle pure
};
};