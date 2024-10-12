#include <iostream>
#include "../include/core/Engine.hpp"
#include "../include/core/AEntity.hpp"
#include "../include/components/RenderComponent.hpp"
#include <SFML/Graphics.hpp>

int mainPotEngine()
{
    potEngine::Engine engine;

    engine.init();
    potEngine::AEntity& test = engine.createEntity();

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
        engine.update(0.0f);
    }

    engine.shutdown();

    return 0;
}