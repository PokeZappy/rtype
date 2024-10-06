#include "SpriteComponent.hpp"

namespace potEngine {

    SpriteComponent::SpriteComponent(sf::Texture texture) : _texture(texture)
    {
        _sprite = sf::Sprite(_texture);
        _initialTextureRect = _sprite.getTextureRect();
    }

    SpriteComponent::SpriteComponent(sf::Texture &texture, sf::IntRect textureRect) : _texture(texture)
    {
        _sprite = sf::Sprite(_texture);
        _sprite.setTexture(_texture);
        _sprite.setTextureRect(textureRect);
        _sprite.setScale(sf::Vector2f(3, 3));
        _initialTextureRect = textureRect;
    }

    SpriteComponent::~SpriteComponent()
    {
        // if (_sprite != nullptr)
        //     RenderComponent::shutdown();
    }

    void SpriteComponent::init()
    {
        // _sprite = new sf::Sprite();
    }

    void SpriteComponent::shutdown()
    {
        // delete _sprite;
    }

    void SpriteComponent::setSprite(sf::Sprite sprite)
    {
        _sprite = sprite;
    }

    sf::Sprite &SpriteComponent::getSprite()
    {
        return _sprite;
    }

    sf::Texture SpriteComponent::getTexture()
    {
        return _texture;
    }

    sf::IntRect SpriteComponent::getInitialTextRect() {
        return (_initialTextureRect);
    }
}

