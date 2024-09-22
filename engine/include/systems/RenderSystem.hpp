#pragma once

#include <SFML/Graphics.hpp>
#include "ASystem.hpp"
#include "Entity.hpp"
#include "WindowEntity.hpp"
#include "WindowDisplayComponent.hpp"

namespace potEngine {
    class RenderSystem : public ASystem {
    public:
        RenderSystem();
        ~RenderSystem();

        void update(float deltaTime, std::vector<std::shared_ptr<Entity>> entities) override;
    private:
        sf::RenderWindow* _window;
    };
}