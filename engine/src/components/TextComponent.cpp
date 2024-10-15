#include "TextComponent.hpp"

namespace potEngine {

    /*!
    * @brief Construct a new TextComponent object.
    *
    * This constructor initializes the TextComponent with the given text, position, font size, and color.
    *
    * @param text The text to display.
    * @param position The position of the text.
    * @param fontSize The font size of the text.
    * @param color The color of the text.
    */
    TextComponent::TextComponent(std::string text, sf::Vector2f position, int fontSize, sf::Color color)
    {
        _font.loadFromFile("/home/Tom/Bureau/Projet/EPITECH/B-CPP-500-LYN-5-1-rtype-cyprien.diederichs/r-type/assets/fonts/Parisienne-Regular.ttf");
        _text = sf::Text(text, _font, fontSize);
        _text.setFillColor(color);
        _text.setPosition(position);
    }

    /*!
    * @brief Destroy the TextComponent object.
    */
    TextComponent::~TextComponent()
    {
    }

    /*!
    * @brief Draw the text on the given window.
    *
    * @param window The window to draw the text on.
    */
    void TextComponent::draw(sf::RenderWindow &window) {
        window.draw(_text);
    }

    /*!
    * @brief Set the text of the TextComponent.
    *
    * @param text The new text to set.
    */
    void TextComponent::setText(sf::Text text)
    {
        _text = text;
    }

    /*!
    * @brief Get the text of the TextComponent.
    *
    * @return A reference to the text.
    */
    sf::Text &TextComponent::getText()
    {
        return _text;
    }
}

