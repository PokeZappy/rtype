#include "ShipAnimationSystem.hpp"
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <unistd.h>

namespace potEngine {
    std::string getExecutablePath() {
    char buffer[1024];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len == -1) throw std::runtime_error("Failed to get executable path.");
    buffer[len] = '\0';
    return std::string(buffer);
}

std::filesystem::path findRootPath(const std::filesystem::path& startPath, const std::string& marker) {
    std::filesystem::path currentPath = startPath;

    while (currentPath != currentPath.root_path()) {
        if (std::filesystem::exists(currentPath / marker)) {
            return currentPath;
        }
        currentPath = currentPath.parent_path();
    }

    throw std::runtime_error("Root directory with marker not found.");
}

std::string assetFinder() {
    try {
        std::string executablePath = getExecutablePath();
        std::filesystem::path execPath(executablePath);
        std::filesystem::path projectRoot = findRootPath(execPath.parent_path(), ".git");
        std::filesystem::path assetsRoot = projectRoot / "r-type" / "assets";

        // std::cout << "Executable Path: " << execPath << std::endl;
        // std::cout << "Project Root Path: " << projectRoot << std::endl;
        // std::cout << "Assets Root Path: " << assetsRoot << std::endl;

        if (!std::filesystem::exists(assetsRoot)) {
            std::cerr << "Folder assets not found, please make sure the assets are in the correct folder." << std::endl;
            return {};
        }

        std::cout << "Assets found at: " << assetsRoot << std::endl;
        return assetsRoot;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {};
    }

}

    void ShipAnimationSystem::updateAnimation(std::shared_ptr<NoneEvent> event) {
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        //     sf::Texture texture;
        //     texture.loadFromFile(assetFinder() + "/sprites/r-typesheet42.gif");
        //     auto entity = engine.createEntity();
        //     auto textComponent = std::make_shared<TextComponent>("coucou", sf::Vector2f(500, 500), 32, sf::Color::White);
        //     engine.addComponent(entity, textComponent);
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        //     auto text = engine.createEntity();
        //     auto textComponent = std::make_shared<TextComponent>("Vous etes mort !", sf::Vector2f(200, 200), 32, sf::Color::White);
        //     engine.addComponent(text, textComponent);
        //     // engine.removeEntity(_playerId);
        // }

        // on monte le ship vers le haut
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            auto playerEntity = engine.getEntity(_playerId);

            if (playerEntity->getComponent<AnimationComponent>() == std::nullopt) {
                std::shared_ptr<AnimationComponent> upAnimation = std::make_shared<AnimationComponent>(2, 0.5, false, changeUpAnimationRect);
                engine.addComponent(playerEntity, upAnimation);
            }
        // on monte le ship vers le bas
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            auto playerEntity = engine.getEntity(_playerId);

            if (playerEntity->getComponent<AnimationComponent>() == std::nullopt) {
                std::shared_ptr<AnimationComponent> upAnimation = std::make_shared<AnimationComponent>(2, 0.5, false, changeDownAnimationRect);
                engine.addComponent(playerEntity, upAnimation);
            }
        } 
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            auto playerEntity = engine.getEntity(_playerId);
            // std::cout << "player entity = " << _playerId << std::endl; 

            if (playerEntity->getComponent<AnimationComponent>() != std::nullopt) {
                playerEntity->removeComponent<AnimationComponent>();
                auto spriteComponent = playerEntity->getComponent<SpriteComponent>();
                if (spriteComponent != std::nullopt) {
                    sf::Sprite &sprite = spriteComponent->get()->getSprite();
                    sprite.setTextureRect(spriteComponent->get()->getInitialTextRect());
                }
            }
        }
    }
};