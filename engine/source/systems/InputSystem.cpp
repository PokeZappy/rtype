#include "InputSystem.hpp"
#include "RenderComponent.hpp"
#include "WindowEntity.hpp"
#include "WindowComponent.hpp"
#include "PositionComponent.hpp"
#include "EventRender.hpp"
#include <iostream>

namespace potEngine {

    InputSystem::InputSystem()
    {
        // _signature.set(AComponent::getID<RenderComponent>(), true);
        eventBus.subscribe(this, &InputSystem::pollInputs);
    }

    InputSystem::~InputSystem() {

    }

    void InputSystem::pollInputs(std::shared_ptr<ComputeInputEvent> event) {
        auto windowComponent = event->window->getComponent<WindowComponent>();
        if (!windowComponent)
            return;
        auto window = windowComponent->get()->getWindow();
        
        sf::Event sfmlEvent;

        while (window->pollEvent(sfmlEvent))
        {
            if (sfmlEvent.type == sf::Event::Closed)
                window->close();

            if (sfmlEvent.type == sf::Event::KeyPressed)
            {
                for (char letter = 'A'; letter <= 'Z'; ++letter)
                {
                    if (sfmlEvent.key.code == sf::Keyboard::Key(letter - 'A'))
                    {
                        std::cout << "La touche " << letter << " pressée." << std::endl;
                    }
                }
            }
        }
    }
}