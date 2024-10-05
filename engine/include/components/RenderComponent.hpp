#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>

namespace potEngine
{
    class RenderComponent : public AComponent {
    public:
        RenderComponent(sf::Texture texture);
        RenderComponent(sf::Texture texture, sf::IntRect textureRect);
        ~RenderComponent();

        virtual void init();
        virtual void shutdown();
        void setSprite(sf::Sprite sprite);
        sf::Sprite &getSprite();
        sf::Texture getTexture();
        sf::IntRect getInitialTextRect();
        private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::IntRect _initialTextureRect;
    };
}
