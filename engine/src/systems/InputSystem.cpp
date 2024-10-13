#include "InputSystem.hpp"
#include "WindowEntity.hpp"
#include "WindowComponent.hpp"
#include "InputInfoEvent.hpp"

sf::View adjustAspectWithBlackBars(sf::View view, float windowWidth, float windowHeight) {
    float windowRatio = windowWidth / windowHeight;
    float viewRatio = view.getSize().x / view.getSize().y;
    std::vector<float> pos(2, 0);
    std::vector<float> size(2, 1);

    if (windowRatio >= viewRatio) {
        size[0] = viewRatio / windowRatio;
        pos[0] = (1 - size[0]) / 2.f;
    } else {
        size[1] = windowRatio / viewRatio;
        pos[1] = (1 - size[1]) / 2.f;
    }
    view.setViewport(sf::FloatRect(pos[0], pos[1], size[0], size[1]));
    return view;
}

namespace potEngine {

    InputSystem::InputSystem() : ASystem()
    {
        _signature.set(AComponent::getID<WindowComponent>(), true);
        engine.subscribeEvent(this, &InputSystem::pollInputs);
    }

    InputSystem::~InputSystem() {

    }

    void InputSystem::pollInputs(std::shared_ptr<NoneEvent> event) {
        // std::cout << "INPUT" << std::endl;
        for (auto entity : _entitiesSystem) {
            auto windowComponent = entity->getComponent<WindowComponent>();
            if (!windowComponent)
                return;
            auto window = windowComponent->get()->getWindow();
            sf::View &view = windowComponent->get()->getView();
            window->setView(view);
            sf::Event sfmlEvent;

            while (window->pollEvent(sfmlEvent))
            {
                engine.publishEvent(std::make_shared<InputInfoEvent>(sfmlEvent.type, sfmlEvent.key.code));
                if (sfmlEvent.type == sf::Event::KeyPressed) {
                    auto key = sfmlEvent.key.code;
                    // if (engine.getInputs().find(key) != engine.getInputs().end()) {
                        // engine.setInput(key, true);
                    // }
                }
                if (sfmlEvent.type == sf::Event::Closed) {
                    window->close();
                    engine.publishEvent(std::make_shared<StopMainLoopEvent>()); // TODO - clear la queue avant de quitter
                }

                if (sfmlEvent.type == sf::Event::Resized)
                    view = adjustAspectWithBlackBars( view, (float)sfmlEvent.size.width, (float)sfmlEvent.size.height );


            if (sfmlEvent.type == sf::Event::KeyReleased) {
                auto key = sfmlEvent.key.code;
                // if (engine.getInputs().find(key) != engine.getInputs().end()) {
                //     engine.setInput(key, false);
                // }
            }
                // std::shared_ptr<InputInfoEvent> input = std::make_shared<InputInfoEvent>(sfmlEvent.type, sfmlEvent.key.code);
                // engine.publishEvent(input);
            }
        }

            // if (sfmlEvent.type == sf::Event::KeyPressed)
            // {
            //     for (char letter = 'A'; letter <= 'Z'; ++letter)
            //     {
            //         if (sfmlEvent.key.code == sf::Keyboard::Key(letter - 'A'))
            //         {
            //             std::cout << "La touche " << letter << " pressée." << std::endl;
            //         }
            //     }
            // }
    }
}