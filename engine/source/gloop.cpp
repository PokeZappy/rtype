#include "gloop.hpp"
#include "ECSManager.hpp"
#include "Entity.hpp"
#include "WindowClearSystem.hpp"
#include "WindowDisplaySystem.hpp"

int potEngine::gloop::mainPotEngine()
{
    potEngine::ECSManager ecsManager;

    ecsManager.init();
    std::shared_ptr<potEngine::Entity> test = std::make_shared<potEngine::Entity>(1);
    std::shared_ptr<potEngine::WindowEntity> window = std::make_shared<potEngine::WindowEntity>(2);

    const int cubeSize = 100;

    sf::Image image;
    image.create(cubeSize, cubeSize, sf::Color::Red);

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite* sprite;

    sprite = new sf::Sprite(texture);

    sf::RenderWindow* windowEntity = new sf::RenderWindow(sf::VideoMode(800, 600), "potEngine");
    window->setWindowEntity(windowEntity);

    std::shared_ptr<potEngine::RenderComponent> renderComponentPtr = std::make_shared<potEngine::RenderComponent>(sprite);
    std::shared_ptr<potEngine::WindowDisplayComponent> windowDisplayComponentPtr = std::make_shared<potEngine::WindowDisplayComponent>();
    test->addComponent(renderComponentPtr);
    window->addComponent(windowDisplayComponentPtr);
    ecsManager.registerSystem<potEngine::RenderSystem>();

    ecsManager.addEntity(test);
    ecsManager.addEntity(window);

    // potEngine::Entity& window = ecsManager.createEntity();
    // potEngine::window& nwindow = static_cast<potEngine::window&>(window);
    // nwindow.setWindow(new sf::RenderWindow(sf::VideoMode(800, 600), "potEngine"));

    // TODO: Add a window entity to the ECSManager and its component and its system
    while (true) {
        ecsManager.update(0.03);
    }

    ecsManager.shutdown();

    return 0;
}
