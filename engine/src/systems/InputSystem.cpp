#include "InputSystem.hpp"
#include "SpriteComponent.hpp"
#include "WindowEntity.hpp"
#include "WindowComponent.hpp"
#include "InputInfoEvent.hpp"
#include <iostream>

namespace potEngine {

    /*!
    * @brief Construct a new Input System object.
    *
    * This constructor initializes the InputSystem and sets up the necessary component signatures and event subscriptions.
    */
    InputSystem::InputSystem() : ASystem()
    {
        _signature.set(AComponent::getID<WindowComponent>(), true);
        engine.subscribeEvent(this, &InputSystem::pollInputs);
    }

    /*!
    * @brief Destroy the Input System object.
    */
    InputSystem::~InputSystem() {

    }

    /*!
    * @brief Poll inputs from the window.
    *
    * This function polls inputs from the window and processes key press and release events.
    *
    * @param event The event triggering the input polling.
    */
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
                if (sfmlEvent.type == sf::Event::KeyPressed) {
                auto key = sfmlEvent.key.code;
                // if (engine.getInputs().find(key) != engine.getInputs().end()) {
                    // engine.setInput(key, true);
                // }
            }
        
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