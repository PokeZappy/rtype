#include "TextComponent.hpp"

namespace potEngine {

    TextComponent::TextComponent(std::string text, sf::Vector2f position, int fontSize, sf::Color color)
    {
        _font.loadFromFile("/home/Tom/Bureau/Projet/EPITECH/B-CPP-500-LYN-5-1-rtype-cyprien.diederichs/r-type/assets/fonts/Parisienne-Regular.ttf");
        _text = sf::Text(text, _font, fontSize);
        _text.setColor(color);
        _text.setPosition(position);
    }

    TextComponent::~TextComponent()
    {
    }

    void TextComponent::draw(sf::RenderWindow &window) {
        window.draw(_text);
    }

    void TextComponent::setText(sf::Text text)
    {
        _text = text;
    }

    sf::Text &TextComponent::getText()
    {
        return _text;
    }
}

