#include "SpriteComponent.hpp"

namespace potEngine {

    /*!
    * @brief Construct a new SpriteComponent object with the given texture path.
    *
    * This constructor initializes the SpriteComponent with the given texture path.
    *
    * @param texturePath The path to the texture file.
    */
    SpriteComponent::SpriteComponent(const std::string &texturePath) {
        _texture.loadFromFile(texturePath);

        _sprite = sf::Sprite(_texture);
        _initialTextureRect = _sprite.getTextureRect();
    }

    /*!
    * @brief Construct a new SpriteComponent object with the given texture path and texture rectangle.
    *
    * This constructor initializes the SpriteComponent with the given texture path and texture rectangle.
    *
    * @param texturePath The path to the texture file.
    * @param textureRect The rectangle defining the texture area.
    */
    SpriteComponent::SpriteComponent(const std::string &texturePath, sf::IntRect textureRect) {
        _texture.loadFromFile(texturePath);

        _sprite = sf::Sprite(_texture);
        _sprite.setTextureRect(textureRect);
        _initialTextureRect = textureRect;
    }

    /*!
    * @brief Construct a new SpriteComponent object with the given texture path, texture rectangle, target size, and actual size.
    *
    * This constructor initializes the SpriteComponent with the given texture path, texture rectangle, target size, and actual size.
    *
    * @param texturePath The path to the texture file.
    * @param textureRect The rectangle defining the texture area.
    * @param targetSize The target size of the sprite.
    * @param actualSize The actual size of the sprite.
    */
    SpriteComponent::SpriteComponent(const std::string &texturePath, sf::IntRect textureRect, sf::Vector2i targetSize, sf::Vector2i actualSize) {
        _texture.loadFromFile(texturePath);
        _sprite = sf::Sprite(_texture);
        _sprite.setTextureRect(textureRect);
//        _sprite.setScale(sf::Vector2f(3, 3));
        _sprite.setScale(targetSize.x / actualSize.x, targetSize.y / actualSize.y);
        _initialTextureRect = textureRect;
    }

    /*!
    * @brief Destroy the SpriteComponent object.
    */
    SpriteComponent::~SpriteComponent()
    {
        // if (_sprite != nullptr)
        //     RenderComponent::shutdown();
    }

    /*!
    * @brief Draw the sprite on the given window.
    *
    * @param window The window to draw the sprite on.
    */
    void SpriteComponent::draw(sf::RenderWindow &window) {
        window.draw(_sprite);
    }

    /*!
    * @brief Initialize the SpriteComponent.
    */
    void SpriteComponent::init()
    {
        // _sprite = new sf::Sprite();
    }

    /*!
    * @brief Shutdown the SpriteComponent.
    */
    void SpriteComponent::shutdown()
    {
        // delete _sprite;
    }

    /*!
    * @brief Set the sprite of the SpriteComponent.
    *
    * @param sprite The new sprite to set.
    */
    void SpriteComponent::setSprite(sf::Sprite sprite)
    {
        _sprite = sprite;
    }

    /*!
    * @brief Get the sprite of the SpriteComponent.
    *
    * @return A reference to the sprite.
    */
    sf::Sprite &SpriteComponent::getSprite()
    {
        return _sprite;
    }

    /*!
    * @brief Get the texture of the SpriteComponent.
    *
    * @return The texture of the sprite.
    */
    sf::Texture SpriteComponent::getTexture()
    {
        return _texture;
    }

    /*!
    * @brief Get the initial texture rectangle of the sprite.
    *
    * @return The initial texture rectangle.
    */
    sf::IntRect SpriteComponent::getInitialTextRect() {
        return (_initialTextureRect);
    }
}

