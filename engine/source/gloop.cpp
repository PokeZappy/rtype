#include "gloop.hpp"
#include "ECSManager.hpp"
#include "AEntity.hpp"
#include "EventBus.hpp"
#include "StartEvent.hpp"
#include "RenderSystem.hpp"

int potEngine::gloop::mainPotEngine()
{
    potEngine::ECSManager ecsManager;
    ecsManager.init();
    
    // Sprite initialisation
    const int cubeSize = 100;

    sf::Image redSquareImage;
    redSquareImage.create(cubeSize, cubeSize, sf::Color::Red);

    sf::Image greenSquareImage;
    greenSquareImage.create(cubeSize, cubeSize, sf::Color::Green);

    sf::Texture redSquareTexture;
    redSquareTexture.loadFromImage(redSquareImage);

    sf::Texture greenSquareTexture;
    greenSquareTexture.loadFromImage(greenSquareImage);

    std::shared_ptr<potEngine::AEntity> redSquareEntity = ecsManager.createSpriteEntity(redSquareTexture);
    std::shared_ptr<potEngine::AEntity> greenSquareEntity = ecsManager.createSpriteEntity(greenSquareTexture);
    std::shared_ptr<potEngine::AEntity> window = ecsManager.createWindowEntity();

    std::vector<std::shared_ptr<potEngine::AEntity>> spriteArray;

    spriteArray.push_back(redSquareEntity);
    spriteArray.push_back(greenSquareEntity);

    auto tesnew = std::make_shared<potEngine::EventRender>(window, spriteArray);
    auto rend = std::make_shared<potEngine::RenderSystem>();

    // eventBus.subscribe(tesnew.get(), &EventRender::render);

    auto start = std::make_shared<potEngine::StartEvent>();
    // std ::cout << "Event start " << typeid(start).name() << std::endl;
    eventBus.publish(start);
    
    start->addEvent(tesnew);

    
    // potEngine::AEntity& window = ecsManager.createEntity();
    // potEngine::window& nwindow = static_cast<potEngine::window&>(window);
    // nwindow.setWindow(new sf::RenderWindow(sf::VideoMode(800, 600), "potEngine"));

    // TODO: Add a window entity to the ECSManager and its component and its system
    ecsManager.update(0.03);

    ecsManager.shutdown();
    return 0;
}
