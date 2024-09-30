#pragma once

#include <SFML/Graphics.hpp>
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "WindowEntity.hpp"
#include "EventBus.hpp"
#include "WindowComponent.hpp"
#include "EventRender.hpp"

namespace potEngine {
    class RenderSystem : public ASystem {
    public:
        RenderSystem();
        ~RenderSystem();

        void update(float deltaTime) override;
    private:
        sf::RenderWindow* _window;
    };
}