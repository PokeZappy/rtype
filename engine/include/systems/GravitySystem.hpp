#pragma once

#include <SFML/Graphics.hpp>
#include "ASystem.hpp"
#include "GravityComponent.hpp"
#include "PositionComponent.hpp"

namespace potEngine
{
    class GravitySystem : public ASystem {
    public:
        GravitySystem() {}; 
        ~GravitySystem() = default;

        void update(float deltaTime) override;
    };
}