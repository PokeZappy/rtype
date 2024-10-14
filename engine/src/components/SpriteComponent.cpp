#include "SpriteComponent.hpp"

namespace potEngine {

    SpriteComponent::SpriteComponent(const std::string &texturePath) {
        _texture.loadFromFile(texturePath);

        _sprite = sf::Sprite(_texture);
        _initialTextureRect = _sprite.getTextureRect();
    }

    SpriteComponent::SpriteComponent(const std::string &texturePath, sf::IntRect textureRect) {
        _texture.loadFromFile(texturePath);

        _sprite = sf::Sprite(_texture);
        _sprite.setTextureRect(textureRect);
        _initialTextureRect = textureRect;
    }

    SpriteComponent::SpriteComponent(const std::string &texturePath, sf::IntRect textureRect, sf::Vector2i targetSize) {
        _texture.loadFromFile(texturePath);
        _sprite = sf::Sprite(_texture);
        _sprite.setTextureRect(textureRect);
//        _sprite.setScale(sf::Vector2f(3, 3));
        //_sprite.setScale(targetSize.x / actualSize.x, targetSize.y / actualSize.y);
        _sprite.setScale(targetSize.x / textureRect.width, targetSize.y / textureRect.height);
        _initialTextureRect = textureRect;
    }

    SpriteComponent::~SpriteComponent()
    {
        // if (_sprite != nullptr)
        //     RenderComponent::shutdown();
    }

    void SpriteComponent::draw(sf::RenderWindow &window) {
        window.draw(_sprite);
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

