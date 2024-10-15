#pragma once

#include "RenderComponent.hpp"

namespace potEngine
{
    /*!
    * @brief Component class for rendering text in the game engine.
    */
    class TextComponent : public RenderComponent {
    public:
        TextComponent() {};
        TextComponent(std::string text, sf::Vector2f position=sf::Vector2f(0, 0), int fontSize=32, sf::Color color = sf::Color::Black);
        ~TextComponent();

        void draw(sf::RenderWindow &window) override;
        void setText(sf::Text text);
        sf::Text &getText();
        private:
        sf::Text _text;
        sf::Font _font;
    };
}
