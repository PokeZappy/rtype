#include "RenderComponent.hpp"

namespace potEngine {

    RenderComponent::RenderComponent(sf::Texture texture) : _texture(texture)
    {
        _sprite = sf::Sprite(_texture);
        _initialTextureRect = _sprite.getTextureRect();
    }

    RenderComponent::RenderComponent(sf::Texture texture, sf::IntRect textureRect) : _texture(texture)
    {
        _sprite = sf::Sprite(_texture);
        _sprite.setTextureRect(textureRect);
        _sprite.setScale(sf::Vector2f(3, 3));
        _initialTextureRect = textureRect;
    }

    RenderComponent::~RenderComponent()
    {
        // if (_sprite != nullptr)
        //     RenderComponent::shutdown();
    }

    void RenderComponent::init()
    {
        // _sprite = new sf::Sprite();
    }

    void RenderComponent::shutdown()
    {
        // delete _sprite;
    }

    void RenderComponent::setSprite(sf::Sprite sprite)
    {
        _sprite = sprite;
    }

    sf::Sprite &RenderComponent::getSprite()
    {
        return _sprite;
    }

    sf::Texture RenderComponent::getTexture()
    {
        return _texture;
    }

    sf::IntRect RenderComponent::getInitialTextRect() {
        return (_initialTextureRect);
    }
}

