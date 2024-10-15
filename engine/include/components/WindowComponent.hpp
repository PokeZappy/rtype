#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>

namespace potEngine {
    class WindowComponent : public AComponent {
    public:
        /*!
        * @brief Construct a new WindowComponent object.
        */
        WindowComponent() {
            _window = new sf::RenderWindow(sf::VideoMode(800, 600), "R-Type");
        };

        /*!
        * @brief Destroy the WindowComponent object.
        */
        ~WindowComponent() {};

        /*!
        * @brief Set the SFML RenderWindow for the component.
        * @param window Pointer to the SFML RenderWindow.
        */
        void setWindow(sf::RenderWindow* window) {
            _window = window;
        }

        /*!
        * @brief Get the SFML RenderWindow of the component.
        * @return Pointer to the SFML RenderWindow.
        */
        sf::RenderWindow* getWindow() {
            return _window;
        }
    private:
        sf::RenderWindow* _window;
        sf::Color* _colorClear;
    };
}