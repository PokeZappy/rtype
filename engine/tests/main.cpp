#include <iostream>
#include "../include/core/ECSManager.hpp"
#include "../include/core/AEntity.hpp"
#include "../include/components/RenderComponent.hpp"
#include <SFML/Graphics.hpp>

int mainPotEngine()
{
    potEngine::ECSManager ecsManager;

    ecsManager.init();
    potEngine::AEntity& test = ecsManager.createEntity();

    const int cubeSize = 100;

    sf::Image image;
    image.create(cubeSize, cubeSize, sf::Color::Red);

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    test.addComponent<potEngine::RenderComponent>(sprite);

    while (true)
    {
        ecsManager.update(0.0f);
    }

    ecsManager.shutdown();

    return 0;
}