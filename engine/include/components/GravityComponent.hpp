#pragma once

#include <SFML/Graphics.hpp>
#include "AComponent.hpp"

namespace {
    class GravityComponent : public AComponent {
    public:
        GravityComponent(float gravity) : _gravity(gravity) {}
        ~GravityComponent() = default;

        float getGravity() { return _gravity; }
    private:
        float _gravity;
    };
}