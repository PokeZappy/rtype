#include "RenderComponent.hpp"

namespace potEngine {
    RenderComponent::RenderComponent()
    {
        // _sprite = nullptr;
    }

    RenderComponent::RenderComponent(sf::Sprite sprite)
    {
        _sprite = sprite;
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
}

