#include "InputSystem.hpp"
#include "SpriteComponent.hpp"
#include "WindowEntity.hpp"
#include "WindowComponent.hpp"
#include "PositionComponent.hpp"
#include "InputInfoEvent.hpp"
#include <iostream>

namespace potEngine {

    InputSystem::InputSystem()
    {
        _signature.set(AComponent::getID<WindowComponent>(), true);
        eventBus.subscribe(this, &InputSystem::pollInputs);
    }

    InputSystem::~InputSystem() {

    }

    void InputSystem::pollInputs(std::shared_ptr<BlcEvent> event) {
        // std::cout << "INPUT" << std::endl;
        for (auto entity : _entitiesSystem) {
            auto windowComponent = entity->getComponent<WindowComponent>();
            if (!windowComponent)
                return;
            auto window = windowComponent->get()->getWindow();
            sf::Event sfmlEvent;

            while (window->pollEvent(sfmlEvent))
            {
                std::shared_ptr<InputInfoEvent> input = std::make_shared<InputInfoEvent>(sfmlEvent.type, sfmlEvent.key.code);
                eventBus.publish(input);
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