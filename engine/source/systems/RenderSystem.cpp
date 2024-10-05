#include "RenderSystem.hpp"
#include "RenderComponent.hpp"
#include "WindowEntity.hpp"
#include "WindowComponent.hpp"
#include "PositionComponent.hpp"
#include "EventRender.hpp"
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <unistd.h>

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

        std::cout << "Executable Path: " << execPath << std::endl;
        std::cout << "Project Root Path: " << projectRoot << std::endl;
        std::cout << "Assets Root Path: " << assetsRoot << std::endl;

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

namespace potEngine
{
    RenderSystem::RenderSystem()
    {
        _signature.set(AComponent::getID<RenderComponent>(), true);
        eventBus.subscribe(this, &RenderSystem::renderWindow);
    }

    RenderSystem::~RenderSystem() {

    }

    void RenderSystem::renderWindow(std::shared_ptr<EventRender> event) {
        auto windowEntity = event->windows->getComponent<WindowComponent>();
        if (windowEntity == std::nullopt) {
            return;
        }
        auto window = windowEntity->get()->getWindow();
        window->clear();
        auto sprites = event->sprites;
        for (auto& sprite : sprites) {
            auto render = sprite->getComponent<RenderComponent>();
            if (render) {
                auto nrender = render->get();
                auto position = sprite->getComponent<PositionComponent>();
                if (position != std::nullopt) {
                    auto pos = position->get()->_position;
                    nrender->getSprite().setPosition(pos[0], pos[1]);
                }
                auto sprite = render->get()->getSprite();
                window->draw(sprite);
            }
        }
        window->display();
    }
}