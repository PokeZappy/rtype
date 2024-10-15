#include <iostream>
#include <filesystem>
#include <stdexcept>
#include "Config.hpp"

std::string getExecutablePath() {
    char buffer[BUFFER_SIZE];
    #ifdef _WIN32
        DWORD len = READLINK(NULL, buffer, sizeof(buffer));
        if (len == 0) throw std::runtime_error("Failed to get executable path.");
    #else
        ssize_t len = READLINK("/proc/self/exe", buffer, sizeof(buffer));
        if (len == -1) throw std::runtime_error("Failed to get executable path.");
        buffer[len] = '\0';
    #endif
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

        // std::cout << "Assets found at: " << assetsRoot << std::endl;
        return assetsRoot.string();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {};
    }

}

std::string configFinder(const char *dir) {
    try {
        std::string executablePath = getExecutablePath();
        std::filesystem::path execPath(executablePath);
        std::filesystem::path projectRoot = findRootPath(execPath.parent_path(), ".git");
        std::filesystem::path assetsRoot = projectRoot / "r-type" / dir / "config";

        // std::cout << "Executable Path: " << execPath << std::endl;
        // std::cout << "Project Root Path: " << projectRoot << std::endl;
        // std::cout << "Config Root Path: " << assetsRoot << std::endl;

        if (!std::filesystem::exists(assetsRoot)) {
            std::cerr << "Folder assets not found, please make sure the assets are in the correct folder." << std::endl;
            return {};
        }

        std::cout << "Config found at: " << assetsRoot << std::endl;
        return assetsRoot.string();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {};
    }

}