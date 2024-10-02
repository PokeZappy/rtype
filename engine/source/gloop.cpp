#include "gloop.hpp"
#include "ECSManager.hpp"
#include "AEntity.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"

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

    std::shared_ptr<potEngine::RenderComponent> renderComponentPtr = std::make_shared<potEngine::RenderComponent>(sprite);
    std::shared_ptr<potEngine::RenderComponent> windowRenderPtr = std::make_shared<potEngine::RenderComponent>();
    std::shared_ptr<potEngine::WindowComponent> WindowComponentPtr = std::make_shared<potEngine::WindowComponent>();


    std::shared_ptr<potEngine::RenderComponent> renderComponentPtr2 = std::make_shared<potEngine::RenderComponent>(sprite2);

    std::vector<potEngine::AEntity> vec;

    vec.push_back(*test);
    vec.push_back(*colTest);

    auto tesnew = std::make_shared<potEngine::EventRender>(*window, vec);

    auto start = std::make_shared<potEngine::StartEvent>();
    start->_mainLoopEvent->addEventMainLoop(tesnew);
    std ::cout << "Event start " << typeid(start).name() << std::endl;
    eventBus.publish(start);
    
    ecsManager.addComponent<potEngine::RenderComponent>(test, renderComponentPtr2);
    ecsManager.addComponent<potEngine::RenderComponent>(test, renderComponentPtr);
    ecsManager.addComponent<potEngine::RenderComponent>(window, windowRenderPtr);
    ecsManager.addComponent<potEngine::WindowComponent>(window, WindowComponentPtr);

    
    // potEngine::AEntity& window = ecsManager.createEntity();
    // potEngine::window& nwindow = static_cast<potEngine::window&>(window);
    // nwindow.setWindow(new sf::RenderWindow(sf::VideoMode(800, 600), "potEngine"));

    // TODO: Add a window entity to the ECSManager and its component and its system
    ecsManager.update(0.03);

    ecsManager.shutdown();
    return 0;
}
