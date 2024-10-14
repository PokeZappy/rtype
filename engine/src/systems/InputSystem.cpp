#include "InputSystem.hpp"
#include "WindowEntity.hpp"
#include "WindowComponent.hpp"
#include "InputInfoEvent.hpp"

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
            sf::Event sfmlEvent;

            while (window->pollEvent(sfmlEvent))
            {
                engine.publishEvent(std::make_shared<InputInfoEvent>(sfmlEvent.type, sfmlEvent.key.code));
            //     if (sfmlEvent.type == sf::Event::KeyPressed) {
            //     auto key = sfmlEvent.key.code;
            //     // if (engine.getInputs().find(key) != engine.getInputs().end()) {
            //         // engine.setInput(key, true);
            //     // }
            // }
        
            // if (sfmlEvent.type == sf::Event::KeyReleased) {
            //     auto key = sfmlEvent.key.code;
            //     // if (engine.getInputs().find(key) != engine.getInputs().end()) {
            //     //     engine.setInput(key, false);
            //     // }
            // }
                // std::shared_ptr<InputInfoEvent> input = std::make_shared<InputInfoEvent>(sfmlEvent.type, sfmlEvent.key.code);
                // engine.publishEvent(input);
            }
        }
            // if (sfmlEvent.type == sf::Event::Closed)
            //     window->close();

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