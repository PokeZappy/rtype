#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>

namespace potEngine
{
    class SpriteComponent : public AComponent {
    public:
        SpriteComponent() {};
        SpriteComponent(sf::Texture texture);
        SpriteComponent(sf::Texture &texture, sf::IntRect textureRect);
        ~SpriteComponent();

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
