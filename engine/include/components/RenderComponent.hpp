#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>

namespace potEngine
{
    class RenderComponent : public AComponent {
    public:
        RenderComponent();
        RenderComponent(sf::Sprite* sprite);
        ~RenderComponent();

        virtual void init();
        virtual void shutdown();
        void setSprite(sf::Sprite* sprite);
        sf::Sprite* getSprite() const;
    private:
        sf::Sprite* _sprite;
    };
}
