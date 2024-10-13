#pragma once

#include <SFML/Graphics.hpp>

#include "AComponent.hpp"

namespace potEngine {
    class WindowComponent : public AComponent {
    public:
        WindowComponent() {
            _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "R-Type");
            _view.setSize( 1920.f, 1080.f );
            _view.setCenter( _view.getSize().x / 2, _view.getSize().y / 2 );
        };
        ~WindowComponent() {
            delete _window;
        };

        void setWindow(sf::RenderWindow* window) {
            _window = window;
        }
        sf::RenderWindow* getWindow() {
            return _window;
        }
        sf::View &getView() {
            return _view;
        }
    private:
        sf::RenderWindow* _window;
        sf::View _view;
        sf::Color* _colorClear;
    };
}