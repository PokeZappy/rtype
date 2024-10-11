#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "IEvent.hpp"
#include "EventBus.hpp"
#include "ECSManager.hpp"

namespace potEngine {
    class InputInfoEvent : public IEvent {
    public:
        sf::Event::EventType type;
        sf::Keyboard::Key key;

        InputInfoEvent(sf::Event::EventType eType, sf::Keyboard::Key eKey) : type(eType), key(eKey) {};
    };
}