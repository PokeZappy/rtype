#pragma once

#include "IComponent.hpp"
#include "SFML/Graphics.hpp"

namespace potEngine {
    class RenderComponent : public IComponent {
    public:
        RenderComponent();
        RenderComponent(sf::Sprite* sprite);
        ~RenderComponent();
    
        virtual void init();
        virtual void shutdown();
        sf::Sprite* getSprite() const;
    private:
        sf::Sprite* _sprite;
    };
}