#include "WindowEntity.hpp"
#include "WindowComponent.hpp"

namespace potEngine
{
    /*!
    * @brief Construct a new WindowEntity object with the given ID.
    *
    * This constructor initializes the WindowEntity and adds a WindowComponent.
    *
    * @param id The ID of the entity.
    */
    WindowEntity::WindowEntity(const std::size_t id) : AEntity(id)
    {
        auto WindowComponentPtr = std::make_shared<WindowComponent>();
        this->addComponent<WindowComponent>(WindowComponentPtr);
    }

    /*!
    * @brief Construct a new WindowEntity object with the given ID and window.
    *
    * This constructor initializes the WindowEntity, adds a WindowComponent, and sets the window.
    *
    * @param id The ID of the entity.
    * @param window A pointer to the SFML RenderWindow.
    */
    WindowEntity::WindowEntity(const std::size_t id, sf::RenderWindow* window) : AEntity(id)
    {
        auto WindowComponentPtr = std::make_shared<WindowComponent>();
        this->addComponent<WindowComponent>(WindowComponentPtr);
    }

    /*!
    * @brief Destroy the WindowEntity object.
    */
    WindowEntity::~WindowEntity() {}

    /*!
    * @brief Set the window for the WindowEntity.
    *
    * @param window A pointer to the SFML RenderWindow.
    */
    void WindowEntity::setWindowEntity(sf::RenderWindow* window) {
        
    }

    /*!
    * @brief Get the window of the WindowEntity.
    *
    * @return A pointer to the SFML RenderWindow.
    */
    sf::RenderWindow* WindowEntity::getWindowEntity() {
        return getComponent<WindowComponent>()->get()->getWindow();
    }

    /*!
    * @brief Get the clear color of the window.
    *
    * @return The clear color of the window.
    */
    sf::Color WindowEntity::getColorClear() const {
        return sf::Color::Black;
    }

    /*!
    * @brief Set the clear color of the window.
    *
    * @param color The clear color to set.
    */
    void WindowEntity::setColorClear(sf::Color color) {
    }
}