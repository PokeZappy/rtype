#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>

namespace potEngine {
    class WindowComponent : public AComponent {
    public:
        WindowComponent() {
            _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "R-Type");
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