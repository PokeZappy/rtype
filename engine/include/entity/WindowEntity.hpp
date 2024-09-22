#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Entity.hpp"

namespace potEngine
{
    class WindowEntity : public Entity {
    public:
        WindowEntity(const std::size_t id);
        WindowEntity(const std::size_t id, sf::RenderWindow* window);
        ~WindowEntity();

        void setWindowEntity(sf::RenderWindow* window);
        sf::RenderWindow* getWindowEntity();
        sf::Color getColorClear() const;
        void setColorClear(sf::Color color);
    private:
        sf::RenderWindow* _window;
        sf::Color _color = sf::Color::Black;
    };
}