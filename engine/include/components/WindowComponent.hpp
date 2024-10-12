#pragma once

#include <SFML/Graphics.hpp>

#include "AComponent.hpp"

namespace potEngine {
    class WindowComponent : public AComponent {
    public:
        WindowComponent() {
            _window = new sf::RenderWindow(sf::VideoMode(800, 600), "R-Type");
        };
        ~WindowComponent() {};

        void setWindow(sf::RenderWindow* window) {
            _window = window;
        }
        sf::RenderWindow* getWindow() {
            return _window;
        }
    private:
        sf::RenderWindow* _window;
        sf::Color* _colorClear;
    };
}