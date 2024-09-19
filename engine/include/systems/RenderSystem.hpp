#pragma once

#include "ASystem.hpp"
#include "SFML/Graphics.hpp"

namespace potEngine {
    class RenderSystem : public ASystem {
    public:
        RenderSystem();
        ~RenderSystem();

        virtual void update(float deltaTime);
    private:
        sf::RenderWindow* _window;
    };
}