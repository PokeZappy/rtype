#pragma once

#include <SFML/Graphics.hpp>
#include "ASystem.hpp"
#include "AEntity.hpp"
#include "WindowEntity.hpp"
#include "EventBus.hpp"
#include "WindowDisplayComponent.hpp"
#include "EventRender.hpp"

namespace potEngine {
    class RenderSystem : public ASystem {
    public:
        RenderSystem() {}; 
        ~RenderSystem() = default;

        void update(float deltaTime, std::vector<std::shared_ptr<AEntity>> entities) override;
    private:
        sf::RenderWindow* _window;
    };
}