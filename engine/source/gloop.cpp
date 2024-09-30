#include "gloop.hpp"
#include "ECSManager.hpp"
#include "AEntity.hpp"
#include "EventBus.hpp"

int potEngine::gloop::mainPotEngine()
{
    potEngine::ECSManager ecsManager;

    ecsManager.init();
    std::shared_ptr<potEngine::AEntity> test = ecsManager.createEntity();
    std::shared_ptr<potEngine::AEntity> window = ecsManager.createEntity();
    std::shared_ptr<potEngine::AEntity> colTest = ecsManager.createEntity();

    const int cubeSize = 100;

    sf::Image image;
    image.create(cubeSize, cubeSize, sf::Color::Red);

    sf::Image image2;
    image2.create(cubeSize, cubeSize, sf::Color::Green);

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Texture texture2;
    texture2.loadFromImage(image2);

    sf::Sprite* sprite;
    sf::Sprite* sprite2;

    sprite = new sf::Sprite(texture);
    sprite2 = new sf::Sprite(texture2);
    sprite2->setPosition(100, 100);

    sf::RenderWindow* windowEntity = new sf::RenderWindow(sf::VideoMode(800, 600), "potEngine");
    // window->setWindowEntity(windowEntity);

    std::shared_ptr<potEngine::RenderComponent> renderComponentPtr = std::make_shared<potEngine::RenderComponent>(sprite);
    std::shared_ptr<potEngine::RenderComponent> windowRenderComponentPtr = std::make_shared<potEngine::RenderComponent>();
    std::shared_ptr<potEngine::WindowDisplayComponent> windowDisplayComponentPtr = std::make_shared<potEngine::WindowDisplayComponent>();


    std::shared_ptr<potEngine::RenderComponent> renderComponentPtr2 = std::make_shared<potEngine::RenderComponent>(sprite2);

    test->addComponent(renderComponentPtr2);
    test->addComponent(renderComponentPtr);
    window->addComponent(windowRenderComponentPtr);
    window->addComponent(windowDisplayComponentPtr);
    ecsManager.registerSystem<potEngine::RenderSystem>();

    // potEngine::AEntity& window = ecsManager.createEntity();
    // potEngine::window& nwindow = static_cast<potEngine::window&>(window);
    // nwindow.setWindow(new sf::RenderWindow(sf::VideoMode(800, 600), "potEngine"));

    // TODO: Add a window entity to the ECSManager and its component and its system
    while (true) {
        ecsManager.update(0.03);
    }

    ecsManager.shutdown();
    return 0;
}
